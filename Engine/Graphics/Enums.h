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

namespace Kodiak
{

enum class Blend : uint8_t
{
	Zero,
	One,
	SrcColor,
	InvSrcColor,
	SrcAlpha,
	InvSrcAlpha,
	DstAlpha,
	InvDstAlpha,
	DstColor,
	InvDstColor,
	SrcAlphaSat,
	BlendFactor,
	InvBlendFactor,
	AlphaFactor,
	InvAlphaFactor,
	Src1Color,
	InvSrc1Color,
	Src1Alpha,
	InvSrc1Alpha
};


enum class BlendOp : uint8_t
{
	Add,
	Subtract,
	RevSubtract,
	Min,
	Max
};


enum class LogicOp : uint8_t
{
	Clear,
	Set,
	Copy,
	CopyInverted,
	Noop,
	Invert,
	And,
	Nand,
	Or,
	Nor,
	Xor,
	Equiv,
	AndReverse,
	OrReverse,
	OrInverted
};


enum class ColorWrite : uint8_t
{
	None =		0,
	Red =		1,
	Green =		2,
	Blue =		4,
	Alpha =		8,
	All =		Red | Green | Blue | Alpha
};

template <> struct EnableBitmaskOperators<ColorWrite> { static const bool enable = true; };


enum class DepthWrite : uint8_t
{
	Zero = 0,
	All = 1
};


enum class CullMode : uint8_t
{
	None,
	Front,
	Back
};


enum class FillMode : uint8_t
{
	Wireframe,
	Solid
};


enum class ComparisonFunc : uint8_t
{
	Never,
	Less,
	Equal,
	LessEqual,
	Greater,
	NotEqual,
	GreaterEqual,
	Always
};


enum class StencilOp : uint8_t
{
	Keep,
	Zero,
	Replace,
	IncrSat,
	DecrSat,
	Invert,
	Incr,
	Decr
};


enum class IndexBufferStripCutValue : uint8_t
{
	Disabled,
	Value_0xFFFF,
	Value_0xFFFFFFFF
};


enum class PrimitiveTopology : uint8_t
{
	PointList,
	LineList,
	LineStrip,
	TriangleList,
	TriangleStrip,
	LineListWithAdjacency,
	LineStripWithAdjacency,
	TriangleListWithAdjacency,
	TriangleStripWithAdjacency,
	PatchList_1_ControlPoint,
	PatchList_2_ControlPoint,
	PatchList_3_ControlPoint,
	PatchList_4_ControlPoint,
	PatchList_5_ControlPoint,
	PatchList_6_ControlPoint,
	PatchList_7_ControlPoint,
	PatchList_8_ControlPoint,
	PatchList_9_ControlPoint,
	PatchList_10_ControlPoint,
	PatchList_11_ControlPoint,
	PatchList_12_ControlPoint,
	PatchList_13_ControlPoint,
	PatchList_14_ControlPoint,
	PatchList_15_ControlPoint,
	PatchList_16_ControlPoint,
	PatchList_17_ControlPoint,
	PatchList_18_ControlPoint,
	PatchList_19_ControlPoint,
	PatchList_20_ControlPoint,
	PatchList_21_ControlPoint,
	PatchList_22_ControlPoint,
	PatchList_23_ControlPoint,
	PatchList_24_ControlPoint,
	PatchList_25_ControlPoint,
	PatchList_26_ControlPoint,
	PatchList_27_ControlPoint,
	PatchList_28_ControlPoint,
	PatchList_29_ControlPoint,
	PatchList_30_ControlPoint,
	PatchList_31_ControlPoint,
	PatchList_32_ControlPoint
};


enum class ShaderStage : uint16_t
{
	None =				0x0000,
	
	Compute =			0x0020,
	
	Vertex =			0x0001,
	Hull =				0x0002,
	Domain =			0x0004,
	Geometry =			0x0008,
	Pixel =				0x0010,
	Amplification =		0x0040,
	Mesh =				0x0080,
	AllGraphics =		0x00FE,

	RayGeneration =		0x0100,
	AnyHit =			0x0200,
	ClosestHit =		0x0400,
	Miss =				0x0800,
	Intersection =		0x1000,
	Callable =			0x2000,
	AllRaytracing =		0x3F00,

