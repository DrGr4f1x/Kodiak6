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

#include "Graphics\Interfaces.h"
#include "Graphics\DX12\DirectXCommon.h"

namespace Kodiak::DX12
{

// Forward declarations
struct DeviceCaps;


class GraphicsDevice : public IntrusiveCounter<Kodiak::IGraphicsDevice>
{
public:
	GraphicsDevice();
	~GraphicsDevice() final;

	void Initialize(const GraphicsDeviceDesc& desc);

private:
	void ReadCaps();
	HRESULT EnumAdapters(int32_t adapterIdx, DXGI_GPU_PREFERENCE gpuPreference, IDXGIFactory6* dxgiFactory6, IDXGIAdapter** adapter);

private:
	// Device info
	// TODO - Put this stuff in a struct
	GraphicsDeviceDesc m_deviceDesc{};
	D3D_FEATURE_LEVEL m_bestFeatureLevel{ D3D_FEATURE_LEVEL_12_2 };
	D3D_SHADER_MODEL m_bestShaderModel{ D3D_SHADER_MODEL_6_7 };
	std::string m_deviceName{ "Unknown" };

	// DirectX 12 objects
	IntrusivePtr<IDXGIFactory4> m_dxgiFactory;
	IntrusivePtr<IDXGIAdapter> m_adapter;
	IntrusivePtr<ID3D12Device> m_device;
	IntrusivePtr<IDXGISwapChain3> m_swapChain;
	bool m_bIsWarpAdapter{ false };
	bool m_bIsTearingSupported{ false };

	// DirectX caps
	std::unique_ptr<DeviceCaps> m_caps;
};


} // namespace Kodiak::DX12