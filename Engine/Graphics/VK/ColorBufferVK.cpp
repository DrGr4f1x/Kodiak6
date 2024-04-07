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

#include "ColorBufferVK.h"

#include "Graphics\CreationParams.h"
#include "CreationParamsVK.h"


namespace Kodiak::VK
{

ColorBuffer::ColorBuffer(const ColorBufferCreationParams& creationParams, const ColorBufferCreationParamsExt& creationParamsExt)
	: GpuResource{ creationParams.resourceType, creationParamsExt.image }
	, PixelBuffer{ creationParams.resourceType, creationParamsExt.image, creationParams.width, creationParams.height, creationParams.arraySizeOrDepth, creationParams.numMips, creationParams.numSamples, creationParams.format }
	, m_name{ creationParams.name }
	, m_clearColor{ creationParams.clearColor }
	, m_imageViewRtv{ creationParamsExt.imageViewRtv }
	, m_imageViewSrv{ creationParamsExt.imageViewSrv }
	, m_imageInfoSrv{ creationParamsExt.imageInfoSrv }
	, m_imageInfoUav{ creationParamsExt.imageInfoUav }
{}

} // namespace Kodiak::VK