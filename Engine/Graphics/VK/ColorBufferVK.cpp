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
	, m_clearColor{ creationParams.clearColor }
	, m_numFragments{ 1 }
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
		return NativeObjectPtr(*m_image);
		break;
	default:
		return nullptr;
		break;
	}
}

} // namespace Kodiak::VK