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


namespace Kodiak::VK
{

DepthBuffer::DepthBuffer(const DepthBufferCreationParams& creationParams, const DepthBufferCreationParamsExt& creationParamsExt) noexcept
	: GpuImage{
		creationParamsExt.image,
		creationParams.width,
		creationParams.height,
		creationParams.arraySizeOrDepth,
		creationParams.numMips,
		creationParams.numSamples,
		creationParams.resourceType,
		creationParamsExt.usageState,
		creationParams.format }
	, m_name{ creationParams.name }
	, m_clearDepth{ creationParams.clearDepth }
	, m_clearStencil{ creationParams.clearStencil }
	, m_imageViewDepthStencil{ creationParamsExt.imageViewDepthStencil }
	, m_imageViewDepthOnly{ creationParamsExt.imageViewDepthOnly }
	, m_imageViewStencilOnly{ creationParamsExt.imageViewStencilOnly }
	, m_imageInfoDepth{ creationParamsExt.imageInfoDepth }
	, m_imageInfoStencil{ creationParamsExt.imageInfoStencil }
{
	m_numMips = m_numMips == 0 ? ComputeNumMips(m_width, m_height) : m_numMips;
}


NativeObjectPtr DepthBuffer::GetNativeObject(NativeObjectType nativeObjectType) const noexcept
{
	using enum NativeObjectType;

	switch (nativeObjectType)
	{
	case VK_Image:
		return NativeObjectPtr(*m_image);
		break;
	default:
		return nullptr;
		break;
	}
}

} // namespace Kodiak::VK