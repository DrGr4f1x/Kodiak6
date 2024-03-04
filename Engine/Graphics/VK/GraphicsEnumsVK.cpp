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
	using enum Blend;

	switch (blend)
	{
	case Zero:				return VK_BLEND_FACTOR_ZERO; break;
	case One:				return VK_BLEND_FACTOR_ONE; break;
	case SrcColor:			return VK_BLEND_FACTOR_SRC_COLOR; break;
	case InvSrcColor:		return VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR; break;
	case SrcAlpha:			return VK_BLEND_FACTOR_SRC_ALPHA; break;
	case InvSrcAlpha:		return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA; break;
	case DstAlpha:			return VK_BLEND_FACTOR_DST_ALPHA; break;
	case InvDstAlpha:		return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA; break;
	case DstColor:			return VK_BLEND_FACTOR_DST_COLOR; break;
	case InvDstColor:		return VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR; break;
	case SrcAlphaSat:		return VK_BLEND_FACTOR_SRC_ALPHA_SATURATE; break;
	case BlendFactor:		return VK_BLEND_FACTOR_CONSTANT_COLOR; break;
	case InvBlendFactor:	return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR; break;
	case AlphaFactor:		return VK_BLEND_FACTOR_CONSTANT_ALPHA; break;
	case InvAlphaFactor:	return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA; break;
	case Src1Color:			return VK_BLEND_FACTOR_SRC1_COLOR; break;
	case InvSrc1Color:		return VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR; break;
	case Src1Alpha:			return VK_BLEND_FACTOR_SRC1_ALPHA; break;
	case InvSrc1Alpha:		return VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA; break;
	default:
		assert(false);
		return VK_BLEND_FACTOR_ZERO;
		break;
	}
}


VkBlendOp BlendOpToVulkan(BlendOp blendOp)
{
	using enum BlendOp;

	switch (blendOp)
	{
	case Add:			return VK_BLEND_OP_ADD; break;
	case Subtract:		return VK_BLEND_OP_SUBTRACT; break;
	case RevSubtract:	return VK_BLEND_OP_REVERSE_SUBTRACT; break;
	case Min:			return VK_BLEND_OP_MIN; break;
	case Max:			return VK_BLEND_OP_MAX; break;
	default:
		assert(false);
		return VK_BLEND_OP_ADD;
		break;
	}
}


VkLogicOp LogicOpToVulkan(LogicOp logicOp)
{
	using enum LogicOp;

	switch (logicOp)
	{
	case Clear:			return VK_LOGIC_OP_CLEAR; break;
	case Set:			return VK_LOGIC_OP_SET; break;
	case Copy:			return VK_LOGIC_OP_COPY; break;
	case CopyInverted:	return VK_LOGIC_OP_COPY_INVERTED; break;
	case Noop:			return VK_LOGIC_OP_NO_OP; break;
	case Invert:		return VK_LOGIC_OP_INVERT; break;
	case And:			return VK_LOGIC_OP_AND; break;
	case Nand:			return VK_LOGIC_OP_NAND; break;
	case Or:			return VK_LOGIC_OP_OR; break;
	case Nor:			return VK_LOGIC_OP_NOR; break;
	case Xor:			return VK_LOGIC_OP_XOR; break;
	case Equiv:			return VK_LOGIC_OP_EQUIVALENT; break;
	case AndReverse:	return VK_LOGIC_OP_AND_REVERSE; break;
	case OrReverse:		return VK_LOGIC_OP_OR_REVERSE; break;
	case OrInverted:	return VK_LOGIC_OP_OR_INVERTED; break;
	default:
		assert(false);
		return VK_LOGIC_OP_NO_OP;
		break;
	}
}


VkColorComponentFlags ColorWriteToVulkan(ColorWrite colorWrite)
{
	using enum ColorWrite;

	uint32_t result = 0;
	if (HasFlag<ColorWrite>(colorWrite, Red))		result |= VK_COLOR_COMPONENT_R_BIT;
	if (HasFlag<ColorWrite>(colorWrite, Green))		result |= VK_COLOR_COMPONENT_G_BIT;
	if (HasFlag<ColorWrite>(colorWrite, Blue))		result |= VK_COLOR_COMPONENT_B_BIT;
	if (HasFlag<ColorWrite>(colorWrite, Alpha))		result |= VK_COLOR_COMPONENT_A_BIT;

	return (VkColorComponentFlags)result;
}


VkCullModeFlags CullModeToVulkan(CullMode cullMode)
{
	using enum CullMode;

	switch (cullMode)
	{
	case None:	return VK_CULL_MODE_NONE; break;
	case Front:	return VK_CULL_MODE_FRONT_BIT; break;
	case Back:	return VK_CULL_MODE_BACK_BIT; break;
	default:
		assert(false);
		return VK_CULL_MODE_BACK_BIT;
		break;
	}
}


