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

#include "CreationParamsVK.h"
#include "DeviceVK.h"


namespace Kodiak::VK
{

ColorBuffer::ColorBuffer(const ColorBufferCreationParams& creationParams, const ColorBufferCreationParamsExt& creationParamsExt)
	: m_name{ creationParams.name }
	, m_resourceType{ creationParams.resourceType }
	, m_width{ creationParams.width }
	, m_height{ creationParams.height }
	, m_arraySizeOrDepth{ creationParams.arraySizeOrDepth }
	, m_numMips{ creationParams.numMips }
	, m_numSamples{ creationParams.numSamples }
	, m_format{ creationParams.format }
	, m_clearColor{ creationParams.clearColor }
	, m_image{ creationParamsExt.image }
{
	m_numMips = m_numMips == 0 ? ComputeNumMips(m_width, m_height) : m_numMips;
}


void ColorBuffer::InitializeFromSwapChain(GraphicsDevice* device)
{
	SetDebugName(device->GetVkDevice(), m_image->Get(), m_name);

	CreateDerivedViews(device, m_numMips);
}


void ColorBuffer::Initialize(GraphicsDevice* device)
{

}


void ColorBuffer::CreateDerivedViews(GraphicsDevice* device, uint32_t numMips)
{
	assert_msg(m_arraySizeOrDepth == 1 || numMips == 1, "We don't support auto-mips on texture arrays");

	m_numMips = numMips - 1;

	auto creationParams = ImageViewCreationParams{}
		.SetImage(m_image)
		.SetName(format("{} RTV Image View", m_name))
		.SetResourceType(m_resourceType)
		.SetImageUsage(GpuImageUsage::RenderTarget)
		.SetFormat(m_format)
		.SetImageAspect(ImageAspect::Color)
		.SetBaseMipLevel(0)
		.SetMipCount(numMips)
		.SetBaseArraySlice(0)
		.SetArraySize(m_arraySizeOrDepth);

	m_imageViewRtv = device->CreateImageView(creationParams);

	creationParams.SetImageUsage(GpuImageUsage::ShaderResource);
	m_imageViewSrv = device->CreateImageView(creationParams);

	m_imageInfoSrv = { VK_NULL_HANDLE, *m_imageViewSrv, GetImageLayout(ResourceState::ShaderResource) };
	m_imageInfoUav = { VK_NULL_HANDLE, *m_imageViewSrv, GetImageLayout(ResourceState::UnorderedAccess) };
}

} // namespace Kodiak::VK