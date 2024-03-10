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

namespace Kodiak::DX12
{

static const std::string s_notSupported{ "Not supported" };

inline std::string D3DCommandListSupportFlagsToString(D3D12_COMMAND_LIST_SUPPORT_FLAGS commandListSupportFlags)
{
	const uint32_t numFlags = __popcnt(commandListSupportFlags);

	if (numFlags == 0)
	{
		assert(commandListSupportFlags == D3D12_COMMAND_LIST_SUPPORT_FLAG_NONE);
		return "None";
	}

	static const std::string nameMap[] =
	{
		"None",
		"Direct",
		"Bundle",
		"Compute",
		"Copy",
		"Video Decode",
		"Video Process",
		"Video Encode"
	};

	std::string result;
	uint32_t testBit = 0;
	uint32_t bitsCounted = 0;
	for (uint32_t i = 1; i < _countof(nameMap); ++i)
	{
		if ((commandListSupportFlags & testBit) == testBit)
		{
			++bitsCounted;
			result += nameMap[i];
			if (bitsCounted != numFlags)
			{
				result += ", ";
			}
		}
		testBit = (1 << i);
	}

	return result;
}

inline std::string D3DConservativeRasterizationTierToString(D3D12_CONSERVATIVE_RASTERIZATION_TIER conservativeRasterizationTier, bool bNumberOnly = false)
{
	switch (conservativeRasterizationTier)
	{
	case D3D12_CONSERVATIVE_RASTERIZATION_TIER_1: return bNumberOnly ? "1" : "Tier 1"; break;
	case D3D12_CONSERVATIVE_RASTERIZATION_TIER_2: return bNumberOnly ? "2" : "Tier 2"; break;
	case D3D12_CONSERVATIVE_RASTERIZATION_TIER_3: return bNumberOnly ? "3" : "Tier 3"; break;
	default: return s_notSupported; break;
	}
}


inline std::string D3DCrossNodeSharingTierToString(D3D12_CROSS_NODE_SHARING_TIER crossNodeSharingTier, bool bNumberOnly = false)
{
	switch (crossNodeSharingTier)
	{
	case D3D12_CROSS_NODE_SHARING_TIER_1_EMULATED: return bNumberOnly ? "1 Emulated" : "Tier 1 Emulated"; break;
	case D3D12_CROSS_NODE_SHARING_TIER_1: return bNumberOnly ? "1" : "Tier 1"; break;
	case D3D12_CROSS_NODE_SHARING_TIER_2: return bNumberOnly ? "2" : "Tier 2"; break;
	case D3D12_CROSS_NODE_SHARING_TIER_3: return bNumberOnly ? "3" : "Tier 3";
	default: return s_notSupported; break;
	}
}


inline std::string D3DFeatureLevelToString(D3D_FEATURE_LEVEL featureLevel, bool bNumberOnly = false)
{
	switch (featureLevel)
	{
	case D3D_FEATURE_LEVEL_9_1:		return bNumberOnly ? "9.1" : "D3D_FEATURE_LEVEL_9_1"; break;
	case D3D_FEATURE_LEVEL_9_2:		return bNumberOnly ? "9.2" : "D3D_FEATURE_LEVEL_9_2"; break;
	case D3D_FEATURE_LEVEL_9_3:		return bNumberOnly ? "9.3" : "D3D_FEATURE_LEVEL_9_3"; break;
	case D3D_FEATURE_LEVEL_10_0:	return bNumberOnly ? "10.0" : "D3D_FEATURE_LEVEL_10_0"; break;
	case D3D_FEATURE_LEVEL_10_1:	return bNumberOnly ? "10.1" : "D3D_FEATURE_LEVEL_10_1"; break;
	case D3D_FEATURE_LEVEL_11_0:	return bNumberOnly ? "11.0" : "D3D_FEATURE_LEVEL_11_0"; break;
	case D3D_FEATURE_LEVEL_11_1:	return bNumberOnly ? "11.1" :"D3D_FEATURE_LEVEL_11_1"; break;
	case D3D_FEATURE_LEVEL_12_0:	return bNumberOnly ? "12.0" : "D3D_FEATURE_LEVEL_12_0"; break;
	case D3D_FEATURE_LEVEL_12_1:	return bNumberOnly ? "12.1" : "D3D_FEATURE_LEVEL_12_1"; break;
	case D3D_FEATURE_LEVEL_12_2:	return bNumberOnly ? "12.2" : "D3D_FEATURE_LEVEL_12_2"; break;
	default: return bNumberOnly ? "1.0 Core" : "D3D_FEATURE_LEVEL_1_0_CORE"; break;
	}
}


inline std::string D3DMEshShaderTierToString(D3D12_MESH_SHADER_TIER meshShaderTier, bool bNumberOnly = false)
{
	return (meshShaderTier == D3D12_MESH_SHADER_TIER_1) ? (bNumberOnly ? "1" : "Tier 1") : s_notSupported;
}


inline std::string D3DProgrammableSamplePositionsTierToString(D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER programmableSamplePositionsTier, bool bNumberOnly = false)
{
	switch (programmableSamplePositionsTier)
	{
	case D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER_1: return bNumberOnly ? "1" : "Tier 1"; break;
	case D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER_2: return bNumberOnly ? "2" : "Tier 2"; break;
	default: return s_notSupported; break;
	}
}


inline std::string D3DRayTracingTierToString(D3D12_RAYTRACING_TIER raytracingTier, bool bNumberOnly = false)
{
	switch (raytracingTier)
	{
	case D3D12_RAYTRACING_TIER_1_0: return bNumberOnly ? "1.0" : "Tier 1.0"; break;
	case D3D12_RAYTRACING_TIER_1_1: return bNumberOnly ? "1.1" : "Tier 1.1"; break;
	default: return s_notSupported; break;
	}
}

inline std::string D3DRenderPassTierToString(D3D12_RENDER_PASS_TIER renderPassTier, bool bNumberOnly = false)
{
	switch (renderPassTier)
	{
	case D3D12_RENDER_PASS_TIER_1: return bNumberOnly ? "1" : "Tier 1"; break;
	case D3D12_RENDER_PASS_TIER_2: return bNumberOnly ? "2" : "Tier 2"; break;
	default: return bNumberOnly ? "0" : "Tier 0"; break;
	}
}

inline std::string D3DResourceBindingTierToString(D3D12_RESOURCE_BINDING_TIER resourceBindingTier, bool bNumberOnly = false)
{
	switch (resourceBindingTier)
	{
	case D3D12_RESOURCE_BINDING_TIER_2: return bNumberOnly ? "2" : "Tier 2"; break;
	case D3D12_RESOURCE_BINDING_TIER_3: return bNumberOnly ? "3" : "Tier 3"; break;
	default: return bNumberOnly ? "1" : "Tier 1"; break;
	}
}


inline std::string D3DResourceHeapTierToString(D3D12_RESOURCE_HEAP_TIER resourceHeapTier, bool bNumberOnly = false)
{
	return resourceHeapTier == D3D12_RESOURCE_HEAP_TIER_1 ? (bNumberOnly ? "1" : "Tier 1")	: (bNumberOnly ? "2" : "Tier 2");
}


inline std::string D3DSamplerFeedbackTierToString(D3D12_SAMPLER_FEEDBACK_TIER samplerFeedbackTier, bool bNumberOnly = false)
{
	switch (samplerFeedbackTier)
	{
	case D3D12_SAMPLER_FEEDBACK_TIER_0_9: return bNumberOnly ? "0.9" : "Tier 0.9"; break;
	case D3D12_SAMPLER_FEEDBACK_TIER_1_0: return bNumberOnly ? "1.0" : "Tier 1.0"; break;
	default: return s_notSupported;
	}
}

inline std::string D3DShaderMinPrecisionSupportToString(D3D12_SHADER_MIN_PRECISION_SUPPORT shaderMinPrecisionSupport)
{
	if (shaderMinPrecisionSupport == D3D12_SHADER_MIN_PRECISION_SUPPORT_10_BIT)
	{
		return "10-bit";
	}
	else if (shaderMinPrecisionSupport == D3D12_SHADER_MIN_PRECISION_SUPPORT_16_BIT)
	{
		return "16-bit";
	}
	else if (shaderMinPrecisionSupport == (D3D12_SHADER_MIN_PRECISION_SUPPORT_10_BIT | D3D12_SHADER_MIN_PRECISION_SUPPORT_16_BIT))
	{
		return "10-bit, 16-bit";
	}
	else
	{
		return "None";
	}
}


inline std::string D3DShaderModelToString(D3D_SHADER_MODEL shaderModel, bool bNumberOnly = false)
{
	switch (shaderModel)
	{
	case D3D_SHADER_MODEL_6_0: return bNumberOnly ? "6.0" : "D3D_SHADER_MODEL_6_0"; break;
	case D3D_SHADER_MODEL_6_1: return bNumberOnly ? "6.1" : "D3D_SHADER_MODEL_6_1"; break;
	case D3D_SHADER_MODEL_6_2: return bNumberOnly ? "6.2" : "D3D_SHADER_MODEL_6_2"; break;
	case D3D_SHADER_MODEL_6_3: return bNumberOnly ? "6.3" : "D3D_SHADER_MODEL_6_3"; break;
	case D3D_SHADER_MODEL_6_4: return bNumberOnly ? "6.4" : "D3D_SHADER_MODEL_6_4"; break;
	case D3D_SHADER_MODEL_6_5: return bNumberOnly ? "6.5" : "D3D_SHADER_MODEL_6_5"; break;
	case D3D_SHADER_MODEL_6_6: return bNumberOnly ? "6.6" : "D3D_SHADER_MODEL_6_6"; break;
	case D3D_SHADER_MODEL_6_7: return bNumberOnly ? "6.7" : "D3D_SHADER_MODEL_6_7"; break;
	default: return bNumberOnly ? "5.1" : "D3D_SHADER_MODEL_5_1"; break;
	}
}


inline std::string D3DSharedResourceCompatilityTierToString(D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER sharedResourceCompatilityTier, bool bNumberOnly = false)
{
	switch (sharedResourceCompatilityTier)
	{
	case D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_1: return bNumberOnly ? "1" : "Tier1"; break;
	case D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_2: return bNumberOnly ? "2" : "Tier 2"; break;
	default: return bNumberOnly ? "0" : "Tier 0"; break;
	}
}

inline std::string D3DTiledResourcesTierToString(D3D12_TILED_RESOURCES_TIER tiledResourcesTier, bool bNumberOnly = false)
{
	switch (tiledResourcesTier)
	{
	case D3D12_TILED_RESOURCES_TIER_1: return bNumberOnly ? "1" : "Tier 1"; break;
	case D3D12_TILED_RESOURCES_TIER_2: return bNumberOnly ? "2" : "Tier 2"; break;
	case D3D12_TILED_RESOURCES_TIER_3: return bNumberOnly ? "3" : "Tier 3"; break;
	case D3D12_TILED_RESOURCES_TIER_4: return bNumberOnly ? "4" : "Tier 4"; break;
	default: return s_notSupported; break;
	}
}


inline std::string D3DTriStateToString(D3D12_TRI_STATE triState)
{
	switch (triState)
	{
	case D3D12_TRI_STATE_FALSE: return "false"; break;
	case D3D12_TRI_STATE_TRUE: return "true"; break;
	default: return "unknown"; break;
	}
}


inline std::string D3DVariableShadingRateTierToString(D3D12_VARIABLE_SHADING_RATE_TIER variableShadingRateTier, bool bNumberOnly = false)
{
	switch (variableShadingRateTier)
	{
	case D3D12_VARIABLE_SHADING_RATE_TIER_1: return bNumberOnly ? "1" : "Tier 1"; break;
	case D3D12_VARIABLE_SHADING_RATE_TIER_2: return bNumberOnly ? "2" : "Tier 2"; break;
	default: return s_notSupported;
	}
}


inline std::string D3DViewInstancingTierToString(D3D12_VIEW_INSTANCING_TIER viewInstancingTier, bool bNumberOnly = false)
{
	switch (viewInstancingTier)
	{
	case D3D12_VIEW_INSTANCING_TIER_1: return bNumberOnly ? "1" : "Tier 1"; break;
	case D3D12_VIEW_INSTANCING_TIER_2: return bNumberOnly ? "2" : "Tier 2"; break;
	case D3D12_VIEW_INSTANCING_TIER_3: return bNumberOnly ? "3" : "Tier 3"; break;
	default: return s_notSupported;
	}
}


inline std::string D3DWaveMmaTierToString(D3D12_WAVE_MMA_TIER waveMmaTier, bool bNumberOnly = false)
{
	return (waveMmaTier == D3D12_WAVE_MMA_TIER_1_0) ? (bNumberOnly ? "1.0" : "Tier 1.0") : s_notSupported;
}


template <typename T> inline std::string D3DTypeToString(T value, bool bNumberOnly = false)
{
	return std::format("{}", value);
}


template <> inline std::string D3DTypeToString(D3D12_COMMAND_LIST_SUPPORT_FLAGS value, bool bNumberOnly)
{
	return D3DCommandListSupportFlagsToString(value);
}


template <> inline std::string D3DTypeToString(D3D12_CONSERVATIVE_RASTERIZATION_TIER value, bool bNumberOnly)
{
	return D3DConservativeRasterizationTierToString(value, bNumberOnly);
}


template <> inline std::string D3DTypeToString(D3D12_CROSS_NODE_SHARING_TIER value, bool bNumberOnly)
{
	return D3DCrossNodeSharingTierToString(value, bNumberOnly);
}


template <> inline std::string D3DTypeToString(D3D_FEATURE_LEVEL value, bool bNumberOnly)
{
	return D3DFeatureLevelToString(value, bNumberOnly);
}


template <> inline std::string D3DTypeToString(D3D12_MESH_SHADER_TIER value, bool bNumberOnly)
{
	return D3DMEshShaderTierToString(value, bNumberOnly);
}


template <> inline std::string D3DTypeToString(D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER value, bool bNumberOnly)
{
	return D3DProgrammableSamplePositionsTierToString(value, bNumberOnly);
}


template <> inline std::string D3DTypeToString(D3D12_RAYTRACING_TIER value, bool bNumberOnly)
{
	return D3DRayTracingTierToString(value, bNumberOnly);
}


template <> inline std::string D3DTypeToString(D3D12_RENDER_PASS_TIER value, bool bNumberOnly)
{
	return D3DRenderPassTierToString(value, bNumberOnly);
}


template <> inline std::string D3DTypeToString(D3D12_RESOURCE_BINDING_TIER value, bool bNumberOnly)
{
	return D3DResourceBindingTierToString(value, bNumberOnly);
}


template <> inline std::string D3DTypeToString(D3D12_RESOURCE_HEAP_TIER value, bool bNumberOnly)
{
	return D3DResourceHeapTierToString(value, bNumberOnly);
}


template <> inline std::string D3DTypeToString(D3D12_SAMPLER_FEEDBACK_TIER value, bool bNumberOnly)
{
	return D3DSamplerFeedbackTierToString(value, bNumberOnly);
}


template <> inline std::string D3DTypeToString(D3D12_SHADER_MIN_PRECISION_SUPPORT value, bool bNumberOnly)
{
	return D3DShaderMinPrecisionSupportToString(value);
}


template <> inline std::string D3DTypeToString(D3D_SHADER_MODEL value, bool bNumberOnly)
{
	return D3DShaderModelToString(value, bNumberOnly);
}


template <> inline std::string D3DTypeToString(D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER value, bool bNumberOnly)
{
	return D3DSharedResourceCompatilityTierToString(value, bNumberOnly);
}


template <> inline std::string D3DTypeToString(D3D12_TILED_RESOURCES_TIER value, bool bNumberOnly)
{
	return D3DTiledResourcesTierToString(value, bNumberOnly);
}


template <> inline std::string D3DTypeToString(D3D12_TRI_STATE value, bool bNumberOnly)
{
	return D3DTriStateToString(value);
}


template <> inline std::string D3DTypeToString(D3D12_VARIABLE_SHADING_RATE_TIER value, bool bNumberOnly)
{
	return D3DVariableShadingRateTierToString(value, bNumberOnly);
}


template <> inline std::string D3DTypeToString(D3D12_VIEW_INSTANCING_TIER value, bool bNumberOnly)
{
	return D3DViewInstancingTierToString(value, bNumberOnly);
}


template <> inline std::string D3DTypeToString(D3D12_WAVE_MMA_TIER value, bool bNumberOnly)
{
	return D3DWaveMmaTierToString(value, bNumberOnly);
}

} // namespace Kodiak::DX12