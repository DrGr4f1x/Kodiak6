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

#include "Formats12.h"

namespace Kodiak::DX12
{

static const std::array<DxgiFormatMapping, (size_t)Kodiak::Format::Count> s_formatMap = { {
	{ Format::Unknown,              DXGI_FORMAT_UNKNOWN,                DXGI_FORMAT_UNKNOWN,                  DXGI_FORMAT_UNKNOWN                },
	{ Format::R8_UInt,              DXGI_FORMAT_R8_TYPELESS,            DXGI_FORMAT_R8_UINT,                  DXGI_FORMAT_R8_UINT                },
	{ Format::R8_SInt,              DXGI_FORMAT_R8_TYPELESS,            DXGI_FORMAT_R8_SINT,                  DXGI_FORMAT_R8_SINT                },
	{ Format::R8_UNorm,             DXGI_FORMAT_R8_TYPELESS,            DXGI_FORMAT_R8_UNORM,                 DXGI_FORMAT_R8_UNORM               },
	{ Format::R8_SNorm,             DXGI_FORMAT_R8_TYPELESS,            DXGI_FORMAT_R8_SNORM,                 DXGI_FORMAT_R8_SNORM               },
	{ Format::RG8_UInt,             DXGI_FORMAT_R8G8_TYPELESS,          DXGI_FORMAT_R8G8_UINT,                DXGI_FORMAT_R8G8_UINT              },
	{ Format::RG8_SInt,             DXGI_FORMAT_R8G8_TYPELESS,          DXGI_FORMAT_R8G8_SINT,                DXGI_FORMAT_R8G8_SINT              },
	{ Format::RG8_UNorm,            DXGI_FORMAT_R8G8_TYPELESS,          DXGI_FORMAT_R8G8_UNORM,               DXGI_FORMAT_R8G8_UNORM             },
	{ Format::RG8_SNorm,            DXGI_FORMAT_R8G8_TYPELESS,          DXGI_FORMAT_R8G8_SNORM,               DXGI_FORMAT_R8G8_SNORM             },
	{ Format::R16_UInt,             DXGI_FORMAT_R16_TYPELESS,           DXGI_FORMAT_R16_UINT,                 DXGI_FORMAT_R16_UINT               },
	{ Format::R16_SInt,             DXGI_FORMAT_R16_TYPELESS,           DXGI_FORMAT_R16_SINT,                 DXGI_FORMAT_R16_SINT               },
	{ Format::R16_UNorm,            DXGI_FORMAT_R16_TYPELESS,           DXGI_FORMAT_R16_UNORM,                DXGI_FORMAT_R16_UNORM              },
	{ Format::R16_SNorm,            DXGI_FORMAT_R16_TYPELESS,           DXGI_FORMAT_R16_SNORM,                DXGI_FORMAT_R16_SNORM              },
	{ Format::R16_Float,            DXGI_FORMAT_R16_TYPELESS,           DXGI_FORMAT_R16_FLOAT,                DXGI_FORMAT_R16_FLOAT              },
	{ Format::BGRA4_UNorm,          DXGI_FORMAT_B4G4R4A4_UNORM,         DXGI_FORMAT_B4G4R4A4_UNORM,           DXGI_FORMAT_B4G4R4A4_UNORM         },
	{ Format::B5G6R5_UNorm,         DXGI_FORMAT_B5G6R5_UNORM,           DXGI_FORMAT_B5G6R5_UNORM,             DXGI_FORMAT_B5G6R5_UNORM           },
	{ Format::B5G5R5A1_UNorm,       DXGI_FORMAT_B5G5R5A1_UNORM,         DXGI_FORMAT_B5G5R5A1_UNORM,           DXGI_FORMAT_B5G5R5A1_UNORM         },
	{ Format::RGBA8_UInt,           DXGI_FORMAT_R8G8B8A8_TYPELESS,      DXGI_FORMAT_R8G8B8A8_UINT,            DXGI_FORMAT_R8G8B8A8_UINT          },
	{ Format::RGBA8_SInt,           DXGI_FORMAT_R8G8B8A8_TYPELESS,      DXGI_FORMAT_R8G8B8A8_SINT,            DXGI_FORMAT_R8G8B8A8_SINT          },
	{ Format::RGBA8_UNorm,          DXGI_FORMAT_R8G8B8A8_TYPELESS,      DXGI_FORMAT_R8G8B8A8_UNORM,           DXGI_FORMAT_R8G8B8A8_UNORM         },
	{ Format::RGBA8_SNorm,          DXGI_FORMAT_R8G8B8A8_TYPELESS,      DXGI_FORMAT_R8G8B8A8_SNORM,           DXGI_FORMAT_R8G8B8A8_SNORM         },
	{ Format::BGRA8_UNorm,          DXGI_FORMAT_B8G8R8A8_TYPELESS,      DXGI_FORMAT_B8G8R8A8_UNORM,           DXGI_FORMAT_B8G8R8A8_UNORM         },
	{ Format::SRGBA8_UNorm,         DXGI_FORMAT_R8G8B8A8_TYPELESS,      DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,      DXGI_FORMAT_R8G8B8A8_UNORM_SRGB    },
	{ Format::SBGRA8_UNorm,         DXGI_FORMAT_B8G8R8A8_TYPELESS,      DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,      DXGI_FORMAT_B8G8R8A8_UNORM_SRGB    },
	{ Format::R10G10B10A2_UNorm,    DXGI_FORMAT_R10G10B10A2_TYPELESS,   DXGI_FORMAT_R10G10B10A2_UNORM,        DXGI_FORMAT_R10G10B10A2_UNORM      },
	{ Format::R11G11B10_Float,      DXGI_FORMAT_R11G11B10_FLOAT,        DXGI_FORMAT_R11G11B10_FLOAT,          DXGI_FORMAT_R11G11B10_FLOAT        },
	{ Format::RG16_UInt,            DXGI_FORMAT_R16G16_TYPELESS,        DXGI_FORMAT_R16G16_UINT,              DXGI_FORMAT_R16G16_UINT            },
	{ Format::RG16_SInt,            DXGI_FORMAT_R16G16_TYPELESS,        DXGI_FORMAT_R16G16_SINT,              DXGI_FORMAT_R16G16_SINT            },
	{ Format::RG16_UNorm,           DXGI_FORMAT_R16G16_TYPELESS,        DXGI_FORMAT_R16G16_UNORM,             DXGI_FORMAT_R16G16_UNORM           },
	{ Format::RG16_SNorm,           DXGI_FORMAT_R16G16_TYPELESS,        DXGI_FORMAT_R16G16_SNORM,             DXGI_FORMAT_R16G16_SNORM           },
	{ Format::RG16_Float,           DXGI_FORMAT_R16G16_TYPELESS,        DXGI_FORMAT_R16G16_FLOAT,             DXGI_FORMAT_R16G16_FLOAT           },
	{ Format::R32_UInt,             DXGI_FORMAT_R32_TYPELESS,           DXGI_FORMAT_R32_UINT,                 DXGI_FORMAT_R32_UINT               },
	{ Format::R32_SInt,             DXGI_FORMAT_R32_TYPELESS,           DXGI_FORMAT_R32_SINT,                 DXGI_FORMAT_R32_SINT               },
	{ Format::R32_Float,            DXGI_FORMAT_R32_TYPELESS,           DXGI_FORMAT_R32_FLOAT,                DXGI_FORMAT_R32_FLOAT              },
	{ Format::RGBA16_UInt,          DXGI_FORMAT_R16G16B16A16_TYPELESS,  DXGI_FORMAT_R16G16B16A16_UINT,        DXGI_FORMAT_R16G16B16A16_UINT      },
	{ Format::RGBA16_SInt,          DXGI_FORMAT_R16G16B16A16_TYPELESS,  DXGI_FORMAT_R16G16B16A16_SINT,        DXGI_FORMAT_R16G16B16A16_SINT      },
	{ Format::RGBA16_Float,         DXGI_FORMAT_R16G16B16A16_TYPELESS,  DXGI_FORMAT_R16G16B16A16_FLOAT,       DXGI_FORMAT_R16G16B16A16_FLOAT     },
	{ Format::RGBA16_UNorm,         DXGI_FORMAT_R16G16B16A16_TYPELESS,  DXGI_FORMAT_R16G16B16A16_UNORM,       DXGI_FORMAT_R16G16B16A16_UNORM     },
	{ Format::RGBA16_SNorm,         DXGI_FORMAT_R16G16B16A16_TYPELESS,  DXGI_FORMAT_R16G16B16A16_SNORM,       DXGI_FORMAT_R16G16B16A16_SNORM     },
	{ Format::RG32_UInt,            DXGI_FORMAT_R32G32_TYPELESS,        DXGI_FORMAT_R32G32_UINT,              DXGI_FORMAT_R32G32_UINT            },
	{ Format::RG32_SInt,            DXGI_FORMAT_R32G32_TYPELESS,        DXGI_FORMAT_R32G32_SINT,              DXGI_FORMAT_R32G32_SINT            },
	{ Format::RG32_Float,           DXGI_FORMAT_R32G32_TYPELESS,        DXGI_FORMAT_R32G32_FLOAT,             DXGI_FORMAT_R32G32_FLOAT           },
	{ Format::RGB32_UInt,           DXGI_FORMAT_R32G32B32_TYPELESS,     DXGI_FORMAT_R32G32B32_UINT,           DXGI_FORMAT_R32G32B32_UINT         },
	{ Format::RGB32_SInt,           DXGI_FORMAT_R32G32B32_TYPELESS,     DXGI_FORMAT_R32G32B32_SINT,           DXGI_FORMAT_R32G32B32_SINT         },
	{ Format::RGB32_Float,          DXGI_FORMAT_R32G32B32_TYPELESS,     DXGI_FORMAT_R32G32B32_FLOAT,          DXGI_FORMAT_R32G32B32_FLOAT        },
	{ Format::RGBA32_UInt,          DXGI_FORMAT_R32G32B32A32_TYPELESS,  DXGI_FORMAT_R32G32B32A32_UINT,        DXGI_FORMAT_R32G32B32A32_UINT      },
	{ Format::RGBA32_SInt,          DXGI_FORMAT_R32G32B32A32_TYPELESS,  DXGI_FORMAT_R32G32B32A32_SINT,        DXGI_FORMAT_R32G32B32A32_SINT      },
	{ Format::RGBA32_Float,         DXGI_FORMAT_R32G32B32A32_TYPELESS,  DXGI_FORMAT_R32G32B32A32_FLOAT,       DXGI_FORMAT_R32G32B32A32_FLOAT     },

	{ Format::D16,                  DXGI_FORMAT_R16_TYPELESS,           DXGI_FORMAT_R16_UNORM,                DXGI_FORMAT_D16_UNORM              },
	{ Format::D24S8,                DXGI_FORMAT_R24G8_TYPELESS,         DXGI_FORMAT_R24_UNORM_X8_TYPELESS,    DXGI_FORMAT_D24_UNORM_S8_UINT      },
	{ Format::X24G8_UInt,           DXGI_FORMAT_R24G8_TYPELESS,         DXGI_FORMAT_X24_TYPELESS_G8_UINT,     DXGI_FORMAT_D24_UNORM_S8_UINT      },
	{ Format::D32,                  DXGI_FORMAT_R32_TYPELESS,           DXGI_FORMAT_R32_FLOAT,                DXGI_FORMAT_D32_FLOAT              },
	{ Format::D32S8,                DXGI_FORMAT_R32G8X24_TYPELESS,      DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS, DXGI_FORMAT_D32_FLOAT_S8X24_UINT   },
	{ Format::X32G8_UInt,           DXGI_FORMAT_R32G8X24_TYPELESS,      DXGI_FORMAT_X32_TYPELESS_G8X24_UINT,  DXGI_FORMAT_D32_FLOAT_S8X24_UINT   },

	{ Format::BC1_UNorm,            DXGI_FORMAT_BC1_TYPELESS,           DXGI_FORMAT_BC1_UNORM,                DXGI_FORMAT_BC1_UNORM              },
	{ Format::BC1_UNorm_Srgb,       DXGI_FORMAT_BC1_TYPELESS,           DXGI_FORMAT_BC1_UNORM_SRGB,           DXGI_FORMAT_BC1_UNORM_SRGB         },
	{ Format::BC2_UNorm,            DXGI_FORMAT_BC2_TYPELESS,           DXGI_FORMAT_BC2_UNORM,                DXGI_FORMAT_BC2_UNORM              },
	{ Format::BC2_UNorm_Srgb,       DXGI_FORMAT_BC2_TYPELESS,           DXGI_FORMAT_BC2_UNORM_SRGB,           DXGI_FORMAT_BC2_UNORM_SRGB         },
	{ Format::BC3_UNorm,            DXGI_FORMAT_BC3_TYPELESS,           DXGI_FORMAT_BC3_UNORM,                DXGI_FORMAT_BC3_UNORM              },
	{ Format::BC3_UNorm_Srgb,       DXGI_FORMAT_BC3_TYPELESS,           DXGI_FORMAT_BC3_UNORM_SRGB,           DXGI_FORMAT_BC3_UNORM_SRGB         },
	{ Format::BC4_UNorm,            DXGI_FORMAT_BC4_TYPELESS,           DXGI_FORMAT_BC4_UNORM,                DXGI_FORMAT_BC4_UNORM              },
	{ Format::BC4_SNorm,            DXGI_FORMAT_BC4_TYPELESS,           DXGI_FORMAT_BC4_SNORM,                DXGI_FORMAT_BC4_SNORM              },
	{ Format::BC5_UNorm,            DXGI_FORMAT_BC5_TYPELESS,           DXGI_FORMAT_BC5_UNORM,                DXGI_FORMAT_BC5_UNORM              },
	{ Format::BC5_SNorm,            DXGI_FORMAT_BC5_TYPELESS,           DXGI_FORMAT_BC5_SNORM,                DXGI_FORMAT_BC5_SNORM              },
	{ Format::BC6H_UFloat,          DXGI_FORMAT_BC6H_TYPELESS,          DXGI_FORMAT_BC6H_UF16,                DXGI_FORMAT_BC6H_UF16              },
	{ Format::BC6H_SFloat,          DXGI_FORMAT_BC6H_TYPELESS,          DXGI_FORMAT_BC6H_SF16,                DXGI_FORMAT_BC6H_SF16              },
	{ Format::BC7_UNorm,            DXGI_FORMAT_BC7_TYPELESS,           DXGI_FORMAT_BC7_UNORM,                DXGI_FORMAT_BC7_UNORM              },
	{ Format::BC7_UNorm_Srgb,       DXGI_FORMAT_BC7_TYPELESS,           DXGI_FORMAT_BC7_UNORM_SRGB,           DXGI_FORMAT_BC7_UNORM_SRGB         },
}};


const DxgiFormatMapping& EngineFormatToDxgi(Format engineFormat)
{
	assert(engineFormat < Format::Count);
	assert(s_formatMap[(uint32_t)engineFormat].engineFormat == engineFormat);

	return s_formatMap[(uint32_t)engineFormat];
}

} // namespace Kodiak::DX12