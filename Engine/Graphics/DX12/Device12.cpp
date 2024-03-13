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

#include "Graphics\GraphicsCommon.h"
#include "Strings12.h"


using namespace Kodiak;
using namespace Kodiak::DX12;
using namespace std;


extern "C" { __declspec(dllexport) extern const UINT D3D12SDKVersion = 611; }
extern "C" { __declspec(dllexport) extern const char* D3D12SDKPath = ".\\D3D12\\"; }


namespace
{

Microsoft::WRL::ComPtr<ID3D12Device> g_device;

#if ENABLE_DX12_DEBUG_MARKUP
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
	Microsoft::WRL::ComPtr<IDXGIAdapter3> adapter3;
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

} // anonymous namespace


GraphicsDevice::GraphicsDevice()
{
	LogInfo(LogDirectX) << "Creating DirectX 12 device" << endl;
}


GraphicsDevice::~GraphicsDevice()
{
	LogInfo(LogDirectX) << "Destroying DirectX 12 device" << endl;

#if defined(_DEBUG)
	ID3D12DebugDevice* debugInterface;
	if (SUCCEEDED(m_device->QueryInterface(&debugInterface)))
	{
		debugInterface->ReportLiveDeviceObjects(D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL);
		debugInterface->Release();
	}
#endif

	g_device.Reset();
}


void GraphicsDevice::Initialize(const GraphicsDeviceDesc& graphicsDeviceDesc)
{
	m_deviceDesc = graphicsDeviceDesc;

#if _DEBUG
	Microsoft::WRL::ComPtr<ID3D12Debug> debugInterface;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface))))
	{
		debugInterface->EnableDebugLayer();
	}
	else
	{
		LogWarning(LogDirectX) << "  Unable to enable D3D12 debug validation layer" << endl;
	}
