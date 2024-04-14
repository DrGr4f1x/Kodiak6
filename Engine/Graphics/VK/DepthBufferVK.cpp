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

#include "DepthBufferVK.h"

#include "Graphics\CreationParams.h"
#include "CreationParamsVK.h"


using namespace std;


namespace Kodiak::VK
{

DepthBuffer::DepthBuffer(const DepthBufferCreationParams& creationParams, const DepthBufferCreationParamsExt& creationParamsExt) noexcept
	: PixelBuffer{ 
		creationParams.resourceType, 
		creationParamsExt.image, 
		creationParamsExt.usageState,
		creationParams.width, creationParams.height, 
		creationParams.arraySizeOrDepth, 
		creationParams.numMips, 
		creationParams.numSamples, 
		creationParams.format,
		creationParamsExt.imageAspect }
	, m_name{ creationParams.name }
	, m_clearDepth{ creationParams.clearDepth }
	, m_clearStencil{ creationParams.clearStencil }
	, m_imageViewDepthStencil{ creationParamsExt.imageViewDepthStencil }
	, m_imageViewDepthOnly{ creationParamsExt.imageViewDepthOnly }
	, m_imageViewStencilOnly{ creationParamsExt.imageViewStencilOnly }
	, m_imageInfoDepth{ creationParamsExt.imageInfoDepth }
	, m_imageInfoStencil{ creationParamsExt.imageInfoStencil }
{}

} // namespace Kodiak::VK