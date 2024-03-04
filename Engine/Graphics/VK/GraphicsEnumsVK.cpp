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


VkBlendOp BlendOpToVulkan(BlendOp blendOp)
{
	switch (blendOp)
	{
	case BlendOp::Add:			return VK_BLEND_OP_ADD; break;
	case BlendOp::Subtract:		return VK_BLEND_OP_SUBTRACT; break;
	case BlendOp::RevSubtract:	return VK_BLEND_OP_REVERSE_SUBTRACT; break;
	case BlendOp::Min:			return VK_BLEND_OP_MIN; break;
	case BlendOp::Max:			return VK_BLEND_OP_MAX; break;
	default:
		assert(false);
		return VK_BLEND_OP_ADD;
		break;
	}
}


VkLogicOp LogicOpToVulkan(LogicOp logicOp)
{
	switch (logicOp)
	{
	case LogicOp::Clear:			return VK_LOGIC_OP_CLEAR; break;
	case LogicOp::Set:				return VK_LOGIC_OP_SET; break;
	case LogicOp::Copy:				return VK_LOGIC_OP_COPY; break;
	case LogicOp::CopyInverted:		return VK_LOGIC_OP_COPY_INVERTED; break;
	case LogicOp::Noop:				return VK_LOGIC_OP_NO_OP; break;
	case LogicOp::Invert:			return VK_LOGIC_OP_INVERT; break;
	case LogicOp::And:				return VK_LOGIC_OP_AND; break;
	case LogicOp::Nand:				return VK_LOGIC_OP_NAND; break;
	case LogicOp::Or:				return VK_LOGIC_OP_OR; break;
	case LogicOp::Nor:				return VK_LOGIC_OP_NOR; break;
	case LogicOp::Xor:				return VK_LOGIC_OP_XOR; break;
	case LogicOp::Equiv:			return VK_LOGIC_OP_EQUIVALENT; break;
	case LogicOp::AndReverse:		return VK_LOGIC_OP_AND_REVERSE; break;
	case LogicOp::OrReverse:		return VK_LOGIC_OP_OR_REVERSE; break;
	case LogicOp::OrInverted:		return VK_LOGIC_OP_OR_INVERTED; break;
	default:
		assert(false);
		return VK_LOGIC_OP_NO_OP;
		break;
	}
}


VkColorComponentFlags ColorWriteToVulkan(ColorWrite colorWrite)
{
	switch (colorWrite)
	{
	case ColorWrite::Red:		return VK_COLOR_COMPONENT_R_BIT; break;
	case ColorWrite::Green:		return VK_COLOR_COMPONENT_G_BIT; break;
	case ColorWrite::Blue:		return VK_COLOR_COMPONENT_B_BIT; break;
	case ColorWrite::Alpha:		return VK_COLOR_COMPONENT_A_BIT; break;
	case ColorWrite::All:		return (VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT); break;
	default:
		assert(false);
		return (VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT);
		break;
	}
}


VkCullModeFlags CullModeToVulkan(CullMode cullMode)
{
	switch (cullMode)
	{
	case CullMode::None:	return VK_CULL_MODE_NONE; break;
	case CullMode::Front:	return VK_CULL_MODE_FRONT_BIT; break;
	case CullMode::Back:	return VK_CULL_MODE_BACK_BIT; break;
	default:
		assert(false);
		return VK_CULL_MODE_BACK_BIT;
		break;
	}
}


VkPolygonMode FillModeToVulkan(FillMode fillMode)
{
	switch (fillMode)
	{
	case FillMode::Wireframe:	return VK_POLYGON_MODE_LINE; break;
	case FillMode::Solid:		return VK_POLYGON_MODE_FILL; break;
	default:
		assert(false);
		return VK_POLYGON_MODE_FILL;
		break;
	}
}


VkCompareOp ComparisonFuncToVulkan(ComparisonFunc comparisonFunc)
{
	switch (comparisonFunc)
	{
	case ComparisonFunc::Never:			return VK_COMPARE_OP_NEVER; break;
	case ComparisonFunc::Less:			return VK_COMPARE_OP_LESS; break;
	case ComparisonFunc::LessEqual:		return VK_COMPARE_OP_LESS_OR_EQUAL; break;
	case ComparisonFunc::Greater:		return VK_COMPARE_OP_GREATER; break;
	case ComparisonFunc::NotEqual:		return VK_COMPARE_OP_NOT_EQUAL; break;
	case ComparisonFunc::GreaterEqual:	return VK_COMPARE_OP_GREATER_OR_EQUAL; break;
	case ComparisonFunc::Always:		return VK_COMPARE_OP_ALWAYS; break;
	default:
		assert(false);
		return VK_COMPARE_OP_ALWAYS;
		break;
	}
}


