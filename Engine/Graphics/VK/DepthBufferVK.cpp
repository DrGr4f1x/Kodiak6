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

#include "CreationParamsVK.h"
#include "DeviceVK.h"
#include "QueueVK.h"


using namespace std;


namespace Kodiak::VK
{

DepthBuffer::DepthBuffer(const DepthBufferCreationParams& creationParams) noexcept
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
{}


void DepthBuffer::Initialize(GraphicsDevice* device)
{
	auto creationParams = ImageCreationParams{}
		.SetName(m_name)
		.SetWidth(m_width)
		.SetHeight(m_height)
		.SetNumMips(m_numMips)
		.SetNumSamples(m_numSamples)
		.SetFormat(m_format)
		.SetResourceType(m_resourceType)
		.SetImageUsage(GpuImageUsage::DepthStencilTarget | GpuImageUsage::ShaderResource | GpuImageUsage::CopyDest | GpuImageUsage::CopySource)
		.SetMemoryAccess(MemoryAccess::GpuRead | MemoryAccess::GpuWrite);

	m_image = device->CreateImage(creationParams);

	CreateDerivedViews(device);
}


void DepthBuffer::CreateDerivedViews(GraphicsDevice* device)
{
	const bool bHasStencil = IsStencilFormat(m_format);

	auto imageAspect = ImageAspect::Depth;
	if (bHasStencil)
	{
		imageAspect |= ImageAspect::Stencil;
	}

	auto creationParams = ImageViewCreationParams{}
		.SetImage(m_image)
		.SetName(format("{} DepthStencil Image View", m_name))
		.SetResourceType(m_resourceType)
		.SetImageUsage(GpuImageUsage::DepthStencilTarget)
		.SetFormat(m_format)
		.SetImageAspect(imageAspect)
		.SetBaseMipLevel(0)
		.SetMipCount(m_numMips)
		.SetBaseArraySlice(0)
		.SetArraySize(m_arraySizeOrDepth);

	m_imageViewDepthStencil = device->CreateImageView(creationParams);

	if (bHasStencil)
	{
		creationParams
			.SetName(format("{} Depth Image View", m_name))
			.SetImageAspect(ImageAspect::Depth);

		m_imageViewDepthOnly = device->CreateImageView(creationParams);

		creationParams
			.SetName(format("{} Stencil Image View", m_name))
			.SetImageAspect(ImageAspect::Stencil);

		m_imageViewStencilOnly = device->CreateImageView(creationParams);
	}
	else
	{
		m_imageViewDepthOnly = m_imageViewDepthStencil;
		m_imageViewStencilOnly = m_imageViewStencilOnly;
	}

	m_imageInfoDepth = { VK_NULL_HANDLE, *m_imageViewDepthOnly, GetImageLayout(ResourceState::ShaderResource) };
	m_imageInfoStencil = { VK_NULL_HANDLE, *m_imageViewStencilOnly, GetImageLayout(ResourceState::ShaderResource) };
}

} // namespace Kodiak::VK