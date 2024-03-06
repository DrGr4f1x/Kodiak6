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

namespace Kodiak::DX12
{

class GraphicsDevice : public TRefCount<Kodiak::IGraphicsDevice>
{
public:
	GraphicsDevice();
	~GraphicsDevice() final;

	void Initialize(const GraphicsDeviceDesc& desc);

private:
	void ReadCaps();

private:
	// Device info
	GraphicsDeviceDesc m_deviceDesc;
	D3D_FEATURE_LEVEL m_bestFeatureLevel{ D3D_FEATURE_LEVEL_11_0 };
	D3D_SHADER_MODEL m_bestShaderModel{ D3D_SHADER_MODEL_6_5 };
	std::string m_deviceName{ "Unknown" };

	// DirectX 12 objects
	Microsoft::WRL::ComPtr<IDXGIFactory4> m_dxgiFactory;
	Microsoft::WRL::ComPtr<ID3D12Device> m_device;
	Microsoft::WRL::ComPtr<IDXGISwapChain3> m_swapChain;

	// DirectX caps
	bool m_capsRead{ false };
	D3D12_FEATURE_DATA_SHADER_MODEL m_dataShaderModel;
	D3D12_FEATURE_DATA_D3D12_OPTIONS m_dataOptions;
	D3D12_FEATURE_DATA_D3D12_OPTIONS1 m_dataOptions1;
	D3D12_FEATURE_DATA_D3D12_OPTIONS2 m_dataOptions2;
	D3D12_FEATURE_DATA_D3D12_OPTIONS3 m_dataOptions3;
	D3D12_FEATURE_DATA_D3D12_OPTIONS4 m_dataOptions4;
	D3D12_FEATURE_DATA_D3D12_OPTIONS5 m_dataOptions5;
	D3D12_FEATURE_DATA_D3D12_OPTIONS6 m_dataOptions6;
};

using DeviceHandle = Microsoft::WRL::ComPtr<Kodiak::DX12::GraphicsDevice>;

Kodiak::DX12::GraphicsDevice* CreateDevice12(const GraphicsDeviceDesc& desc);

ID3D12Device* GetDevice();

} // namespace Kodiak::DX12