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

#include "GraphicsEnums12.h"

using namespace Kodiak;
using namespace Kodiak::DX12;

namespace Kodiak::DX12
{

D3D12_BLEND BlendToDX12(Blend blend)
{
	switch (blend)
	{
	case Blend::Zero:				return D3D12_BLEND_ZERO; break;
	case Blend::One:				return D3D12_BLEND_ONE; break;
	case Blend::SrcColor:			return D3D12_BLEND_SRC_COLOR; break;
	case Blend::InvSrcColor:		return D3D12_BLEND_INV_SRC_COLOR; break;
	case Blend::SrcAlpha:			return D3D12_BLEND_SRC_ALPHA; break;
	case Blend::InvSrcAlpha:		return D3D12_BLEND_INV_SRC_ALPHA; break;
	case Blend::DstAlpha:			return D3D12_BLEND_DEST_ALPHA; break;
	case Blend::InvDstAlpha:		return D3D12_BLEND_INV_DEST_ALPHA; break;
	case Blend::DstColor:			return D3D12_BLEND_DEST_COLOR; break;
	case Blend::InvDstColor:		return D3D12_BLEND_INV_DEST_COLOR; break;
	case Blend::SrcAlphaSat:		return D3D12_BLEND_SRC_ALPHA_SAT; break;
	case Blend::BlendFactor:		return D3D12_BLEND_BLEND_FACTOR; break;
	case Blend::InvBlendFactor:		return D3D12_BLEND_INV_BLEND_FACTOR; break;
	case Blend::AlphaFactor:		return D3D12_BLEND_ALPHA_FACTOR; break;
	case Blend::InvAlphaFactor:		return D3D12_BLEND_INV_ALPHA_FACTOR; break;
	case Blend::Src1Color:			return D3D12_BLEND_SRC1_COLOR; break;
	case Blend::InvSrc1Color:		return D3D12_BLEND_INV_SRC1_COLOR; break;
	case Blend::Src1Alpha:			return D3D12_BLEND_SRC1_ALPHA; break;
	case Blend::InvSrc1Alpha:		return D3D12_BLEND_INV_SRC1_ALPHA; break;
	default:
		assert(false);
		return D3D12_BLEND_ZERO;
		break;
	}
}

} // namespace Kodiak::DX12