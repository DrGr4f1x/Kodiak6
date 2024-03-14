//
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Author:  David Elder
//

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
	Copy
};


enum class ResourceState : uint32_t
{
	Undefined =							0x0000,
	Common =							0x0001,
	VertexBuffer =						0x0002,
	IndexBuffer =						0x0004,
	ConstantBuffer =					0x0008,
	RenderTarget =						0x0010,
	UnorderedAccess =					0x0020,
	DepthWrite =						0x0040,
	DepthRead =							0x0080,
	NonPixelShaderResource =			0x0100,
	PixelShaderResource =				0x0200,
	ShaderResource =					0x0400,
	StreamOut =							0x0800,
	IndirectArgument =					0x1000,
	CopyDest =							0x2000,
	CopySource =						0x4000,
	ResolveDest =						0x8000,
	ResolveSource =						0x010000,
	GenericRead =						0x020000,
	Present =							0x040000,
	Predication =						0x080000,
	RayTracingAccelerationStructure =	0x100000,
	ShadingRateSource =					0x200000
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
	ReadbackBuffer =		0x010000
};

template <> struct EnableBitmaskOperators<ResourceType> { static const bool enable = true; };


inline bool IsTextureResource(ResourceType resourceType)
{
	using enum ResourceType;

	return (resourceType >= Texture1D) && (resourceType <= Texture3D);
}


inline bool IsTextureArray(ResourceType resourceType)
{
	using enum ResourceType;

	return
		resourceType == Texture1D_Array ||
		resourceType == Texture2D_Array ||
		resourceType == Texture2DMS_Array ||
		resourceType == TextureCube ||
		resourceType == TextureCube_Array;
}


inline bool IsBufferResource(ResourceType resourceType)
{
	using enum ResourceType;

	return (resourceType > Texture3D);
}


inline uint32_t ComputeNumMips(uint32_t width, uint32_t height)
{
	uint32_t highBit{ 0 };
	_BitScanReverse((unsigned long*)&highBit, width | height);
	return highBit + 1;
}


enum class HardwareVendor
{
	Unknown,
	AMD,
	Intel,
	NVIDIA
};

inline std::string HardwareVendorToString(HardwareVendor hardwareVendor)
{
	using enum HardwareVendor;

	switch (hardwareVendor)
	{
	case AMD:		return std::string("AMD");			break;
	case Intel:		return std::string("Intel");		break;
	case NVIDIA:	return std::string("NVIDIA");		break;
	default:		return std::string("<Unknown>");	break;
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

	default:
		return Unknown;
		break;
	}
}

inline std::string VendorIdToString(uint32_t vendorId)
{
	return HardwareVendorToString(VendorIdToHardwareVendor(vendorId));
}

} // namespace Kodiak