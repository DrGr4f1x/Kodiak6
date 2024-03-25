//
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Author:  David Elder
//

#include "Stdafx.h"

#include "Device12.h"

#include "DeviceCaps12.h"
#include "Formats12.h"
#include "Queue12.h"
#include "Strings12.h"


using namespace Kodiak;
using namespace Kodiak::DX12;
using namespace std;


extern "C" { __declspec(dllexport) extern const UINT D3D12SDKVersion = 611; }
extern "C" { __declspec(dllexport) extern const char* D3D12SDKPath = ".\\D3D12\\"; }


namespace
{

#if ENABLE_D3D12_DEBUG_MARKERS
void SetDebugName(ID3D12Object* object, const string& name)
{
	object->SetPrivateData(WKPDID_D3DDebugObjectName, UINT(name.size()), name.data());
}
#else
void SetDebugName(ID3D12Object* object, const string& name) {}
#endif


bool IsDirectXAgilitySDKAvailable()
{
	HMODULE agilitySDKDllHandle = ::GetModuleHandle("D3D12Core.dll");
	return agilitySDKDllHandle != nullptr;
}


bool IsAdapterIntegrated(IDXGIAdapter* adapter)
{
	IntrusivePtr<IDXGIAdapter3> adapter3;
	adapter->QueryInterface(IID_PPV_ARGS(adapter3.GetAddressOf()));

	DXGI_QUERY_VIDEO_MEMORY_INFO nonLocalVideoMemoryInfo{};
	if (adapter3 && SUCCEEDED(adapter3->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_NON_LOCAL, &nonLocalVideoMemoryInfo)))
	{
		return nonLocalVideoMemoryInfo.Budget == 0;
	}

	return true;
}


bool TestCreateDevice(IDXGIAdapter* adapter, D3D_FEATURE_LEVEL minFeatureLevel, DeviceBasicCaps& deviceBasicCaps)
{
	ID3D12Device* device = nullptr;
	if (SUCCEEDED(D3D12CreateDevice(adapter, minFeatureLevel, IID_PPV_ARGS(&device))))
	{
		DeviceCaps testCaps;
		testCaps.ReadBasicCaps(device, minFeatureLevel);
		deviceBasicCaps = testCaps.basicCaps;

		device->Release();
		return true;
	}
	return false;
}


void DebugMessageCallback(
	D3D12_MESSAGE_CATEGORY category,
	D3D12_MESSAGE_SEVERITY severity,
	D3D12_MESSAGE_ID id,
	LPCSTR pDescription,
	void* pContext)
{
	using namespace Kodiak;
	using namespace Kodiak::DX12;

	string debugMessage = format("[{}] Code {} : {}", category, (uint32_t)id, pDescription);

	switch (severity)
	{
	case D3D12_MESSAGE_SEVERITY_CORRUPTION:
		LogFatal(LogDirectX) << debugMessage << endl;
		break;
	case D3D12_MESSAGE_SEVERITY_ERROR:
		LogError(LogDirectX) << debugMessage << endl;
		break;
	case D3D12_MESSAGE_SEVERITY_WARNING:
		LogWarning(LogDirectX) << debugMessage << endl;
		break;
	case D3D12_MESSAGE_SEVERITY_INFO:
	case D3D12_MESSAGE_SEVERITY_MESSAGE:
		LogInfo(LogDirectX) << debugMessage << endl;
		break;
	}
}

} // anonymous namespace


GraphicsDevice::GraphicsDevice(const DeviceCreationParams& deviceCreationParams) noexcept
	: m_deviceCreationParams{ deviceCreationParams }
{
	LogInfo(LogDirectX) << "Creating DirectX 12 device." << endl;

	m_dxgiFactory = m_deviceCreationParams.dxgiFactory;
	m_dxDevice.Attach(m_deviceCreationParams.dx12Device);

	SetDebugName(m_dxDevice.Get(), "Device");
}


