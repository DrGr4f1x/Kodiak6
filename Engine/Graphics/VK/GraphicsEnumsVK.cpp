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

#include "GraphicsEnumsVK.h"

using namespace Kodiak;
using namespace Kodiak::VK;

namespace Kodiak::VK
{

VkBlendFactor BlendToVulkan(Blend blend)
{
	switch (blend)
	{
	case Blend::Zero:				return VK_BLEND_FACTOR_ZERO; break;
	case Blend::One:				return VK_BLEND_FACTOR_ONE; break;
	case Blend::SrcColor:			return VK_BLEND_FACTOR_SRC_COLOR; break;
	case Blend::InvSrcColor:		return VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR; break;
	case Blend::SrcAlpha:			return VK_BLEND_FACTOR_SRC_ALPHA; break;
	case Blend::InvSrcAlpha:		return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA; break;
	case Blend::DstAlpha:			return VK_BLEND_FACTOR_DST_ALPHA; break;
	case Blend::InvDstAlpha:		return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA; break;
	case Blend::DstColor:			return VK_BLEND_FACTOR_DST_COLOR; break;
	case Blend::InvDstColor:		return VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR; break;
	case Blend::SrcAlphaSat:		return VK_BLEND_FACTOR_SRC_ALPHA_SATURATE; break;
	case Blend::BlendFactor:		return VK_BLEND_FACTOR_CONSTANT_COLOR; break;
	case Blend::InvBlendFactor:		return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR; break;
	case Blend::AlphaFactor:		return VK_BLEND_FACTOR_CONSTANT_ALPHA; break;
	case Blend::InvAlphaFactor:		return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA; break;
	case Blend::Src1Color:			return VK_BLEND_FACTOR_SRC1_COLOR; break;
	case Blend::InvSrc1Color:		return VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR; break;
	case Blend::Src1Alpha:			return VK_BLEND_FACTOR_SRC1_ALPHA; break;
	case Blend::InvSrc1Alpha:		return VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA; break;
	default:
		assert(false);
		return VK_BLEND_FACTOR_ZERO;
		break;
	}
}

} // namespace Kodiak::VK