VkStencilOp StencilOpToVulkan(StencilOp stencilOp)
{
	switch (stencilOp)
	{
	case StencilOp::Keep:		return VK_STENCIL_OP_KEEP; break;
	case StencilOp::Zero:		return VK_STENCIL_OP_ZERO; break;
	case StencilOp::Replace:	return VK_STENCIL_OP_REPLACE; break;
	case StencilOp::IncrSat:	return VK_STENCIL_OP_INCREMENT_AND_CLAMP; break;
	case StencilOp::DecrSat:	return VK_STENCIL_OP_DECREMENT_AND_CLAMP; break;
	case StencilOp::Invert:		return VK_STENCIL_OP_INVERT; break;
	case StencilOp::Incr:		return VK_STENCIL_OP_INCREMENT_AND_WRAP; break;
	case StencilOp::Decr:		return VK_STENCIL_OP_DECREMENT_AND_WRAP; break;
	default:
		assert(false);
		return VK_STENCIL_OP_KEEP;
		break;
	}
}


VkPrimitiveTopology PrimitiveTopologyToVulkan(PrimitiveTopology primitiveTopology)
{
	switch (primitiveTopology)
	{
	case PrimitiveTopology::PointList:						return VK_PRIMITIVE_TOPOLOGY_POINT_LIST; break;
	case PrimitiveTopology::LineList:						return VK_PRIMITIVE_TOPOLOGY_LINE_LIST; break;
	case PrimitiveTopology::LineStrip:						return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP; break;
	case PrimitiveTopology::TriangleList:					return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST; break;
	case PrimitiveTopology::TriangleStrip:					return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP; break;
	case PrimitiveTopology::LineListWithAdjacency:			return VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY; break;
	case PrimitiveTopology::LineStripWithAdjacency:			return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY; break;
	case PrimitiveTopology::TriangleListWithAdjacency:		return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY; break;
	case PrimitiveTopology::TriangleStripWithAdjacency:		return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY; break;
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
		return VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
		break;
	default:
		assert(false);
		return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		break;
	}
}


uint32_t GetControlPointCount(PrimitiveTopology primitiveTopology)
{
	switch (primitiveTopology)
	{
	case PrimitiveTopology::PatchList_1_ControlPoint:	return 1;
	case PrimitiveTopology::PatchList_2_ControlPoint:	return 2;
	case PrimitiveTopology::PatchList_3_ControlPoint:	return 3;
	case PrimitiveTopology::PatchList_4_ControlPoint:	return 4;
	case PrimitiveTopology::PatchList_5_ControlPoint:	return 5;
	case PrimitiveTopology::PatchList_6_ControlPoint:	return 6;
	case PrimitiveTopology::PatchList_7_ControlPoint:	return 7;
	case PrimitiveTopology::PatchList_8_ControlPoint:	return 8;
	case PrimitiveTopology::PatchList_9_ControlPoint:	return 9;
	case PrimitiveTopology::PatchList_10_ControlPoint:	return 10;
	case PrimitiveTopology::PatchList_11_ControlPoint:	return 11;
	case PrimitiveTopology::PatchList_12_ControlPoint:	return 12;
	case PrimitiveTopology::PatchList_13_ControlPoint:	return 13;
	case PrimitiveTopology::PatchList_14_ControlPoint:	return 14;
	case PrimitiveTopology::PatchList_15_ControlPoint:	return 15;
	case PrimitiveTopology::PatchList_16_ControlPoint:	return 16;
	case PrimitiveTopology::PatchList_17_ControlPoint:	return 17;
	case PrimitiveTopology::PatchList_18_ControlPoint:	return 18;
	case PrimitiveTopology::PatchList_19_ControlPoint:	return 19;
	case PrimitiveTopology::PatchList_20_ControlPoint:	return 20;
	case PrimitiveTopology::PatchList_21_ControlPoint:	return 21;
	case PrimitiveTopology::PatchList_22_ControlPoint:	return 22;
	case PrimitiveTopology::PatchList_23_ControlPoint:	return 23;
	case PrimitiveTopology::PatchList_24_ControlPoint:	return 24;
	case PrimitiveTopology::PatchList_25_ControlPoint:	return 25;
	case PrimitiveTopology::PatchList_26_ControlPoint:	return 26;
	case PrimitiveTopology::PatchList_27_ControlPoint:	return 27;
	case PrimitiveTopology::PatchList_28_ControlPoint:	return 28;
	case PrimitiveTopology::PatchList_29_ControlPoint:	return 29;
	case PrimitiveTopology::PatchList_30_ControlPoint:	return 30;
	case PrimitiveTopology::PatchList_31_ControlPoint:	return 31;
	case PrimitiveTopology::PatchList_32_ControlPoint:	return 32;
	default:
		return 0;
	}
}


