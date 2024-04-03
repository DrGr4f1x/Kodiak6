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

#include "DeviceManager12.h"
#include "Graphics\DX12\Device12.h"
#include "Graphics\DX12\DeviceCaps12.h"
#include "Graphics\DX12\Formats12.h"
#include "Graphics\DX12\Queue12.h"
#include "Graphics\DX12\Strings12.h"

using namespace std;


namespace Kodiak::DX12
{

bool TestCreateDevice(IDXGIAdapter* adapter, D3D_FEATURE_LEVEL minFeatureLevel, DeviceBasicCaps& deviceBasicCaps)
{
	IntrusivePtr<ID3D12Device> device;
	if (SUCCEEDED(D3D12CreateDevice(adapter, minFeatureLevel, IID_PPV_ARGS(&device))))
	{
		DeviceCaps testCaps;
		testCaps.ReadBasicCaps(device, minFeatureLevel);
		deviceBasicCaps = testCaps.basicCaps;

		return true;
	}
	return false;
}


AdapterType GetAdapterType(IDXGIAdapter* adapter)
{
	IntrusivePtr<IDXGIAdapter3> adapter3;
	adapter->QueryInterface(IID_PPV_ARGS(&adapter3));

	// Check for integrated adapter
	DXGI_QUERY_VIDEO_MEMORY_INFO nonLocalVideoMemoryInfo{};
	if (adapter3 && SUCCEEDED(adapter3->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_NON_LOCAL, &nonLocalVideoMemoryInfo)))
	{
		if (nonLocalVideoMemoryInfo.Budget == 0)
		{
			return AdapterType::Integrated;
		}
	}

	// Check for software adapter (WARP)
	DXGI_ADAPTER_DESC desc{};
	adapter->GetDesc(&desc);

	if (desc.VendorId == 0x1414)
	{
		return AdapterType::Software;
	}

	return AdapterType::Discrete;
}


DxgiRLOHelper::~DxgiRLOHelper()
{
	if (doReport)
	{
		IDXGIDebug1* pDebug{ nullptr };
		if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&pDebug))))
		{
			pDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
			pDebug->Release();
		}
	}
}


DeviceManager::DeviceManager(const DeviceManagerCreationParams& creationParams)
	: m_creationParams{ creationParams }
{
	m_bIsDeveloperModeEnabled = IsDeveloperModeEnabled();
	m_bIsRenderDocAvailable = IsRenderDocAvailable();

	Initialize();
}


void DeviceManager::BeginFrame()
{
	m_device->BeginFrame();
}


void DeviceManager::Present()
{
	m_device->Present();
}


void DeviceManager::Initialize()
{
	if (!CreateInstance())
	{
		LogFatal(LogDirectX) << "Failed to create DXGI factory." << endl;
		return;
	}

	if (!CreateDevice())
	{
		LogFatal(LogDirectX) << "Failed to create D3D12 device." << endl;
		return;
	}

	if (!CreateSwapChain())
	{
		LogFatal(LogDirectX) << "Failed to create DXGI swapchain." << endl;
	}
}


bool DeviceManager::CreateInstance()
{
	m_dxgiRLOHelper.doReport = m_creationParams.enableValidation;

	if (!m_dxgiFactory)
	{
		if (!SUCCEEDED(CreateDXGIFactory2(m_creationParams.enableValidation ? DXGI_CREATE_FACTORY_DEBUG : 0, IID_PPV_ARGS(&m_dxgiFactory))))
		{
			LogFatal(LogDirectX) << "Failed to create DXGIFactory." << endl;
			return false;
		}
	}
	SetDebugName(m_dxgiFactory, "DXGI Factory");

	IntrusivePtr<IDXGIFactory5> dxgiFactory5;
	if (SUCCEEDED(m_dxgiFactory->QueryInterface(IID_PPV_ARGS(&dxgiFactory5))))
	{
		BOOL supported{ 0 };
		if (SUCCEEDED(dxgiFactory5->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &supported, sizeof(supported))))
		{
			m_bIsTearingSupported = (supported != 0);
		}
	}

	if (m_creationParams.enableValidation)
	{
		IntrusivePtr<ID3D12Debug> debugInterface;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface))))
		{
			debugInterface->EnableDebugLayer();
			LogInfo(LogDirectX) << "Enabled D3D12 debug layer." << endl;
		}
		else
		{
			LogWarning(LogDirectX) << "Failed to enable D3D12 debug layer." << endl;
		}
	}

	if (m_bIsDeveloperModeEnabled && !m_bIsRenderDocAvailable)
	{
		if (SUCCEEDED(D3D12EnableExperimentalFeatures(1, &D3D12ExperimentalShaderModels, nullptr, nullptr)))
		{
			LogInfo(LogDirectX) << "Enabled D3D12 experimental shader models" << endl;
		}
		else
		{
			LogWarning(LogDirectX) << "Failed to enable D3D12 experimental shader models" << endl;
		}
	}

	return true;
}


