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
		uint32_t result = 0;
		if (HasFlag<ColorWrite>(colorWrite, ColorWrite::Red))	result |= D3D12_COLOR_WRITE_ENABLE_RED;
		if (HasFlag<ColorWrite>(colorWrite, ColorWrite::Green))	result |= D3D12_COLOR_WRITE_ENABLE_GREEN;
		if (HasFlag<ColorWrite>(colorWrite, ColorWrite::Blue))	result |= D3D12_COLOR_WRITE_ENABLE_BLUE;
		if (HasFlag<ColorWrite>(colorWrite, ColorWrite::Alpha))	result |= D3D12_COLOR_WRITE_ENABLE_ALPHA;

		return (D3D12_COLOR_WRITE_ENABLE)result;
	}
}


D3D12_DEPTH_WRITE_MASK DepthWriteToDX12(DepthWrite depthWrite)
{
	switch (depthWrite)
	{
	case DepthWrite::Zero:	return D3D12_DEPTH_WRITE_MASK_ZERO; break;
	case DepthWrite::All:	return D3D12_DEPTH_WRITE_MASK_ALL; break;
	default:
		assert(false);
		return D3D12_DEPTH_WRITE_MASK_ALL;
		break;
	}
}


D3D12_CULL_MODE CullModeToDX12(CullMode cullMode)
{
	switch (cullMode)
	{
	case CullMode::None:	return D3D12_CULL_MODE_NONE; break;
	case CullMode::Front:	return D3D12_CULL_MODE_FRONT; break;
	case CullMode::Back:	return D3D12_CULL_MODE_BACK; break;
	default:
		assert(false);
		return D3D12_CULL_MODE_BACK;
		break;
	}
}


D3D12_FILL_MODE FillModeToDX12(FillMode fillMode)
{
	switch (fillMode)
	{
	case FillMode::Wireframe: return D3D12_FILL_MODE_WIREFRAME; break;
	case FillMode::Solid: return D3D12_FILL_MODE_SOLID; break;
	default:
		assert(false);
		return D3D12_FILL_MODE_SOLID;
		break;
	}
}


D3D12_COMPARISON_FUNC ComparisonFuncToDX12(ComparisonFunc comparisonFunc)
{
	switch (comparisonFunc)
	{
	case ComparisonFunc::Never: return D3D12_COMPARISON_FUNC_NEVER; break;
	case ComparisonFunc::Less: return D3D12_COMPARISON_FUNC_LESS; break;
	case ComparisonFunc::LessEqual: return D3D12_COMPARISON_FUNC_LESS_EQUAL; break;
	case ComparisonFunc::Greater: return D3D12_COMPARISON_FUNC_GREATER; break;
	case ComparisonFunc::NotEqual: return D3D12_COMPARISON_FUNC_NOT_EQUAL; break;
	case ComparisonFunc::GreaterEqual: return D3D12_COMPARISON_FUNC_GREATER_EQUAL; break;
	case ComparisonFunc::Always: return D3D12_COMPARISON_FUNC_ALWAYS; break;
	default:
		assert(false);
		return D3D12_COMPARISON_FUNC_ALWAYS;
		break;
	}
}


D3D12_STENCIL_OP StencilOpToDX12(StencilOp stencilOp)
{
	switch (stencilOp)
	{
	case StencilOp::Keep:		return D3D12_STENCIL_OP_KEEP; break;
	case StencilOp::Zero:		return D3D12_STENCIL_OP_ZERO; break;
	case StencilOp::Replace:	return D3D12_STENCIL_OP_REPLACE; break;
	case StencilOp::IncrSat:	return D3D12_STENCIL_OP_INCR_SAT; break;
	case StencilOp::DecrSat:	return D3D12_STENCIL_OP_DECR_SAT; break;
	case StencilOp::Invert:		return D3D12_STENCIL_OP_INVERT; break;
	case StencilOp::Incr:		return D3D12_STENCIL_OP_INCR; break;
	case StencilOp::Decr:		return D3D12_STENCIL_OP_DECR; break;
	default:
		assert(false);
		return D3D12_STENCIL_OP_KEEP;
		break;

	}
}


D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IndexBufferStripCutValueToDX12(IndexBufferStripCutValue indexBufferStripCutValue)
{
	switch (indexBufferStripCutValue)
	{
	case IndexBufferStripCutValue::Disabled:			return D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED; break;
	case IndexBufferStripCutValue::Value_0xFFFF:		return D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_0xFFFF; break;
	case IndexBufferStripCutValue::Value_0xFFFFFFFF:	return D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_0xFFFFFFFF; break;
	default:
		assert(false);
		return D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
		break;
	}
}


