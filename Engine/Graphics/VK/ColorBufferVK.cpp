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
#include "QueueVK.h"


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
	auto creationParams = ImageCreationParams{}
		.SetName(m_name)
		.SetWidth(m_width)
		.SetHeight(m_height)
		.SetNumMips(m_numMips)
		.SetNumSamples(m_numSamples)
		.SetFormat(m_format)
		.SetResourceType(m_resourceType)
		.SetImageUsage(GpuImageUsage::RenderTarget | GpuImageUsage::ShaderResource | GpuImageUsage::UnorderedAccess | GpuImageUsage::CopyDest | GpuImageUsage::CopySource)
		.SetMemoryAccess(MemoryAccess::GpuRead | MemoryAccess::GpuWrite);

	if (HasFlag(m_resourceType, ResourceType::Texture3D))
	{
		creationParams.SetNumMips(1);
		creationParams.SetDepth(m_arraySizeOrDepth);
	}
	else if (HasAnyFlag(m_resourceType, ResourceType::Texture2D_Type))
	{
		if (HasAnyFlag(m_resourceType, ResourceType::TextureArray_Type))
		{
			creationParams.SetResourceType(m_numSamples == 1 ? ResourceType::Texture2D_Array : ResourceType::Texture2DMS_Array);
			creationParams.SetArraySize(m_arraySizeOrDepth);
		}
		else
		{
			creationParams.SetResourceType(m_numSamples == 1 ? ResourceType::Texture2D : ResourceType::Texture2DMS_Array);
		}
	}

	m_image = device->CreateImage(creationParams);

	CreateDerivedViews(device, m_numMips);
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