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

namespace Kodiak::VK
{

ColorBuffer::ColorBuffer(const ColorBufferCreationParams& creationParams, const ColorBufferCreationParamsExt& creationParamsExt)
	: m_resourceType{ creationParams.resourceType }
	, m_width{ creationParams.width }
	, m_height{ creationParams.height }
	, m_arraySizeOrDepth{ creationParams.arraySizeOrDepth }
	, m_numMips{ creationParams.numMips }
	, m_numSamples{ creationParams.numSamples }
	, m_format{ creationParams.format }
	, m_name{ creationParams.name }
	, m_clearColor{ creationParams.clearColor }
	, m_numFragments{ 1 }
	, m_resource{ creationParamsExt.image }
	, m_usageState{ creationParamsExt.usageState }
	, m_transitioningState{ ResourceState::Undefined }
	, m_imageViewRtv{ creationParamsExt.imageViewRtv }
	, m_imageViewSrv{ creationParamsExt.imageViewSrv }
	, m_imageInfoSrv{ creationParamsExt.imageInfoSrv }
	, m_imageInfoUav{ creationParamsExt.imageInfoUav }
{
	m_numMips = m_numMips == 0 ? ComputeNumMips(m_width, m_height) : m_numMips;
}


NativeObjectPtr ColorBuffer::GetNativeObject(NativeObjectType nativeObjectType) const noexcept
{
	using enum NativeObjectType;

	switch (nativeObjectType)
	{
	case VK_Image:
		return NativeObjectPtr(*m_resource);
		break;
	default:
		return nullptr;
		break;
	}
}

} // namespace Kodiak::VK