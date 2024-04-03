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
	: m_name{ creationParams.name }
	, m_resourceType{ creationParams.resourceType }
	, m_width{ creationParams.width }
	, m_height{ creationParams.height }
	, m_arraySizeOrDepth{ 1 }
	, m_numMips{ 1 }
	, m_numSamples{ 1 }
	, m_format{ creationParams.format }
	, m_clearDepth{ creationParams.clearDepth }
	, m_clearStencil{ creationParams.clearStencil }
	, m_image{ creationParamsExt.image }
	, m_imageViewDepthStencil{ creationParamsExt.imageViewDepthStencil }
	, m_imageViewDepthOnly{ creationParamsExt.imageViewDepthOnly }
	, m_imageViewStencilOnly{ creationParamsExt.imageViewStencilOnly }
	, m_imageInfoDepth{ creationParamsExt.imageInfoDepth }
	, m_imageInfoStencil{ creationParamsExt.imageInfoStencil }
{}

} // namespace Kodiak::VK