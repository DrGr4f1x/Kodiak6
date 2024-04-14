//
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Author:  David Elder
//

#pragma once

#include "Graphics\VK\PixelBufferVK.h"
#include "Graphics\VK\VulkanCommon.h"


namespace Kodiak::VK
{

// Forward declarations
class GraphicsDevice;


struct DepthBufferCreationParamsExt
{
	VkImageHandle image;
	VkImageViewHandle imageViewDepthStencil;
	VkImageViewHandle imageViewDepthOnly;
	VkImageViewHandle imageViewStencilOnly;
	VkDescriptorImageInfo imageInfoDepth{};
	VkDescriptorImageInfo imageInfoStencil{};
	ImageAspect imageAspect{ 0 };
	ResourceState usageState{ ResourceState::Undefined };

	DepthBufferCreationParamsExt& SetImage(CVkImage* value) noexcept { image = value; return *this; }
	DepthBufferCreationParamsExt& SetImageViewDepthStencil(CVkImageView* value) noexcept { imageViewDepthStencil = value; return *this; }
	DepthBufferCreationParamsExt& SetImageViewDepthOnly(CVkImageView* value) noexcept { imageViewDepthOnly = value; return *this; }
	DepthBufferCreationParamsExt& SetImageViewStencilOnly(CVkImageView* value) noexcept { imageViewStencilOnly = value; return *this; }
	DepthBufferCreationParamsExt& SetImageInfoDepth(const VkDescriptorImageInfo& value) noexcept { imageInfoDepth = value; return *this; }
	DepthBufferCreationParamsExt& SetImageInfoStencil(const VkDescriptorImageInfo& value) noexcept { imageInfoStencil = value; return *this; }
	DepthBufferCreationParamsExt& SetImageAspect(const ImageAspect value) noexcept { imageAspect = value; return *this; }
	DepthBufferCreationParamsExt& SetUsageState(const ResourceState value) noexcept { usageState = value; return *this; }
};


#pragma warning(disable:4250)
class DepthBuffer : public IntrusiveCounter<IDepthBuffer>, public PixelBuffer
{
	friend class GraphicsDevice;

public:
	~DepthBuffer() final = default;

	// IDepthBuffer implementation
	float GetClearDepth() const noexcept final { return m_clearDepth;	}
	uint8_t GetClearStencil() const noexcept final { return m_clearStencil; }

	// Get pre-created CPU-visible descriptor handles
	VkImageView GetDepthStencilImageView() const noexcept { return *m_imageViewDepthStencil; }
	VkImageView GetDepthOnlyImageView() const noexcept { return *m_imageViewDepthOnly; }
	VkImageView GetStencilOnlyImageView() const noexcept { return *m_imageViewStencilOnly; }
	VkDescriptorImageInfo GetDepthImageInfo() const noexcept { return m_imageInfoDepth; }
	VkDescriptorImageInfo GetStencilImageInfo() const noexcept { return m_imageInfoStencil; }

private:
	DepthBuffer(const DepthBufferCreationParams& creationParams, const DepthBufferCreationParamsExt& creationParamsExt) noexcept;

private:
	const std::string m_name;
	float m_clearDepth{ 1.0f };
	uint8_t m_clearStencil{ 0 };

	VkImageViewHandle m_imageViewDepthStencil;
	VkImageViewHandle m_imageViewDepthOnly;
	VkImageViewHandle m_imageViewStencilOnly;
	VkDescriptorImageInfo m_imageInfoDepth{};
	VkDescriptorImageInfo m_imageInfoStencil{};
};
#pragma warning(default:4250)

} // namespace Kodiak::VK