GraphicsDevice::~GraphicsDevice()
{
	LogInfo(LogDirectX) << "Destroying DirectX 12 device." << endl;

	for (auto fenceEvent : m_frameFenceEvents)
	{
		WaitForSingleObject(fenceEvent, INFINITE);
		CloseHandle(fenceEvent);
	}

	if (m_dxInfoQueue)
	{
		m_dxInfoQueue->UnregisterMessageCallback(m_callbackCookie);
		m_dxInfoQueue.Reset();
	}

	for (auto& queue : m_queues)
	{
		queue.reset();
	}

	if (m_deviceCreationParams.enableValidation)
	{
		ID3D12DebugDevice* debugInterface{ nullptr };
		if (SUCCEEDED(m_dxDevice->QueryInterface(&debugInterface)))
		{
			debugInterface->ReportLiveDeviceObjects(D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL);
			debugInterface->Release();
		}
	}
}


bool GraphicsDevice::Initialize()
{
	CreateQueue(QueueType::Graphics);
	CreateQueue(QueueType::Compute);
	CreateQueue(QueueType::Copy);

	m_caps = make_unique<DeviceCaps>();
	ReadCaps();

	return true;
}


bool GraphicsDevice::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	swapChainDesc.Width = m_deviceCreationParams.backBufferWidth;
	swapChainDesc.Height = m_deviceCreationParams.backBufferHeight;
	swapChainDesc.SampleDesc.Count = m_deviceCreationParams.swapChainSampleCount;
	swapChainDesc.SampleDesc.Quality = m_deviceCreationParams.swapChainSampleQuality;
	swapChainDesc.BufferUsage = DXGI_USAGE_SHADER_INPUT | DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = m_deviceCreationParams.numSwapChainBuffers;
	swapChainDesc.Flags = m_deviceCreationParams.allowModeSwitch ? DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH : 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	switch (m_deviceCreationParams.swapChainFormat)
	{
	case Format::SRGBA8_UNorm:
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		break;
	case Format::SBGRA8_UNorm:
		swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		break;
	default:
		swapChainDesc.Format = FormatToDxgi(m_deviceCreationParams.swapChainFormat).srvFormat;
		break;
	}

	if (m_deviceCreationParams.isTearingSupported)
	{
		swapChainDesc.Flags |= DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
	}

	IntrusivePtr<IDXGISwapChain1> swapChain1;
	if (FAILED(m_dxgiFactory->CreateSwapChainForHwnd(GetQueue(QueueType::Graphics).GetCommandQueue(), m_deviceCreationParams.hwnd, &swapChainDesc, nullptr, nullptr, &swapChain1)))
	{
		LogError(LogDirectX) << "Failed to create swap chain." << endl;
		return false;
	}

	if (FAILED(swapChain1->QueryInterface(IID_PPV_ARGS(&m_dxgiSwapChain))))
	{
		LogError(LogDirectX) << "Failed to get IDXGISwapChain3 interface." << endl;
		return false;
	}

	if (FAILED(m_dxDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_frameFence))))
	{
		LogError(LogDirectX) << "Failed to create frame fence." << endl;
		return false;
	}

	for (uint32_t bufferIdx = 0; bufferIdx < swapChainDesc.BufferCount; ++bufferIdx)
	{
		m_frameFenceEvents.push_back(CreateEvent(nullptr, false, true, nullptr));
	}

	return true;
}


void GraphicsDevice::BeginFrame()
{
	// TODO Handle window resize here

	auto bufferIndex = m_dxgiSwapChain->GetCurrentBackBufferIndex();
	WaitForSingleObject(m_frameFenceEvents[bufferIndex], INFINITE);
}


void GraphicsDevice::Present()
{
	if (!m_bIsWindowVisible)
	{
		return;
	}

	auto bufferIndex = m_dxgiSwapChain->GetCurrentBackBufferIndex();

	UINT presentFlags = 0;

	m_dxgiSwapChain->Present(m_deviceCreationParams.enableVSync ? 1 : 0, presentFlags);

	m_frameFence->SetEventOnCompletion(m_frameCount, m_frameFenceEvents[bufferIndex]);
	GetQueue(QueueType::Graphics).GetCommandQueue()->Signal(m_frameFence, m_frameCount);
	++m_frameCount;
}


