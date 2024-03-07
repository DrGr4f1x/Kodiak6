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

inline std::string D3DConservativeRasterizationTierToString(D3D12_CONSERVATIVE_RASTERIZATION_TIER conservativeRasterizationTier, bool bNumberOnly = false)
{
	switch (conservativeRasterizationTier)
	{
	case D3D12_CONSERVATIVE_RASTERIZATION_TIER_1: return bNumberOnly ? "1" : "Tier 1"; break;
	case D3D12_CONSERVATIVE_RASTERIZATION_TIER_2: return bNumberOnly ? "2" : "Tier 2"; break;
	case D3D12_CONSERVATIVE_RASTERIZATION_TIER_3: return bNumberOnly ? "3" : "Tier 3"; break;
	default: return "Not supported"; break;
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
	default: return "Not supported"; break;
	}
}


inline std::string D3DFeatureLevelToString(D3D_FEATURE_LEVEL featureLevel)
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
	case D3D_FEATURE_LEVEL_12_2:		return "D3D_FEATURE_LEVEL_12_2"; break;
	default:							return "D3D_FEATURE_LEVEL_1_0_CORE"; break;
	}
}


inline std::string D3DResouceBindingTierToString(D3D12_RESOURCE_BINDING_TIER resourceBindingTier, bool bNumberOnly = false)
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
	return resourceHeapTier == D3D12_RESOURCE_HEAP_TIER_1 ? (bNumberOnly ? " 1" : "Tier 1")	: (bNumberOnly ?"2" : "Tier 2");
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


inline std::string D3DShaderModelToString(D3D_SHADER_MODEL shaderModel)
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


inline std::string D3DTiledResourcesTierToString(D3D12_TILED_RESOURCES_TIER tiledResourcesTier, bool bNumberOnly = false)
{
	switch (tiledResourcesTier)
	{
	case D3D12_TILED_RESOURCES_TIER_1: return bNumberOnly ? "1" : "Tier 1"; break;
	case D3D12_TILED_RESOURCES_TIER_2: return bNumberOnly ? "2" : "Tier 2"; break;
	case D3D12_TILED_RESOURCES_TIER_3: return bNumberOnly ? "3" : "Tier 3"; break;
	case D3D12_TILED_RESOURCES_TIER_4: return bNumberOnly ? "4" : "Tier 4"; break;
	default: return "Not supported"; break;
	}
}

} // namespace Kodiak::DX12