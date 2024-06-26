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

#include "Graphics\CreationParams.h"
#include "Graphics\DX12\DirectXCommon.h"


namespace Kodiak::DX12
{

// Forward declarations
struct DeviceCaps;

struct DxgiRLOHelper
{
	bool doReport{ false };

	DxgiRLOHelper() noexcept = default;
	~DxgiRLOHelper();
};


class DeviceManager : public IDeviceManager, public NonCopyable
{
	IMPLEMENT_IOBJECT

public:
	explicit DeviceManager(const DeviceManagerCreationParams& creationParams);
	~DeviceManager() noexcept final = default;

	void BeginFrame() final;
	void Present() final;

protected:
	void Initialize();
	bool CreateInstance();
	bool CreateDevice();
	bool CreateSwapChain();

	std::vector<AdapterInfo> EnumerateAdapters();
	HRESULT EnumAdapter(int32_t adapterIdx, DXGI_GPU_PREFERENCE gpuPreference, IDXGIFactory6* dxgiFactory6, IDXGIAdapter** adapter);
	
private:
	DeviceManagerCreationParams m_creationParams;
	bool m_bIsDeveloperModeEnabled{ false };
	bool m_bIsRenderDocAvailable{ false };

	DxgiRLOHelper m_dxgiRLOHelper;

	D3D_FEATURE_LEVEL m_bestFeatureLevel{ D3D_FEATURE_LEVEL_12_2 };
	D3D_SHADER_MODEL m_bestShaderModel{ D3D_SHADER_MODEL_6_7 };

	IntrusivePtr<IDXGIFactory4> m_dxgiFactory;

	bool m_bIsWarpAdapter{ false };
	bool m_bIsTearingSupported{ false };

	// Kodiak objects
	DeviceHandle m_device;

	std::unique_ptr<DeviceCaps> m_caps;
};

} // namespace Kodiak::DX12