VkPolygonMode FillModeToVulkan(FillMode fillMode)
{
	using enum FillMode;

	switch (fillMode)
	{
	case Wireframe:	return VK_POLYGON_MODE_LINE; break;
	case Solid:		return VK_POLYGON_MODE_FILL; break;
	default:
		assert(false);
		return VK_POLYGON_MODE_FILL;
		break;
	}
}


VkCompareOp ComparisonFuncToVulkan(ComparisonFunc comparisonFunc)
{
	using enum ComparisonFunc;

	switch (comparisonFunc)
	{
	case Never:			return VK_COMPARE_OP_NEVER; break;
	case Less:			return VK_COMPARE_OP_LESS; break;
	case LessEqual:		return VK_COMPARE_OP_LESS_OR_EQUAL; break;
	case Greater:		return VK_COMPARE_OP_GREATER; break;
	case NotEqual:		return VK_COMPARE_OP_NOT_EQUAL; break;
	case GreaterEqual:	return VK_COMPARE_OP_GREATER_OR_EQUAL; break;
	case Always:		return VK_COMPARE_OP_ALWAYS; break;
	default:
		assert(false);
		return VK_COMPARE_OP_ALWAYS;
		break;
	}
}


VkStencilOp StencilOpToVulkan(StencilOp stencilOp)
{
	using enum StencilOp;

	switch (stencilOp)
	{
	case Keep:		return VK_STENCIL_OP_KEEP; break;
	case Zero:		return VK_STENCIL_OP_ZERO; break;
	case Replace:	return VK_STENCIL_OP_REPLACE; break;
	case IncrSat:	return VK_STENCIL_OP_INCREMENT_AND_CLAMP; break;
	case DecrSat:	return VK_STENCIL_OP_DECREMENT_AND_CLAMP; break;
	case Invert:	return VK_STENCIL_OP_INVERT; break;
	case Incr:		return VK_STENCIL_OP_INCREMENT_AND_WRAP; break;
	case Decr:		return VK_STENCIL_OP_DECREMENT_AND_WRAP; break;
	default:
		assert(false);
		return VK_STENCIL_OP_KEEP;
		break;
	}
}


