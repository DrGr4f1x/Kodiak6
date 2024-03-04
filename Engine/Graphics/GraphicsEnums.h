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

} // namespace Kodiak