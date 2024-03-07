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

#include "DeviceCaps12.h"

#include "Strings12.h"

#include <format>


using namespace Kodiak;
using namespace Kodiak::DX12;
using namespace std;


void DeviceCaps::ReadBasicCaps(ID3D12Device* device, D3D_FEATURE_LEVEL minFeatureLevel)
{
	if (!m_basicCapsRead)
	{
		basicCaps.maxFeatureLevel = GetHighestFeatureLevel(device, minFeatureLevel);
		basicCaps.maxShaderModel = GetHighestShaderModel(device);

		D3D12_FEATURE_DATA_D3D12_OPTIONS dx12Caps{};
		device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS, &dx12Caps, sizeof(dx12Caps));
		basicCaps.resourceBindingTier = dx12Caps.ResourceBindingTier;
		basicCaps.resourceHeapTier = dx12Caps.ResourceHeapTier;

		basicCaps.numDeviceNodes = device->GetNodeCount();

		D3D12_FEATURE_DATA_D3D12_OPTIONS1 dx12Caps1{};
		device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS1, &dx12Caps1, sizeof(dx12Caps1));
		basicCaps.bSupportsWaveOps = dx12Caps1.WaveOps == TRUE;

		D3D12_FEATURE_DATA_D3D12_OPTIONS9 dx12Caps9{};
		device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS9, &dx12Caps9, sizeof(dx12Caps9));
		basicCaps.bSupportsAtomic64 = dx12Caps9.AtomicInt64OnTypedResourceSupported == TRUE;

		m_basicCapsRead = true;
	}
}


void DeviceCaps::ReadFullCaps(ID3D12Device* device, D3D_FEATURE_LEVEL minFeatureLevel, D3D_SHADER_MODEL bestShaderModel)
{
	ReadBasicCaps(device, minFeatureLevel);

	if (!m_capsRead)
	{
		shaderModel.HighestShaderModel = bestShaderModel;
		device->CheckFeatureSupport(D3D12_FEATURE_SHADER_MODEL, &shaderModel, sizeof(shaderModel));

		m_validCaps[0] = SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS, &caps, sizeof(caps)));
		m_validCaps[1] = SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS1, &caps1, sizeof(caps1)));
		m_validCaps[2] = SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS2, &caps2, sizeof(caps2)));
		m_validCaps[3] = SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS3, &caps3, sizeof(caps3)));
		m_validCaps[4] = SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS4, &caps4, sizeof(caps4)));
		m_validCaps[5] = SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &caps5, sizeof(caps5)));
		m_validCaps[6] = SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS6, &caps6, sizeof(caps6)));
		m_validCaps[7] = SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS7, &caps7, sizeof(caps7)));
		m_validCaps[8] = SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS8, &caps8, sizeof(caps8)));
		m_validCaps[9] = SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS9, &caps9, sizeof(caps9)));
		m_validCaps[10] = SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS10, &caps10, sizeof(caps10)));
		m_validCaps[11] = SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS11, &caps11, sizeof(caps11)));
		m_validCaps[12] = SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS12, &caps12, sizeof(caps12)));
		m_validCaps[13] = SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS13, &caps13, sizeof(caps13)));

		m_capsRead = true;
	}
}


bool DeviceCaps::HasCaps(int32_t capsNum) const
{
	assert(capsNum >= 0 && capsNum < m_validCaps.size());
	return m_validCaps[capsNum];
}


