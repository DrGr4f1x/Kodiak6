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


D3D12_BLEND_OP BlendOpToDX12(BlendOp blendOp)
{
	switch (blendOp)
	{
	case BlendOp::Add:			return D3D12_BLEND_OP_ADD; break;
	case BlendOp::Subtract:		return D3D12_BLEND_OP_SUBTRACT; break;
	case BlendOp::RevSubtract:	return D3D12_BLEND_OP_REV_SUBTRACT; break;
	case BlendOp::Min:			return D3D12_BLEND_OP_MIN; break;
	case BlendOp::Max:			return D3D12_BLEND_OP_MAX; break;
	default:
		assert(false);
		return D3D12_BLEND_OP_ADD;
		break;
	}
}


D3D12_LOGIC_OP LogicOpToDX12(LogicOp logicOp)
{
	switch (logicOp)
	{
	case LogicOp::Clear:			return D3D12_LOGIC_OP_CLEAR; break;
	case LogicOp::Set:				return D3D12_LOGIC_OP_SET; break;
	case LogicOp::Copy:				return D3D12_LOGIC_OP_COPY; break;
	case LogicOp::CopyInverted:		return D3D12_LOGIC_OP_COPY_INVERTED; break;
	case LogicOp::Noop:				return D3D12_LOGIC_OP_NOOP; break;
	case LogicOp::Invert:			return D3D12_LOGIC_OP_INVERT; break;
	case LogicOp::And:				return D3D12_LOGIC_OP_AND; break;
	case LogicOp::Nand:				return D3D12_LOGIC_OP_NAND; break;
	case LogicOp::Or:				return D3D12_LOGIC_OP_OR; break;
	case LogicOp::Nor:				return D3D12_LOGIC_OP_NOR; break;
	case LogicOp::Xor:				return D3D12_LOGIC_OP_XOR; break;
	case LogicOp::Equiv:			return D3D12_LOGIC_OP_EQUIV; break;
	case LogicOp::AndReverse:		return D3D12_LOGIC_OP_AND_REVERSE; break;
	case LogicOp::OrReverse:		return D3D12_LOGIC_OP_OR_REVERSE; break;
	case LogicOp::OrInverted:		return D3D12_LOGIC_OP_OR_INVERTED; break;
	default:
		assert(false);
		return D3D12_LOGIC_OP_NOOP;
		break;
	}
}

D3D12_COLOR_WRITE_ENABLE ColorWriteToDX12(ColorWrite colorWrite)
{
	switch (colorWrite)
	{
	case ColorWrite::Red:		return D3D12_COLOR_WRITE_ENABLE_RED; break;
	case ColorWrite::Green:		return D3D12_COLOR_WRITE_ENABLE_GREEN; break;
	case ColorWrite::Blue:		return D3D12_COLOR_WRITE_ENABLE_BLUE; break;
	case ColorWrite::Alpha:		return D3D12_COLOR_WRITE_ENABLE_ALPHA; break;
	case ColorWrite::All:		return D3D12_COLOR_WRITE_ENABLE_ALL; break;
	default:
		assert(false);
		return D3D12_COLOR_WRITE_ENABLE_ALL;
		break;
	}
}


D3D12_DEPTH_WRITE_MASK DepthWriteToDX12(DepthWrite depthWrite)
{
	switch (depthWrite)
	{
	case DepthWrite::Zero: return D3D12_DEPTH_WRITE_MASK_ZERO; break;
	case DepthWrite::All: return D3D12_DEPTH_WRITE_MASK_ALL; break;
	default:
		assert(false);
		return D3D12_DEPTH_WRITE_MASK_ALL;
		break;
	}
}

} // namespace Kodiak::DX12