	All =				0x3FFF
};

template <> struct EnableBitmaskOperators<ShaderStage> { static const bool enable = true; };


enum class DescriptorType
{
	CBV,
	DynamicCBV,
	Sampler,
	TextureSRV,
	TypedBufferSRV,
	StructuredBufferSRV,
	TextureUAV,
	TypedBufferUAV,
	StructuredBufferUAV
};


enum class RootSignatureFlags
{
	None =								0x0000,
	AllowInputAssemblerInputLayout =	0x0001,
	DenyVertexShaderRootAccess =		0x0002,
	DenyHullShaderRootAccess =			0x0004,
	DenyDomainShaderRootAccess =		0x0008,
	DenyGeometryShaderRootAccess =		0x0010,
	DenyPixelShaderRootAccess =			0x0020,
	AllowStreamOutput =					0x0040,
	LocalRootSignature =				0x0080,
	DenyAmplificationShaderRootAccess =	0x0100,
	DenyMeshShaderRootAccess =			0x0200,
	CbvSrvUavHeapDirectlyIndexed =		0x0400,
	SamplerHeapDirectlyIndexed =		0x0800
};

template <> struct EnableBitmaskOperators<RootSignatureFlags> { static const bool enable = true; };


enum class TextureFilter
{
	MinMagMipPoint,
	MinMagPointMipLinear,
	MinPointMagLinearMipPoint,
	MinPointMagMipLinear,
	MinLinearMagMipPoint,
	MinLinearMagPointMipLinear,
	MinMagLinearMipPoint,
	MinMagMipLinear,
	Anisotropic,

	ComparisonMinMagMipPoint,
	ComparisonMinMagPointMipLinear,
	ComparisonMinPointMagLinearMipPoint,
	ComparisonMinPointMagMipLinear,
	ComparisonMinLinearMagMipPoint,
	ComparisonMinLinearMagPointMipLinear,
	ComparisonMinMagLinearMipPoint,
	ComparisonMinMagMipLinear,
	ComparisonAnisotropic,

	MinimumMinMagMipPoint,
	MinimumMinMagPointMipLinear,
	MinimumMinPointMagLinearMipPoint,
	MinimumMinPointMagMipLinear,
	MinimumMinLinearMagMipPoint,
	MinimumMinLinearMagPointMipLinear,
	MinimumMinMagLinearMipPoint,
	MinimumMinMagMipLinear,
	MinimumAnisotropic,

	MaximumMinMagMipPoint,
	MaximumMinMagPointMipLinear,
	MaximumMinPointMagLinearMipPoint,
	MaximumMinPointMagMipLinear,
	MaximumMinLinearMagMipPoint,
	MaximumMinLinearMagPointMipLinear,
	MaximumMinMagLinearMipPoint,
	MaximumMinMagMipLinear,
	MaximumAnisotropic,

	Count
};


enum class TextureAddress : uint8_t
{
	Wrap,
	Mirror,
	Clamp,
	Border,
	MirrorOnce
};


enum class InputClassification : uint8_t
{
	PerVertexData,
	PerInstanceData
};


enum class CommandListType : uint8_t
{
	Direct,
	Bundle,
	Compute,
	Copy,

	Count
};


inline std::string EngineTypeToString(CommandListType commandListType)
{
	using enum CommandListType;

	switch (commandListType)
	{
	case Bundle:	return "Bundle"; break;
	case Compute:	return "Compute"; break;
	case Copy:		return "Copy"; break;
	default:		return "Direct"; break;
	}
}


enum class ResourceState : uint32_t
{
	Undefined =						0,
	Common =						0x00000001,
	ConstantBuffer =				0x00000002,
	VertexBuffer =					0x00000004,
	IndexBuffer =					0x00000008,
	IndirectArgument =				0x00000010,
	ShaderResource =				0x00000020,
	UnorderedAccess =				0x00000040,
	RenderTarget =					0x00000080,
	DepthWrite =					0x00000100,
	DepthRead =						0x00000200,
	StreamOut =						0x00000400,
	CopyDest =						0x00000800,
	CopySource =					0x00001000,
	ResolveDest =					0x00002000,
	ResolveSource =					0x00004000,
	Present =						0x00008000,
	AccelStructRead =				0x00010000,
	AccelStructWrite =				0x00020000,
	AccelStructBuildInput =			0x00040000,
	AccelStructBuildBlas =			0x00080000,
	ShadingRateSurface =			0x00100000,
	OpacityMicromapWrite =			0x00200000,
	OpacityMicromapBuildInput =		0x00400000,
	Predication =					0x00800000,
};

template <> struct EnableBitmaskOperators<ResourceState> { static const bool enable = true; };


enum class QueryType : uint8_t
{
	Occlusion,
	Timestamp,
	PipelineStats
};


enum class RootParameterType : uint8_t
{
	Invalid,
	DescriptorTable,
	RootConstants,
	RootCBV,
	DynamicRootCBV
};


enum class ResourceType : uint32_t
{
	Unknown =				0x0000,
	Texture1D =				0x0001,
	Texture1D_Array =		0x0002,
	Texture2D =				0x0004,
	Texture2D_Array =		0x0008,
	Texture2DMS =			0x0010,
	Texture2DMS_Array =		0x0020,
	TextureCube =			0x0040,
	TextureCube_Array =		0x0080,
	Texture3D =				0x0100,
	IndexBuffer =			0x0200,
	VertexBuffer =			0x0400,
	ConstantBuffer =		0x0800,
	ByteAddressBuffer =		0x1000,
	IndirectArgsBuffer =	0x2000,
	StructuredBuffer =		0x4000,
	TypedBuffer =			0x8000,
	ReadbackBuffer =		0x010000,