void DeviceCaps::LogCaps()
{
	LOG_INFO << "  Device Caps";

	LOG_INFO << format("    {:50} {}", "Highest supported shader model:", D3DShaderModelToString(shaderModel.HighestShaderModel));

	constexpr const char* formatStr = "      {:48} {}";

	if (HasCaps(0))
	{
		LOG_INFO << "    D3D12_FEATURE_D3D12_OPTIONS";
		LOG_INFO << format(formatStr, "DoublePrecisionFloatShaderOps:", caps.DoublePrecisionFloatShaderOps == TRUE);
		LOG_INFO << format(formatStr, "OutputMergerLogicOp:", caps.OutputMergerLogicOp == TRUE);
		LOG_INFO << format(formatStr, "MinPrecisionSupport:", D3DShaderMinPrecisionSupportToString(caps.MinPrecisionSupport));
		LOG_INFO << format(formatStr, "TiledResourcesTier:", D3DTiledResourcesTierToString(caps.TiledResourcesTier));
		LOG_INFO << format(formatStr, "PSSpecifiedStencilRefSupported:", caps.PSSpecifiedStencilRefSupported == TRUE);
		LOG_INFO << format(formatStr, "TypedUAVLoadAdditionalFormats:", caps.TypedUAVLoadAdditionalFormats == TRUE);
		LOG_INFO << format(formatStr, "ROVsSupported:", caps.ROVsSupported == TRUE);
		LOG_INFO << format(formatStr, "ConservativeRasterizationTier:", D3DConservativeRasterizationTierToString(caps.ConservativeRasterizationTier));
		LOG_INFO << format(formatStr, "MaxGPUVirtualAddressBitsPerResource:", caps.MaxGPUVirtualAddressBitsPerResource);
		LOG_INFO << format(formatStr, "StandardSwizzle64KBSupported:", caps.StandardSwizzle64KBSupported == TRUE);
		LOG_INFO << format(formatStr, "CrossNodeSharingTier:", D3DCrossNodeSharingTierToString(caps.CrossNodeSharingTier));
		LOG_INFO << format(formatStr, "CrossAdapterRowMajorTextureSupported:", caps.CrossAdapterRowMajorTextureSupported == TRUE);
		LOG_INFO << format("      {} {}", "VPAndRTArrayIndexFromAnyShaderFeedingRasterizerSupportedWithoutGSEmulation:", caps.VPAndRTArrayIndexFromAnyShaderFeedingRasterizerSupportedWithoutGSEmulation == TRUE);
		LOG_INFO << format(formatStr, "ResourceHeapTier:", D3DResourceHeapTierToString(caps.ResourceHeapTier));
	}

	if (HasCaps(1))
	{
		LOG_INFO << "    D3D12_FEATURE_D3D12_OPTIONS1";
		LOG_INFO << format(formatStr, "WaveOps:", caps1.WaveOps == TRUE);
		LOG_INFO << format(formatStr, "WaveLaneCountMin:", caps1.WaveLaneCountMin);
		LOG_INFO << format(formatStr, "WaveLaneCountMax:", caps1.WaveLaneCountMax);
		LOG_INFO << format(formatStr, "TotalLaneCount:", caps1.TotalLaneCount);
		LOG_INFO << format(formatStr, "ExpandedComputeResourceState:", caps1.ExpandedComputeResourceStates == TRUE);
		LOG_INFO << format(formatStr, "Int64ShaderOps:", caps1.Int64ShaderOps);
	}

	if (HasCaps(2))
	{
		LOG_INFO << "    D3D12_FEATURE_D3D12_OPTIONS2";
		LOG_INFO << format(formatStr, "DepthBoundsTestSupported:", caps2.DepthBoundsTestSupported == TRUE);
		LOG_INFO << format(formatStr, "ProgrammableSamplePositionsTier:", D3DProgrammableSamplePositionsTierToString(caps2.ProgrammableSamplePositionsTier));
	}

	if (HasCaps(3))
	{
		LOG_INFO << "    D3D12_FEATURE_D3D12_OPTIONS3";
		LOG_INFO << format(formatStr, "CopyQueueTimestampQueriesSupported:", caps3.CopyQueueTimestampQueriesSupported == TRUE);
		LOG_INFO << format(formatStr, "CastingFullyTypedFormatSupported:", caps3.CastingFullyTypedFormatSupported == TRUE);
		LOG_INFO << format(formatStr, "WriteBufferImmediateSupportFlags:", D3DCommandListSupportFlagsToString(caps3.WriteBufferImmediateSupportFlags));
		LOG_INFO << format(formatStr, "ViewInstancingTier:", D3DViewInstancingTierToString(caps3.ViewInstancingTier));
		LOG_INFO << format(formatStr, "BarycentricsSupported:", caps3.BarycentricsSupported == TRUE);
	}
}


D3D_FEATURE_LEVEL DeviceCaps::GetHighestFeatureLevel(ID3D12Device* device, D3D_FEATURE_LEVEL minFeatureLevel)
{
	const D3D_FEATURE_LEVEL featureLevels[]
	{
		D3D_FEATURE_LEVEL_12_2,
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};

	D3D12_FEATURE_DATA_FEATURE_LEVELS featureLevelCaps{};
	featureLevelCaps.pFeatureLevelsRequested = featureLevels;
	featureLevelCaps.NumFeatureLevels = _countof(featureLevels);

	if (SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_FEATURE_LEVELS, &featureLevelCaps, sizeof(featureLevelCaps))))
	{
		return featureLevelCaps.MaxSupportedFeatureLevel;
	}

	return minFeatureLevel;
}


D3D_SHADER_MODEL DeviceCaps::GetHighestShaderModel(ID3D12Device* device)
{
	const D3D_SHADER_MODEL shaderModels[]
	{
		D3D_SHADER_MODEL_6_7,
		D3D_SHADER_MODEL_6_6,
		D3D_SHADER_MODEL_6_5,
		D3D_SHADER_MODEL_6_4,
		D3D_SHADER_MODEL_6_3,
		D3D_SHADER_MODEL_6_2,
		D3D_SHADER_MODEL_6_1,
		D3D_SHADER_MODEL_6_0,
	};

	D3D12_FEATURE_DATA_SHADER_MODEL featureShaderModel{};
	for (const auto shaderModel : shaderModels)
	{
		featureShaderModel.HighestShaderModel = shaderModel;
		if (SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_SHADER_MODEL, &featureShaderModel, sizeof(featureShaderModel))))
		{
			return featureShaderModel.HighestShaderModel;
		}
	}

	return D3D_SHADER_MODEL_5_1;
}