bool DeviceManager::CreateDevice()
{
	vector<AdapterInfo> adapterInfos = EnumerateAdapters();

	int32_t firstDiscreteAdapterIdx{ -1 };
	int32_t bestMemoryAdapterIdx{ -1 };
	int32_t firstAdapterIdx{ -1 };
	int32_t warpAdapterIdx{ -1 };
	int32_t chosenAdapterIdx{ -1 };
	size_t maxMemory{ 0 };

	int32_t adapterIdx{ 0 };
	for (const auto& adapterInfo : adapterInfos)
	{
		if (firstAdapterIdx == -1)
		{
			firstAdapterIdx = adapterIdx;
		}

		if (adapterInfo.adapterType == AdapterType::Discrete && firstDiscreteAdapterIdx == -1)
		{
			firstDiscreteAdapterIdx = adapterIdx;
		}

		if (adapterInfo.adapterType == AdapterType::Software && warpAdapterIdx == -1 && m_creationParams.allowSoftwareDevice)
		{
			warpAdapterIdx = adapterIdx;
		}

		if (adapterInfo.dedicatedVideoMemory > maxMemory)
		{
			maxMemory = adapterInfo.dedicatedVideoMemory;
			bestMemoryAdapterIdx = adapterIdx;
		}

		++adapterIdx;
	}

	// Now choose our best adapter
	if (m_creationParams.preferDiscreteDevice)
	{
		if (bestMemoryAdapterIdx != -1)
		{
			chosenAdapterIdx = bestMemoryAdapterIdx;
		}
		else if (firstDiscreteAdapterIdx != -1)
		{
			chosenAdapterIdx = firstDiscreteAdapterIdx;
		}
		else
		{
			chosenAdapterIdx = firstAdapterIdx;
		}
	}
	else
	{
		chosenAdapterIdx = firstAdapterIdx;
	}

	if (chosenAdapterIdx == -1)
	{
		LogFatal(LogDirectX) << "Failed to select a D3D12 adapter." << endl;
		return false;
	}

	// Create device, either WARP or hardware
	IntrusivePtr<ID3D12Device> device{ nullptr };
	if (chosenAdapterIdx == warpAdapterIdx)
	{
		IntrusivePtr<IDXGIAdapter> tempAdapter;
		assert_succeeded(m_dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&tempAdapter)));
		assert_succeeded(D3D12CreateDevice(tempAdapter, m_bestFeatureLevel, IID_PPV_ARGS(&device)));

		m_bIsWarpAdapter = true;

		LogWarning(LogDirectX) << "Failed to find a hardware adapter, falling back to WARP." << endl;
	}
	else
	{
		IntrusivePtr<IDXGIAdapter> tempAdapter;
		assert_succeeded(m_dxgiFactory->EnumAdapters((UINT)chosenAdapterIdx, &tempAdapter));
		assert_succeeded(D3D12CreateDevice(tempAdapter, m_bestFeatureLevel, IID_PPV_ARGS(&device)));

		LogInfo(LogDirectX) << "Selected D3D12 adapter " << chosenAdapterIdx << endl;
	}

#ifndef _RELEASE
	if (!m_bIsWarpAdapter)
	{
		// Prevent the GPU from overclocking or underclocking to get consistent timings
		if (m_bIsDeveloperModeEnabled && !m_bIsRenderDocAvailable)
		{
			device->SetStablePowerState(TRUE);
		}
	}
#endif

	// Create the Kodiak GraphicsDevice
	auto creationParams = DeviceCreationParams{}
		.SetDxgiFactory(m_dxgiFactory.Get())
		.SetDevice(device)
		.SetBackBufferWidth(m_creationParams.backBufferWidth)
		.SetBackBufferHeight(m_creationParams.backBufferHeight)
		.SetNumSwapChainBuffers(m_creationParams.numSwapChainBuffers)
		.SetSwapChainFormat(m_creationParams.swapChainFormat)
		.SetSwapChainSampleCount(m_creationParams.swapChainSampleCount)
		.SetSwapChainSampleQuality(m_creationParams.swapChainSampleQuality)
		.SetAllowModeSwitch(m_creationParams.allowModeSwitch)
		.SetIsTearingSupported(m_bIsTearingSupported)
		.SetEnableVSync(m_creationParams.enableVSync)
		.SetMaxFramesInFlight(m_creationParams.maxFramesInFlight)
		.SetHwnd(m_creationParams.hwnd)
		.SetEnableValidation(m_creationParams.enableValidation)
		.SetEnableDebugMarkers(m_creationParams.enableDebugMarkers);

	m_device = DeviceHandle::Create(new GraphicsDevice(creationParams));

	if (!m_device->Initialize())
	{
		LogError(LogDirectX) << "Failed to initialize D3D12 GraphicsDevice." << endl;
		return false;
	}

	return true;
}


