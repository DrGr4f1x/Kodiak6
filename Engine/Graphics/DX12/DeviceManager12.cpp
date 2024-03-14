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
#include "Graphics\DX12\DeviceCaps12.h"
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
	adapter->QueryInterface(IID_PPV_ARGS(adapter3.GetAddressOf()));

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


bool DeviceManager12::CreateInstanceInternal()
{
	if (!m_dxgiFactory)
	{
		if (!SUCCEEDED(CreateDXGIFactory2(m_desc.enableDebugRuntime ? DXGI_CREATE_FACTORY_DEBUG : 0, IID_PPV_ARGS(&m_dxgiFactory))))
		{
			LogFatal(LogDirectX) << "Failed to create DXGIFactory" << endl;
			return false;
		}
	}

	return true;
}


bool DeviceManager12::CreateDevice()
{
	const bool bUseDebugLayer = m_desc.enableDebugRuntime;

	if (bUseDebugLayer)
	{
		IntrusivePtr<ID3D12Debug> debugInterface;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface))))
		{
			debugInterface->EnableDebugLayer();
		}
		else
		{
			LogWarning(LogDirectX) << "  Failed to enable D3D12 debug validation layer" << endl;
		}
	}

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
			LogWarning(LogDirectX) << "  Failed to enable D3D12 experimental shader models" << endl;
		}
	}
}


vector<AdapterInfo> DeviceManager12::EnumerateAdapters()
{
	vector<AdapterInfo> adapters;

	IntrusivePtr<IDXGIFactory6> dxgiFactory6;
	m_dxgiFactory->QueryInterface(IID_PPV_ARGS(dxgiFactory6.GetAddressOf()));

	const D3D_FEATURE_LEVEL minRequiredLevel{ D3D_FEATURE_LEVEL_11_0 };
	const DXGI_GPU_PREFERENCE gpuPreference{ DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE };

	IntrusivePtr<IDXGIAdapter> tempAdapter;
	IntrusivePtr<ID3D12Device> tempDevice;

	LogInfo(LogDirectX) << "Enumerating DXGI adapters..." << endl;

	for (int32_t idx = 0; DXGI_ERROR_NOT_FOUND != EnumAdapter((UINT)idx, gpuPreference, dxgiFactory6.Get(), tempAdapter.GetAddressOf()); ++idx)
	{
		DXGI_ADAPTER_DESC desc{};
		tempAdapter->GetDesc(&desc);

		DeviceBasicCaps basicCaps{};

		if (TestCreateDevice(tempAdapter.Get(), minRequiredLevel, basicCaps))
		{
			AdapterInfo adapterInfo{};

			adapterInfo.name = MakeStr(desc.Description);
			adapterInfo.deviceId = desc.DeviceId;
			adapterInfo.vendorId = desc.VendorId;
			adapterInfo.dedicatedVideoMemory = desc.DedicatedVideoMemory;
			adapterInfo.dedicatedSystemMemory = desc.DedicatedSystemMemory;
			adapterInfo.sharedSystemMemory = desc.SharedSystemMemory;
			adapterInfo.vendor = VendorIdToHardwareVendor(adapterInfo.vendorId);
			adapterInfo.adapterType = GetAdapterType(tempAdapter.Get());
			adapterInfo.adapter = tempAdapter;

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
	}

	return adapters;
}


HRESULT DeviceManager12::EnumAdapter(int32_t adapterIdx, DXGI_GPU_PREFERENCE gpuPreference, IDXGIFactory6* dxgiFactory6, IDXGIAdapter** adapter)
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