D3D12_PRIMITIVE_TOPOLOGY PrimitiveTopologyToDX12(PrimitiveTopology primitiveTopology)
{
	switch (primitiveTopology)
	{
	case PrimitiveTopology::PointList:						return D3D_PRIMITIVE_TOPOLOGY_POINTLIST; break;
	case PrimitiveTopology::LineList:						return D3D_PRIMITIVE_TOPOLOGY_LINELIST; break;
	case PrimitiveTopology::LineStrip:						return D3D_PRIMITIVE_TOPOLOGY_LINESTRIP; break;
	case PrimitiveTopology::TriangleList:					return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST; break;
	case PrimitiveTopology::TriangleStrip:					return D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; break;
	case PrimitiveTopology::LineListWithAdjacency:			return D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ; break;
	case PrimitiveTopology::LineStripWithAdjacency:			return D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ; break;
	case PrimitiveTopology::TriangleListWithAdjacency:		return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ; break;
	case PrimitiveTopology::TriangleStripWithAdjacency:		return D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ; break;
	case PrimitiveTopology::PatchList_1_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_2_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_3_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_4_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_5_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_6_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_7_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_8_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_9_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_10_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_11_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_12_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_13_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_14_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_15_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_16_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_17_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_18_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_19_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_20_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_21_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_22_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_23_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_24_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_25_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_26_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_27_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_28_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_29_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_30_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_31_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST; break;
	case PrimitiveTopology::PatchList_32_ControlPoint:		return D3D_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST; break;
	default:
		assert(false);
		return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		break;
	}
}


D3D12_PRIMITIVE_TOPOLOGY_TYPE PrimitiveTopologyToPrimitiveTopologyTypeDX12(PrimitiveTopology primitiveTopology)
{
	switch (primitiveTopology)
	{
	case PrimitiveTopology::PointList: 
		return D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT; 
		break;

	case PrimitiveTopology::LineList:
	case PrimitiveTopology::LineStrip:
	case PrimitiveTopology::LineListWithAdjacency:
	case PrimitiveTopology::LineStripWithAdjacency:
		return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
		break;

	case PrimitiveTopology::TriangleList:
	case PrimitiveTopology::TriangleStrip:
	case PrimitiveTopology::TriangleListWithAdjacency:
	case PrimitiveTopology::TriangleStripWithAdjacency:
		return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		break;

	case PrimitiveTopology::PatchList_1_ControlPoint:
	case PrimitiveTopology::PatchList_2_ControlPoint:
	case PrimitiveTopology::PatchList_3_ControlPoint:
	case PrimitiveTopology::PatchList_4_ControlPoint:
	case PrimitiveTopology::PatchList_5_ControlPoint:
	case PrimitiveTopology::PatchList_6_ControlPoint:
	case PrimitiveTopology::PatchList_7_ControlPoint:
	case PrimitiveTopology::PatchList_8_ControlPoint:
	case PrimitiveTopology::PatchList_9_ControlPoint:
	case PrimitiveTopology::PatchList_10_ControlPoint:
	case PrimitiveTopology::PatchList_11_ControlPoint:
	case PrimitiveTopology::PatchList_12_ControlPoint:
	case PrimitiveTopology::PatchList_13_ControlPoint:
	case PrimitiveTopology::PatchList_14_ControlPoint:
	case PrimitiveTopology::PatchList_15_ControlPoint:
	case PrimitiveTopology::PatchList_16_ControlPoint:
	case PrimitiveTopology::PatchList_17_ControlPoint:
	case PrimitiveTopology::PatchList_18_ControlPoint:
	case PrimitiveTopology::PatchList_19_ControlPoint:
	case PrimitiveTopology::PatchList_20_ControlPoint:
	case PrimitiveTopology::PatchList_21_ControlPoint:
	case PrimitiveTopology::PatchList_22_ControlPoint:
	case PrimitiveTopology::PatchList_23_ControlPoint:
	case PrimitiveTopology::PatchList_24_ControlPoint:
	case PrimitiveTopology::PatchList_25_ControlPoint:
	case PrimitiveTopology::PatchList_26_ControlPoint:
	case PrimitiveTopology::PatchList_27_ControlPoint:
	case PrimitiveTopology::PatchList_28_ControlPoint:
	case PrimitiveTopology::PatchList_29_ControlPoint:
	case PrimitiveTopology::PatchList_30_ControlPoint:
	case PrimitiveTopology::PatchList_31_ControlPoint:
	case PrimitiveTopology::PatchList_32_ControlPoint:
		return D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH;
		break;

	default:
		assert(false);
		return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		break;
	}
}


