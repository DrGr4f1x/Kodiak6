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

#include "Graphics\GraphicsDevice.h"

#include "DeviceCaps12.h"


namespace Kodiak::DX12
{

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
	GraphicsDeviceDesc m_deviceDesc{};
	D3D_FEATURE_LEVEL m_bestFeatureLevel{ D3D_FEATURE_LEVEL_12_2 };
	D3D_SHADER_MODEL m_bestShaderModel{ D3D_SHADER_MODEL_6_7 };
	std::string m_deviceName{ "Unknown" };

	// DirectX 12 objects
	Microsoft::WRL::ComPtr<IDXGIFactory4> m_dxgiFactory;
	Microsoft::WRL::ComPtr<IDXGIAdapter> m_adapter;
	Microsoft::WRL::ComPtr<ID3D12Device> m_device;
	Microsoft::WRL::ComPtr<IDXGISwapChain3> m_swapChain;
	bool m_bIsWarpAdapter{ false };

	// DirectX caps
	DeviceCaps m_caps;
};

using DeviceHandle = IntrusivePtr<GraphicsDevice>;

Kodiak::DX12::GraphicsDevice* CreateDevice12(const GraphicsDeviceDesc& desc);

ID3D12Device* GetDevice();

inline LogCategory LogDirectX{ "LogDirectX" };

} // namespace Kodiak::DX12