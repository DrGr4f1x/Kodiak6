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

struct AdapterInfo
{
	std::string name{};
	uint32_t vendorId{ 0 };
	uint32_t deviceId{ 0 };
	uint32_t dedicatedVideoMemory{ 0 };
	uint32_t dedicatedSystemMemory{ 0 };
	uint32_t sharedSystemMemory{ 0 };
	HardwareVendor vendor{ HardwareVendor::Unknown };
	AdapterType adapterType{ AdapterType::Other };

	IntrusivePtr<IDXGIAdapter> adapter;
};


class DeviceManager12 : public DeviceManager
{
public:
	DeviceManager12() = default;
	~DeviceManager12() final = default;

protected:
	bool CreateInstanceInternal() final;
	bool CreateDevice() final;
	bool CreateSwapChain() final;

	std::vector<AdapterInfo> EnumerateAdapters();
	HRESULT EnumAdapter(int32_t adapterIdx, DXGI_GPU_PREFERENCE gpuPreference, IDXGIFactory6* dxgiFactory6, IDXGIAdapter** adapter);

private:
	D3D_FEATURE_LEVEL m_bestFeatureLevel{ D3D_FEATURE_LEVEL_12_2 };
	D3D_SHADER_MODEL m_bestShaderModel{ D3D_SHADER_MODEL_6_7 };
	std::string m_deviceName{ "Unknown" };

	IntrusivePtr<IDXGIFactory4> m_dxgiFactory;
};

} // namespace Kodiak::DX12