CommandContextHandle GraphicsDevice::BeginCommandContext(const string& ID)
{
	return nullptr;
}


GraphicsContextHandle GraphicsDevice::BeginGraphicsContext(const string& ID)
{
	return nullptr;
}


ComputeContextHandle GraphicsDevice::BeginComputeContext(const string& ID, bool bAsync)
{
	return nullptr;
}


void GraphicsDevice::ReadCaps()
{
	const D3D_FEATURE_LEVEL minFeatureLevel{ D3D_FEATURE_LEVEL_12_0 };
	const D3D_SHADER_MODEL maxShaderModel{ D3D_SHADER_MODEL_6_7 };

	m_caps->ReadFullCaps(m_dxDevice.Get(), minFeatureLevel, maxShaderModel);

	// TODO
	//if (g_graphicsDeviceOptions.logDeviceFeatures)
	if (false)
	{
		m_caps->LogCaps();
	}
}


void GraphicsDevice::InstallDebugCallback()
{
	if (SUCCEEDED(m_dxDevice->QueryInterface(IID_PPV_ARGS(&m_dxInfoQueue))))
	{
		// Suppress whole categories of messages
		//D3D12_MESSAGE_CATEGORY Categories[] = {};

		// Suppress messages based on their severity level
		D3D12_MESSAGE_SEVERITY severities[] =
		{
			D3D12_MESSAGE_SEVERITY_INFO
		};

		// Suppress individual messages by their ID
		D3D12_MESSAGE_ID denyIds[] =
		{
			// This occurs when there are uninitialized descriptors in a descriptor table, even when a
			// shader does not access the missing descriptors.  I find this is common when switching
			// shader permutations and not wanting to change much code to reorder resources.
			D3D12_MESSAGE_ID_INVALID_DESCRIPTOR_HANDLE,

			// Triggered when a shader does not export all color components of a render target, such as
			// when only writing RGB to an R10G10B10A2 buffer, ignoring alpha.
			D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_PS_OUTPUT_RT_OUTPUT_MISMATCH,

			// This occurs when a descriptor table is unbound even when a shader does not access the missing
			// descriptors.  This is common with a root signature shared between disparate shaders that
			// don't all need the same types of resources.
			D3D12_MESSAGE_ID_COMMAND_LIST_DESCRIPTOR_TABLE_NOT_SET,

			D3D12_MESSAGE_ID_COPY_DESCRIPTORS_INVALID_RANGES,

			// Silence complaints about shaders not being signed by DXIL.dll.  We don't care about this.
			D3D12_MESSAGE_ID_NON_RETAIL_SHADER_MODEL_WONT_VALIDATE,

			// RESOURCE_BARRIER_DUPLICATE_SUBRESOURCE_TRANSITIONS
			(D3D12_MESSAGE_ID)1008,
		};

		D3D12_INFO_QUEUE_FILTER newFilter = {};
		//newFilter.DenyList.NumCategories = _countof(Categories);
		//newFilter.DenyList.pCategoryList = Categories;
		newFilter.DenyList.NumSeverities = _countof(severities);
		newFilter.DenyList.pSeverityList = severities;
		newFilter.DenyList.NumIDs = _countof(denyIds);
		newFilter.DenyList.pIDList = denyIds;

		m_dxInfoQueue->PushStorageFilter(&newFilter);
		m_dxInfoQueue->RegisterMessageCallback(DebugMessageCallback, D3D12_MESSAGE_CALLBACK_FLAG_NONE, nullptr, &m_callbackCookie);
	}
}


void GraphicsDevice::CreateQueue(QueueType queueType)
{
	m_queues[(uint32_t)queueType] = make_unique<Queue>(m_dxDevice.Get(), queueType);
}


Queue& GraphicsDevice::GetQueue(QueueType queueType)
{
	return *m_queues[(uint32_t)queueType];
}


Queue& GraphicsDevice::GetQueue(CommandListType commandListType)
{
	const auto queueType = CommandListTypeToQueueType(commandListType);
	return GetQueue(queueType);
}