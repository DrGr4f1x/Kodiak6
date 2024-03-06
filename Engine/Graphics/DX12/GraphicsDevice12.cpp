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

#include "GraphicsDevice12.h"

using namespace Kodiak;
using namespace Kodiak::DX12;
using namespace std;


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


string D3DFeatureLevelToString(D3D_FEATURE_LEVEL featureLevel)
{
	switch (featureLevel)
	{
	case D3D_FEATURE_LEVEL_1_0_CORE:	return "D3D_FEATURE_LEVEL_1_0_CORE"; break;
	case D3D_FEATURE_LEVEL_9_1:			return "D3D_FEATURE_LEVEL_9_1"; break;
	case D3D_FEATURE_LEVEL_9_2:			return "D3D_FEATURE_LEVEL_9_2"; break;
	case D3D_FEATURE_LEVEL_9_3:			return "D3D_FEATURE_LEVEL_9_3"; break;
	case D3D_FEATURE_LEVEL_10_0:		return "D3D_FEATURE_LEVEL_10_0"; break;
	case D3D_FEATURE_LEVEL_10_1:		return "D3D_FEATURE_LEVEL_10_1"; break;
	case D3D_FEATURE_LEVEL_11_0:		return "D3D_FEATURE_LEVEL_11_0"; break;
	case D3D_FEATURE_LEVEL_11_1:		return "D3D_FEATURE_LEVEL_11_1"; break;
	case D3D_FEATURE_LEVEL_12_0:		return "D3D_FEATURE_LEVEL_12_0"; break;
	case D3D_FEATURE_LEVEL_12_1:		return "D3D_FEATURE_LEVEL_12_1"; break;
	case D3D_FEATURE_LEVEL_12_2:		return "D3D_FEATURE_LEVEL_12_0"; break;
	default:							return "D3D_FEATURE_LEVEL_1_0_CORE"; break;
	}
}


string D3DShaderModelToString(D3D_SHADER_MODEL shaderModel)
{
	switch (shaderModel)
	{
	case D3D_SHADER_MODEL_5_1:		return "D3D_SHADER_MODEL_5_1"; break;
	case D3D_SHADER_MODEL_6_0:		return "D3D_SHADER_MODEL_6_0"; break;
	case D3D_SHADER_MODEL_6_1:		return "D3D_SHADER_MODEL_6_1"; break;
	case D3D_SHADER_MODEL_6_2:		return "D3D_SHADER_MODEL_6_2"; break;
	case D3D_SHADER_MODEL_6_3:		return "D3D_SHADER_MODEL_6_3"; break;
	case D3D_SHADER_MODEL_6_4:		return "D3D_SHADER_MODEL_6_4"; break;
	case D3D_SHADER_MODEL_6_5:		return "D3D_SHADER_MODEL_6_5"; break;
	case D3D_SHADER_MODEL_6_6:		return "D3D_SHADER_MODEL_6_6"; break;
	case D3D_SHADER_MODEL_6_7:		return "D3D_SHADER_MODEL_6_7"; break;
	default:						return "D3D_SHADER_MODEL_5_1"; break;
	}
	
}

} // anonymous namespace


GraphicsDevice::GraphicsDevice()
{
	LOG_INFO << "Creating DirectX 12 device";
}


GraphicsDevice::~GraphicsDevice()
{
	LOG_INFO << "Destroying DirectX 12 device";

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
		LOG_WARNING << "  Unable to enable D3D12 debug validation layer";
	}
