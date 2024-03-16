//
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Author:  David Elder
//

#pragma once

#include "Graphics\DeviceManager.h"
#include "Graphics\DX12\DirectXCommon.h"


namespace Kodiak::DX12
{

// Forward declarations
struct DeviceCaps;


class DeviceManager12 : public DeviceManager
{
public:
	DeviceManager12() = default;
	~DeviceManager12() final;

protected:
	bool CreateInstanceInternal() final;
	bool CreateDevice() final;
	bool CreateSwapChain() final;

	std::vector<AdapterInfo> EnumerateAdapters();
	HRESULT EnumAdapter(int32_t adapterIdx, DXGI_GPU_PREFERENCE gpuPreference, IDXGIFactory6* dxgiFactory6, IDXGIAdapter** adapter);
	bool SelectAdapterAndCreateDevice();

	void ConfigureInfoQueue();
	bool CreateCommandQueues();

	void ReadCaps();

private:
	D3D_FEATURE_LEVEL m_bestFeatureLevel{ D3D_FEATURE_LEVEL_12_2 };
	D3D_SHADER_MODEL m_bestShaderModel{ D3D_SHADER_MODEL_6_7 };
	std::string m_deviceName{ "Unknown" };

	IntrusivePtr<IDXGIFactory4> m_dxgiFactory;
	IntrusivePtr<IDXGIAdapter> m_adapter;
	IntrusivePtr<ID3D12Device> m_device;
	IntrusivePtr<ID3D12CommandQueue> m_graphicsQueue;
	IntrusivePtr<ID3D12CommandQueue> m_computeQueue;
	IntrusivePtr<ID3D12CommandQueue> m_copyQueue;
	IntrusivePtr<IDXGISwapChain3> m_swapChain;
	bool m_bIsWarpAdapter{ false };
	bool m_bIsTearingSupported{ false };

	IntrusivePtr<ID3D12Fence> m_frameFence;
	std::vector<HANDLE> m_frameFenceEvents;

	std::unique_ptr<DeviceCaps> m_caps;
};

} // namespace Kodiak::DX12