VkVertexInputRate InputClassificationToVulkan(InputClassification inputClassification)
{
	switch (inputClassification)
	{
	case InputClassification::PerVertexData:	return VK_VERTEX_INPUT_RATE_VERTEX; break;
	case InputClassification::PerInstanceData:	return VK_VERTEX_INPUT_RATE_INSTANCE; break;
	default:
		assert(false);
		return VK_VERTEX_INPUT_RATE_VERTEX;
		break;
	}
}


VkShaderStageFlags ShaderStageToVulkan(ShaderStage shaderStage)
{
	if (shaderStage == ShaderStage::All)
	{
		return VK_SHADER_STAGE_ALL;
	}

	if (shaderStage == ShaderStage::AllGraphics)
	{
		return VK_SHADER_STAGE_ALL_GRAPHICS;
	}

	uint32_t result = 0;
	if (HasFlag<ShaderStage>(shaderStage, ShaderStage::Compute))		result |= VK_SHADER_STAGE_COMPUTE_BIT;
	if (HasFlag<ShaderStage>(shaderStage, ShaderStage::Vertex))			result |= VK_SHADER_STAGE_VERTEX_BIT;
	if (HasFlag<ShaderStage>(shaderStage, ShaderStage::Hull))			result |= VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
	if (HasFlag<ShaderStage>(shaderStage, ShaderStage::Domain))			result |= VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
	if (HasFlag<ShaderStage>(shaderStage, ShaderStage::Geometry))		result |= VK_SHADER_STAGE_GEOMETRY_BIT;
	if (HasFlag<ShaderStage>(shaderStage, ShaderStage::Pixel))			result |= VK_SHADER_STAGE_FRAGMENT_BIT;
	if (HasFlag<ShaderStage>(shaderStage, ShaderStage::Amplification))	result |= VK_SHADER_STAGE_TASK_BIT_EXT;
	if (HasFlag<ShaderStage>(shaderStage, ShaderStage::Mesh))			result |= VK_SHADER_STAGE_MESH_BIT_EXT;
	if (HasFlag<ShaderStage>(shaderStage, ShaderStage::RayGeneration))	result |= VK_SHADER_STAGE_RAYGEN_BIT_KHR;
	if (HasFlag<ShaderStage>(shaderStage, ShaderStage::Miss))			result |= VK_SHADER_STAGE_MISS_BIT_KHR;
	if (HasFlag<ShaderStage>(shaderStage, ShaderStage::ClosestHit))		result |= VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR;
	if (HasFlag<ShaderStage>(shaderStage, ShaderStage::AnyHit))			result |= VK_SHADER_STAGE_ANY_HIT_BIT_KHR;
	if (HasFlag<ShaderStage>(shaderStage, ShaderStage::Intersection))	result |= VK_SHADER_STAGE_INTERSECTION_BIT_KHR;
	if (HasFlag<ShaderStage>(shaderStage, ShaderStage::Callable))		result |= VK_SHADER_STAGE_CALLABLE_BIT_KHR;

	return (VkShaderStageFlags)result;
}


VkDescriptorType DescriptorTypeToVulkan(DescriptorType descriptorType)
{
	switch (descriptorType)
	{
	case DescriptorType::CBV:					return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER; break;
	case DescriptorType::DynamicCBV:			return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC; break;
	case DescriptorType::Sampler:				return VK_DESCRIPTOR_TYPE_SAMPLER; break;
	case DescriptorType::TextureSRV:			return VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE; break;
	case DescriptorType::StructuredBufferSRV:	return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER; break;
	case DescriptorType::StructuredBufferUAV:	return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER; break;
	case DescriptorType::TextureUAV:			return VK_DESCRIPTOR_TYPE_STORAGE_IMAGE; break;
	case DescriptorType::TypedBufferSRV:		return VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER; break;
	case DescriptorType::TypedBufferUAV:		return VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER; break;
	default:
		assert(false);
		return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		break;
	}
}

} // namespace Kodiak::VK