VkPrimitiveTopology PrimitiveTopologyToVulkan(PrimitiveTopology primitiveTopology)
{
	using enum PrimitiveTopology;

	switch (primitiveTopology)
	{
	case PointList:						return VK_PRIMITIVE_TOPOLOGY_POINT_LIST; break;
	case LineList:						return VK_PRIMITIVE_TOPOLOGY_LINE_LIST; break;
	case LineStrip:						return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP; break;
	case TriangleList:					return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST; break;
	case TriangleStrip:					return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP; break;
	case LineListWithAdjacency:			return VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY; break;
	case LineStripWithAdjacency:		return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY; break;
	case TriangleListWithAdjacency:		return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY; break;
	case TriangleStripWithAdjacency:	return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY; break;
	case PatchList_1_ControlPoint:
	case PatchList_2_ControlPoint:
	case PatchList_3_ControlPoint:
	case PatchList_4_ControlPoint:
	case PatchList_5_ControlPoint:
	case PatchList_6_ControlPoint:
	case PatchList_7_ControlPoint:
	case PatchList_8_ControlPoint:
	case PatchList_9_ControlPoint:
	case PatchList_10_ControlPoint:
	case PatchList_11_ControlPoint:
	case PatchList_12_ControlPoint:
	case PatchList_13_ControlPoint:
	case PatchList_14_ControlPoint:
	case PatchList_15_ControlPoint:
	case PatchList_16_ControlPoint:
	case PatchList_17_ControlPoint:
	case PatchList_18_ControlPoint:
	case PatchList_19_ControlPoint:
	case PatchList_20_ControlPoint:
	case PatchList_21_ControlPoint:
	case PatchList_22_ControlPoint:
	case PatchList_23_ControlPoint:
	case PatchList_24_ControlPoint:
	case PatchList_25_ControlPoint:
	case PatchList_26_ControlPoint:
	case PatchList_27_ControlPoint:
	case PatchList_28_ControlPoint:
	case PatchList_29_ControlPoint:
	case PatchList_30_ControlPoint:
	case PatchList_31_ControlPoint:
	case PatchList_32_ControlPoint:
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
	using enum PrimitiveTopology;

	switch (primitiveTopology)
	{
	case PatchList_1_ControlPoint:	return 1;
	case PatchList_2_ControlPoint:	return 2;
	case PatchList_3_ControlPoint:	return 3;
	case PatchList_4_ControlPoint:	return 4;
	case PatchList_5_ControlPoint:	return 5;
	case PatchList_6_ControlPoint:	return 6;
	case PatchList_7_ControlPoint:	return 7;
	case PatchList_8_ControlPoint:	return 8;
	case PatchList_9_ControlPoint:	return 9;
	case PatchList_10_ControlPoint:	return 10;
	case PatchList_11_ControlPoint:	return 11;
	case PatchList_12_ControlPoint:	return 12;
	case PatchList_13_ControlPoint:	return 13;
	case PatchList_14_ControlPoint:	return 14;
	case PatchList_15_ControlPoint:	return 15;
	case PatchList_16_ControlPoint:	return 16;
	case PatchList_17_ControlPoint:	return 17;
	case PatchList_18_ControlPoint:	return 18;
	case PatchList_19_ControlPoint:	return 19;
	case PatchList_20_ControlPoint:	return 20;
	case PatchList_21_ControlPoint:	return 21;
	case PatchList_22_ControlPoint:	return 22;
	case PatchList_23_ControlPoint:	return 23;
	case PatchList_24_ControlPoint:	return 24;
	case PatchList_25_ControlPoint:	return 25;
	case PatchList_26_ControlPoint:	return 26;
	case PatchList_27_ControlPoint:	return 27;
	case PatchList_28_ControlPoint:	return 28;
	case PatchList_29_ControlPoint:	return 29;
	case PatchList_30_ControlPoint:	return 30;
	case PatchList_31_ControlPoint:	return 31;
	case PatchList_32_ControlPoint:	return 32;
	default:
		return 0;
	}
}


VkVertexInputRate InputClassificationToVulkan(InputClassification inputClassification)
{
	using enum InputClassification;

	switch (inputClassification)
	{
	case PerVertexData:		return VK_VERTEX_INPUT_RATE_VERTEX; break;
	case PerInstanceData:	return VK_VERTEX_INPUT_RATE_INSTANCE; break;
	default:
		assert(false);
		return VK_VERTEX_INPUT_RATE_VERTEX;
		break;
	}
}


VkShaderStageFlags ShaderStageToVulkan(ShaderStage shaderStage)
{
	using enum ShaderStage;

	if (shaderStage == All)
	{
		return VK_SHADER_STAGE_ALL;
	}

	if (shaderStage == AllGraphics)
	{
		return VK_SHADER_STAGE_ALL_GRAPHICS;
	}

	uint32_t result = 0;
	if (HasFlag<ShaderStage>(shaderStage, Compute))			result |= VK_SHADER_STAGE_COMPUTE_BIT;
	if (HasFlag<ShaderStage>(shaderStage, Vertex))			result |= VK_SHADER_STAGE_VERTEX_BIT;
	if (HasFlag<ShaderStage>(shaderStage, Hull))			result |= VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
	if (HasFlag<ShaderStage>(shaderStage, Domain))			result |= VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
	if (HasFlag<ShaderStage>(shaderStage, Geometry))		result |= VK_SHADER_STAGE_GEOMETRY_BIT;
	if (HasFlag<ShaderStage>(shaderStage, Pixel))			result |= VK_SHADER_STAGE_FRAGMENT_BIT;
	if (HasFlag<ShaderStage>(shaderStage, Amplification))	result |= VK_SHADER_STAGE_TASK_BIT_EXT;
	if (HasFlag<ShaderStage>(shaderStage, Mesh))			result |= VK_SHADER_STAGE_MESH_BIT_EXT;
	if (HasFlag<ShaderStage>(shaderStage, RayGeneration))	result |= VK_SHADER_STAGE_RAYGEN_BIT_KHR;
	if (HasFlag<ShaderStage>(shaderStage, Miss))			result |= VK_SHADER_STAGE_MISS_BIT_KHR;
	if (HasFlag<ShaderStage>(shaderStage, ClosestHit))		result |= VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR;
	if (HasFlag<ShaderStage>(shaderStage, AnyHit))			result |= VK_SHADER_STAGE_ANY_HIT_BIT_KHR;
	if (HasFlag<ShaderStage>(shaderStage, Intersection))	result |= VK_SHADER_STAGE_INTERSECTION_BIT_KHR;
	if (HasFlag<ShaderStage>(shaderStage, Callable))		result |= VK_SHADER_STAGE_CALLABLE_BIT_KHR;

	return (VkShaderStageFlags)result;
}


VkDescriptorType DescriptorTypeToVulkan(DescriptorType descriptorType)
{
	using enum DescriptorType;

	switch (descriptorType)
	{
	case CBV:					return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER; break;
	case DynamicCBV:			return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC; break;
	case Sampler:				return VK_DESCRIPTOR_TYPE_SAMPLER; break;
	case TextureSRV:			return VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE; break;
	case StructuredBufferSRV:	return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER; break;
	case StructuredBufferUAV:	return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER; break;
	case TextureUAV:			return VK_DESCRIPTOR_TYPE_STORAGE_IMAGE; break;
	case TypedBufferSRV:		return VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER; break;
	case TypedBufferUAV:		return VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER; break;
	default:
		assert(false);
		return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		break;
	}
}

} // namespace Kodiak::VK