#endif

	const bool bIsDeveloperModeEnabled = IsDeveloperModeEnabled();
	const bool bIsRenderDocAvailable = IsRenderDocAvailable();

	if (bIsDeveloperModeEnabled && !bIsRenderDocAvailable)
	{
		D3D12EnableExperimentalFeatures(1, &D3D12ExperimentalShaderModels, nullptr, nullptr);
	}

	// Obtain the DXGI factory
	assert_succeeded(CreateDXGIFactory2(0, IID_PPV_ARGS(&m_dxgiFactory)));

	// Create the D3D graphics device
	Microsoft::WRL::ComPtr<IDXGIAdapter1> pAdapter;

	static const bool bUseWarpDriver = false;

	Microsoft::WRL::ComPtr<ID3D12Device> pDevice;

	if (!bUseWarpDriver)
	{
		size_t maxSize = 0;

		for (uint32_t idx = 0; DXGI_ERROR_NOT_FOUND != m_dxgiFactory->EnumAdapters1(idx, &pAdapter); ++idx)
		{
			DXGI_ADAPTER_DESC1 desc;
			pAdapter->GetDesc1(&desc);
			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
				continue;

			D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_12_2, D3D_FEATURE_LEVEL_12_1, D3D_FEATURE_LEVEL_12_0 };

			for (int i = 0; i < _countof(featureLevels); ++i)
			{
				if (desc.DedicatedVideoMemory > maxSize && SUCCEEDED(D3D12CreateDevice(pAdapter.Get(), featureLevels[i], IID_PPV_ARGS(&pDevice))))
				{
					maxSize = desc.DedicatedVideoMemory;
					m_bestFeatureLevel = featureLevels[i];
					m_deviceName = MakeStr(desc.Description);

					LOG_INFO << "  D3D12-capable hardware found:  " << m_deviceName << " (" << (maxSize >> 20) << ")";

					break;
				}
			}
		}

		if (maxSize > 0)
		{
			m_device = pDevice;

			ReadCaps();

			LOG_INFO << "  Selected adapter: " << m_deviceName << " (" << (maxSize >> 20) << ")";
			LOG_INFO << "    Feature Level: " << D3DFeatureLevelToString(m_bestFeatureLevel);
			LOG_INFO << "    Shader Model:  " << D3DShaderModelToString(m_bestShaderModel);
		}
	}

	if (!m_device)
	{
		if (bUseWarpDriver)
		{
			LOG_NOTICE << "WARP software adapter requested.  Initializing...";
		}
		else
		{
			LOG_WARNING << "Failed to find a hardware adapter.  Falling back to WARP.\n";
		}

		assert_succeeded(m_dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&pAdapter)));
		assert_succeeded(D3D12CreateDevice(pAdapter.Get(), m_bestFeatureLevel, IID_PPV_ARGS(&pDevice)));
		m_device = pDevice;

		ReadCaps();

		LOG_INFO << "  Selected WARP software adapter";
		LOG_INFO << "    Feature Level: " << D3DFeatureLevelToString(m_bestFeatureLevel);
		LOG_INFO << "    Shader Model:  " << D3DShaderModelToString(m_bestShaderModel);
	}
#ifndef _RELEASE
	else
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
	if (m_capsRead)
	{
		return;
	}


	m_dataShaderModel.HighestShaderModel = m_bestShaderModel;
	m_device->CheckFeatureSupport(D3D12_FEATURE_SHADER_MODEL, &m_dataShaderModel, sizeof(m_dataShaderModel));
	m_bestShaderModel = m_dataShaderModel.HighestShaderModel;

	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_12_2, D3D_FEATURE_LEVEL_12_1, D3D_FEATURE_LEVEL_12_0 };
	D3D12_FEATURE_DATA_FEATURE_LEVELS d3dLevels = {};
	d3dLevels.NumFeatureLevels = _countof(featureLevels);
	d3dLevels.pFeatureLevelsRequested = featureLevels;
	d3dLevels.MaxSupportedFeatureLevel = D3D_FEATURE_LEVEL_12_2;
	m_device->CheckFeatureSupport(D3D12_FEATURE_FEATURE_LEVELS, &d3dLevels, sizeof(d3dLevels));
	m_bestFeatureLevel = d3dLevels.MaxSupportedFeatureLevel;

	bool hasOptions = SUCCEEDED(m_device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS, &m_dataOptions, sizeof(m_dataOptions)));
	bool hasOptions1 = SUCCEEDED(m_device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS1, &m_dataOptions1, sizeof(m_dataOptions1)));
	bool hasOptions2 = SUCCEEDED(m_device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS2, &m_dataOptions2, sizeof(m_dataOptions2)));
	bool hasOptions3 = SUCCEEDED(m_device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS3, &m_dataOptions3, sizeof(m_dataOptions3)));
	bool hasOptions4 = SUCCEEDED(m_device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS4, &m_dataOptions4, sizeof(m_dataOptions4)));
	bool hasOptions5 = SUCCEEDED(m_device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &m_dataOptions5, sizeof(m_dataOptions5)));
	bool hasOptions6 = SUCCEEDED(m_device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS6, &m_dataOptions6, sizeof(m_dataOptions6)));

	m_capsRead = true;
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