	Texture1D_Type =		Texture1D | Texture1D_Array,
	Texture2D_Type =		Texture2D | Texture2D_Array | Texture2DMS | Texture2DMS_Array,
	TextureCube_Type =		TextureCube | TextureCube_Array,
	TextureArray_Type =		Texture1D_Array | Texture2D_Array | Texture2DMS_Array | TextureCube_Array
};
template <> struct EnableBitmaskOperators<ResourceType> { static const bool enable = true; };


enum class QueueType : uint8_t
{
	Graphics,
	Compute,
	Copy,

	Count
};


inline std::string EngineTypeToString(QueueType queueType)
{
	switch (queueType)
	{
	case QueueType::Compute:	return "Compute"; break;
	case QueueType::Copy:		return "Copy"; break;
	default:					return "Graphics"; break;
	}
}

enum class HardwareVendor
{
	Unknown,
	AMD,
	Intel,
	NVIDIA,
	Microsoft
};


inline std::string HardwareVendorToString(HardwareVendor hardwareVendor)
{
	using enum HardwareVendor;

	switch (hardwareVendor)
	{
	case AMD:		return "AMD"; break;
	case Intel:		return "Intel";	break;
	case NVIDIA:	return "NVIDIA"; break;
	case Microsoft: return "Microsoft"; break;
	default:		return "Unknown"; break;
	}
}


inline HardwareVendor VendorIdToHardwareVendor(uint32_t vendorId)
{
	using enum HardwareVendor;

	switch (vendorId)
	{
	case 0x10de:
		return NVIDIA;
		break;

	case 0x1002:
	case 0x1022:
		return AMD;
		break;

	case 0x163c:
	case 0x8086:
	case 0x8087:
		return Intel;
		break;

	case 0x1414:
		return Microsoft;
		break;

	default:
		return Unknown;
		break;
	}
}


inline std::string VendorIdToString(uint32_t vendorId)
{
	return HardwareVendorToString(VendorIdToHardwareVendor(vendorId));
}


enum class AdapterType : uint8_t
{
	Discrete,
	Integrated,
	Software,
	Other
};


inline std::string AdapterTypeToString(AdapterType adapterType)
{
	using enum AdapterType;

	switch (adapterType)
	{
	case Discrete:		return "Discrete"; break;
	case Integrated:	return "Integrated"; break;
	case Software:		return "Software"; break;
	default:			return "Other"; break;
	}
}


inline CommandListType QueueTypeToCommandListType(QueueType queueType)
{
	switch (queueType)
	{
	case QueueType::Compute:	return CommandListType::Compute; break;
	case QueueType::Copy:		return CommandListType::Copy; break;
	default:					return CommandListType::Direct; break;
	}
}


inline QueueType CommandListTypeToQueueType(CommandListType commandListType)
{
	switch (commandListType)
	{
	case CommandListType::Compute:	return QueueType::Compute; break;
	case CommandListType::Copy:		return QueueType::Copy; break;
	default:						return QueueType::Graphics; break;
	}
}


enum class GpuImageUsage
{
	Unknown =				0,
	RenderTarget =			1 << 0,
	DepthStencilTarget =	1 << 1,
	ShaderResource =		1 << 2,
	UnorderedAccess =		1 << 3,
	CopySource =			1 << 4,
	CopyDest =				1 << 5,
};
template <> struct EnableBitmaskOperators<GpuImageUsage> { static const bool enable = true; };


enum class ImageAspect
{
	Color =		1 << 0,
	Depth =		1 << 1,
	Stencil =	1 << 2
};
template <> struct EnableBitmaskOperators<ImageAspect> { static const bool enable = true; };


enum class MemoryAccess
{
	Unknown =		0,
	GpuRead =		1 << 0,
	GpuWrite =		1 << 1,
	CpuRead =		1 << 2,
	CpuWrite =		1 << 3,
	CpuMapped =		1 << 4
};
template <> struct EnableBitmaskOperators<MemoryAccess> { static const bool enable = true; };


enum class NativeObjectType : uint32_t
{
	// DX12
	DX12_Resource	= 0x00010001,

	// Vulkan
	VK_Image		= 0x00020001,
	VK_Buffer		= 0x00020002,
};

} // namespace Kodiak


#define DECLARE_STRING_FORMATTERS(ENGINE_TYPE) \
template <> \
struct std::formatter<ENGINE_TYPE> : public std::formatter<std::string> \
{ \
	auto format(ENGINE_TYPE value, std::format_context& ctx) const \
	{ \
		auto str = Kodiak::EngineTypeToString(value); \
		return std::formatter<std::string>::format(str, ctx); \
	} \
}; \
inline std::ostream& operator<<(ENGINE_TYPE type, std::ostream& os) { os << Kodiak::EngineTypeToString(type); return os; }


DECLARE_STRING_FORMATTERS(Kodiak::CommandListType)
DECLARE_STRING_FORMATTERS(Kodiak::QueueType)


#undef DECLARE_STRING_FORMATTERS