bool DeviceManager::CreateSwapChain()
{
	return m_device->CreateSwapChain();
}


vector<AdapterInfo> DeviceManager::EnumerateAdapters()
{
	vector<AdapterInfo> adapters;

	IntrusivePtr<IDXGIFactory6> dxgiFactory6;
	m_dxgiFactory->QueryInterface(IID_PPV_ARGS(&dxgiFactory6));

	const D3D_FEATURE_LEVEL minRequiredLevel{ D3D_FEATURE_LEVEL_11_0 };
	const DXGI_GPU_PREFERENCE gpuPreference{ DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE };

	IDXGIAdapter* tempAdapter{ nullptr };

	LogInfo(LogDirectX) << "Enumerating DXGI adapters..." << endl;

	for (int32_t idx = 0; DXGI_ERROR_NOT_FOUND != EnumAdapter((UINT)idx, gpuPreference, dxgiFactory6.Get(), &tempAdapter); ++idx)
	{
		DXGI_ADAPTER_DESC desc{};
		tempAdapter->GetDesc(&desc);

		DeviceBasicCaps basicCaps{};

		if (TestCreateDevice(tempAdapter, minRequiredLevel, basicCaps))
		{
			AdapterInfo adapterInfo{};

			adapterInfo.name = MakeStr(desc.Description);
			adapterInfo.deviceId = desc.DeviceId;
			adapterInfo.vendorId = desc.VendorId;
			adapterInfo.dedicatedVideoMemory = desc.DedicatedVideoMemory;
			adapterInfo.dedicatedSystemMemory = desc.DedicatedSystemMemory;
			adapterInfo.sharedSystemMemory = desc.SharedSystemMemory;
			adapterInfo.vendor = VendorIdToHardwareVendor(adapterInfo.vendorId);
			adapterInfo.adapterType = GetAdapterType(tempAdapter);

			LogInfo(LogDirectX) << format("  Adapter {} is D3D12-capable: {} (Vendor: {}, VendorId: {:#x}, DeviceId: {:#x})",
				idx,
				adapterInfo.name,
				HardwareVendorToString(adapterInfo.vendor),
				adapterInfo.vendorId, adapterInfo.deviceId)
				<< endl;

			LogInfo(LogDirectX) << format("    Feature level {}, shader model {}, binding tier {}, wave ops {}, atomic64 {}",
				D3DTypeToString(basicCaps.maxFeatureLevel, true),
				D3DTypeToString(basicCaps.maxShaderModel, true),
				D3DTypeToString(basicCaps.resourceBindingTier, true),
				basicCaps.bSupportsWaveOps ? "supported" : "not supported",
				basicCaps.bSupportsAtomic64 ? "supported" : "not supported")
				<< endl;

			LogInfo(LogDirectX) << format("    Adapter memory: {} MB dedicated video memory, {} MB dedicated system memory, {} MB shared memory",
				(uint32_t)(desc.DedicatedVideoMemory >> 20),
				(uint32_t)(desc.DedicatedSystemMemory >> 20),
				(uint32_t)(desc.SharedSystemMemory >> 20))
				<< endl;

			m_bestFeatureLevel = basicCaps.maxFeatureLevel;
			m_bestShaderModel = basicCaps.maxShaderModel;

			adapters.push_back(adapterInfo);
		}

		tempAdapter->Release();
		tempAdapter = nullptr;
	}

	return adapters;
}


HRESULT DeviceManager::EnumAdapter(int32_t adapterIdx, DXGI_GPU_PREFERENCE gpuPreference, IDXGIFactory6* dxgiFactory6, IDXGIAdapter** adapter)
{
	if (!dxgiFactory6 || gpuPreference == DXGI_GPU_PREFERENCE_UNSPECIFIED)
	{
		return m_dxgiFactory->EnumAdapters((UINT)adapterIdx, adapter);
	}
	else
	{
		return dxgiFactory6->EnumAdapterByGpuPreference((UINT)adapterIdx, gpuPreference, IID_PPV_ARGS(adapter));
	}
}

} // namespace Kodiak::DX12