D3D12_SHADER_VISIBILITY ShaderStageToDX12(ShaderStage shaderStage)
{
	switch (shaderStage)
	{
	case ShaderStage::Vertex:			return D3D12_SHADER_VISIBILITY_VERTEX; break;
	case ShaderStage::Hull:				return D3D12_SHADER_VISIBILITY_HULL; break;
	case ShaderStage::Domain:			return D3D12_SHADER_VISIBILITY_DOMAIN; break;
	case ShaderStage::Geometry:			return D3D12_SHADER_VISIBILITY_GEOMETRY; break;
	case ShaderStage::Pixel:			return D3D12_SHADER_VISIBILITY_PIXEL; break;
	case ShaderStage::Amplification:	return D3D12_SHADER_VISIBILITY_AMPLIFICATION; break;
	case ShaderStage::Mesh:				return D3D12_SHADER_VISIBILITY_MESH; break;
	default:
		// Some combinations are unrepresentable in DX12
		return D3D12_SHADER_VISIBILITY_ALL;
		break;
	}
}


D3D12_DESCRIPTOR_RANGE_TYPE DescriptorTypeToDX12(DescriptorType type)
{
	switch (type)
	{
	case DescriptorType::CBV:
	case DescriptorType::DynamicCBV:
		return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
		break;
	case DescriptorType::Sampler:
		return D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
		break;
	case DescriptorType::TextureSRV:
	case DescriptorType::TypedBufferSRV:
	case DescriptorType::StructuredBufferSRV:
		return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		break;
	case DescriptorType::TextureUAV:
	case DescriptorType::TypedBufferUAV:
	case DescriptorType::StructuredBufferUAV:
		return D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
		break;
	default:
		assert(false);
		return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		break;
	}
}


D3D12_ROOT_SIGNATURE_FLAGS RootSignatureFlagsToDX12(RootSignatureFlags rootSignatureFlags)
{
	uint32_t result = 0;
	if (HasFlag<RootSignatureFlags>(rootSignatureFlags, RootSignatureFlags::AllowInputAssemblerInputLayout))			result |= D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	if (HasFlag<RootSignatureFlags>(rootSignatureFlags, RootSignatureFlags::DenyVertexShaderRootAccess))				result |= D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS;
	if (HasFlag<RootSignatureFlags>(rootSignatureFlags, RootSignatureFlags::DenyHullShaderRootAccess))					result |= D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS;
	if (HasFlag<RootSignatureFlags>(rootSignatureFlags, RootSignatureFlags::DenyDomainShaderRootAccess))				result |= D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS;
	if (HasFlag<RootSignatureFlags>(rootSignatureFlags, RootSignatureFlags::DenyGeometryShaderRootAccess))				result |= D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;
	if (HasFlag<RootSignatureFlags>(rootSignatureFlags, RootSignatureFlags::DenyPixelShaderRootAccess))					result |= D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;
	if (HasFlag<RootSignatureFlags>(rootSignatureFlags, RootSignatureFlags::AllowStreamOutput))							result |= D3D12_ROOT_SIGNATURE_FLAG_ALLOW_STREAM_OUTPUT;
	if (HasFlag<RootSignatureFlags>(rootSignatureFlags, RootSignatureFlags::DenyAmplificationShaderRootAccess))			result |= D3D12_ROOT_SIGNATURE_FLAG_DENY_AMPLIFICATION_SHADER_ROOT_ACCESS;
	if (HasFlag<RootSignatureFlags>(rootSignatureFlags, RootSignatureFlags::DenyMeshShaderRootAccess))					result |= D3D12_ROOT_SIGNATURE_FLAG_DENY_MESH_SHADER_ROOT_ACCESS;
	if (HasFlag<RootSignatureFlags>(rootSignatureFlags, RootSignatureFlags::CbvSrvUavHeapDirectlyIndexed))				result |= D3D12_ROOT_SIGNATURE_FLAG_CBV_SRV_UAV_HEAP_DIRECTLY_INDEXED;
	if (HasFlag<RootSignatureFlags>(rootSignatureFlags, RootSignatureFlags::SamplerHeapDirectlyIndexed))				result |= D3D12_ROOT_SIGNATURE_FLAG_SAMPLER_HEAP_DIRECTLY_INDEXED;
	
	return (D3D12_ROOT_SIGNATURE_FLAGS)result;
}

} // namespace Kodiak::DX12