#endif

	const bool bIsDeveloperModeEnabled = IsDeveloperModeEnabled();
	const bool bIsRenderDocAvailable = IsRenderDocAvailable();

	if (bIsDeveloperModeEnabled && !bIsRenderDocAvailable)
	{
		if (SUCCEEDED(D3D12EnableExperimentalFeatures(1, &D3D12ExperimentalShaderModels, nullptr, nullptr)))
		{
			LogInfo(LogDirectX) << "  Enabled D3D12 experimental shader models" << endl;
		}
		else
		{
			LogWarning(LogDirectX) << "  Unable to enable D3D12 experimental shader models" << endl;
		}
	}

	// Obtain the DXGI factory
	assert_succeeded(CreateDXGIFactory2(0, IID_PPV_ARGS(&m_dxgiFactory)));

	Microsoft::WRL::ComPtr<IDXGIFactory6> dxgiFactory6;
	m_dxgiFactory->QueryInterface(IID_PPV_ARGS(dxgiFactory6.GetAddressOf()));

	// Create the D3D graphics device
	IDXGIAdapter* pAdapter{ nullptr };

	static const bool bUseWarpAdapter{ false };
	static const bool bAllowSoftwareRendering{ false };
	static const bool bFavorDiscreteAdapter{ true };

	Microsoft::WRL::ComPtr<ID3D12Device> pDevice;

	const D3D_FEATURE_LEVEL minRequiredLevel{ D3D_FEATURE_LEVEL_11_0 };
	const DXGI_GPU_PREFERENCE gpuPreference{ DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE };

	int32_t firstDiscreteAdapterIdx{ -1 };
	int32_t bestMemoryAdapterIdx{ -1 };
	int32_t firstAdapterIdx{ -1 };
	int32_t warpAdapterIdx{ -1 };
	int32_t chosenAdapter{ -1 };

	size_t bestDedicatedVideoMemory{ 0 };

	LogInfo(LogDirectX) << "Enumerating DXGI adapters..." << endl;

	for (int32_t idx = 0; DXGI_ERROR_NOT_FOUND != EnumAdapters((UINT)idx, gpuPreference, dxgiFactory6.Get(), &pAdapter); ++idx)
	{
		Microsoft::WRL::ComPtr<IDXGIAdapter> adapter{ pAdapter };

		DXGI_ADAPTER_DESC desc{};
		adapter->GetDesc(&desc);

		DeviceBasicCaps basicCaps{};

		if (TestCreateDevice(adapter.Get(), minRequiredLevel, basicCaps))
		{
			string deviceName = MakeStr(desc.Description);
			LogInfo(LogDirectX) << format("  Adapter {} is D3D12-capable: {} (VendorId: {:#x}, DeviceId: {:#x}, SubSysId: {:#x}, Revision: {:#x})",
				idx,
				deviceName,
				desc.VendorId, desc.DeviceId, desc.SubSysId, desc.Revision)
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

			const bool bIsWarpAdapter = desc.VendorId == 0x1414;
			if (bIsWarpAdapter && warpAdapterIdx == -1)
			{
				warpAdapterIdx = idx;
			}

			const bool bSkipWarp = (bUseWarpAdapter && !bIsWarpAdapter) || (!bUseWarpAdapter && bIsWarpAdapter && !bAllowSoftwareRendering);

			const bool bSkipAdapter = bSkipWarp;

			const bool bIsIntegrated = IsAdapterIntegrated(adapter.Get());

			if (!bSkipAdapter)
			{
				if (!bIsWarpAdapter && !bIsIntegrated)
				{
					firstDiscreteAdapterIdx = idx;
				}

				if (desc.DedicatedVideoMemory > bestDedicatedVideoMemory)
				{
					bestMemoryAdapterIdx = idx;
					bestDedicatedVideoMemory = desc.DedicatedVideoMemory;
				}

				if (firstAdapterIdx == -1)
				{
					firstAdapterIdx = idx;
				}
			}
		}
	}

	// Now chose our best adapter
	if (bFavorDiscreteAdapter)
	{
		if (bestMemoryAdapterIdx != -1)
		{
			chosenAdapter = bestMemoryAdapterIdx;
		}
		else if (firstDiscreteAdapterIdx != -1)
		{
			chosenAdapter = firstDiscreteAdapterIdx;
		}
		else
		{
			chosenAdapter = firstAdapterIdx;
		}
	}
	else
	{
		chosenAdapter = firstAdapterIdx;
	}

	if (chosenAdapter == -1)
	{
		LogFatal(LogDirectX) << "Failed to select a D3D12 adapter" << endl;
	}

	// Create device, either WARP or hardware
	if (chosenAdapter == warpAdapterIdx)
	{
		assert_succeeded(m_dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&pAdapter)));
		assert_succeeded(D3D12CreateDevice(pAdapter, m_bestFeatureLevel, IID_PPV_ARGS(&pDevice)));

		m_device = pDevice;
		m_adapter = pAdapter;
		m_bIsWarpAdapter = true;

		if (bUseWarpAdapter)
		{
			LogNotice(LogDirectX) << "Selected WARP software adapter" << endl;
		}
		else
		{
			LogWarning(LogDirectX) << "Failed to find a hardware adapter, falling back to WARP" << endl;
		}
	}
	else
	{
		assert_succeeded(m_dxgiFactory->EnumAdapters((UINT)chosenAdapter, &pAdapter));
		assert_succeeded(D3D12CreateDevice(pAdapter, m_bestFeatureLevel, IID_PPV_ARGS(&pDevice)));
		m_device = pDevice;
		m_adapter = pAdapter;

		LogInfo(LogDirectX) << "Selected D3D12 adapter " << chosenAdapter << endl;
	}

	ReadCaps();

#ifndef _RELEASE
	if (!m_bIsWarpAdapter)
	{
		// Prevent the GPU from overclocking or underclocking to get consistent timings
		if (bIsDeveloperModeEnabled && !bIsRenderDocAvailable)
		{
			m_device->SetStablePowerState(TRUE);
		}
	}
#endif
}


void GraphicsDevice::ReadCaps()
{
	const D3D_FEATURE_LEVEL minFeatureLevel{ D3D_FEATURE_LEVEL_12_0 };
	const D3D_SHADER_MODEL maxShaderModel{ D3D_SHADER_MODEL_6_7 };

	m_caps.ReadFullCaps(m_device.Get(), minFeatureLevel, maxShaderModel);

	m_bestShaderModel = m_caps.basicCaps.maxShaderModel;

	if (g_graphicsDeviceOptions.logDeviceFeatures)
	{
		m_caps.LogCaps();
	}
}

HRESULT GraphicsDevice::EnumAdapters(int32_t adapterIdx, DXGI_GPU_PREFERENCE gpuPreference, IDXGIFactory6* dxgiFactory6, IDXGIAdapter** adapter)
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


Kodiak::DX12::GraphicsDevice* Kodiak::DX12::CreateDevice12(const Kodiak::GraphicsDeviceDesc& desc)
{
	GraphicsDevice* device = new GraphicsDevice;

	device->Initialize(desc);

	g_graphicsDevice = device;

	return device;
}


ID3D12Device* GetDevice()
{
	return g_device.Get();
}