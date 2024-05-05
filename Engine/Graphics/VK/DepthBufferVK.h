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
	ResourceState usageState{ ResourceState::Undefined };

	DepthBufferCreationParamsExt& SetImage(CVkImage* value) noexcept { image = value; return *this; }
	DepthBufferCreationParamsExt& SetImageViewDepthStencil(CVkImageView* value) noexcept { imageViewDepthStencil = value; return *this; }
	DepthBufferCreationParamsExt& SetImageViewDepthOnly(CVkImageView* value) noexcept { imageViewDepthOnly = value; return *this; }
	DepthBufferCreationParamsExt& SetImageViewStencilOnly(CVkImageView* value) noexcept { imageViewStencilOnly = value; return *this; }
	DepthBufferCreationParamsExt& SetImageInfoDepth(const VkDescriptorImageInfo& value) noexcept { imageInfoDepth = value; return *this; }
	DepthBufferCreationParamsExt& SetImageInfoStencil(const VkDescriptorImageInfo& value) noexcept { imageInfoStencil = value; return *this; }
	DepthBufferCreationParamsExt& SetUsageState(const ResourceState value) noexcept { usageState = value; return *this; }
};


#pragma warning(disable:4250)
class DepthBuffer : public IDepthBuffer
{
	IMPLEMENT_IOBJECT

	friend class GraphicsDevice;

public:
	~DepthBuffer() final = default;

	// IObject implementation
	NativeObjectPtr GetNativeObject(NativeObjectType nativeObjectType) const noexcept override;

	// IGpuImage implementation
	ResourceType GetType() const noexcept override { return m_resourceType; }
	uint64_t GetWidth() const noexcept override { return m_width; }
	uint32_t GetHeight() const noexcept override { return m_height; }
	uint32_t GetDepth() const noexcept override { return m_resourceType == ResourceType::Texture3D ? m_arraySizeOrDepth : 1; }
	uint32_t GetArraySize() const noexcept override { return m_resourceType == ResourceType::Texture3D ? 1 : m_arraySizeOrDepth; }
	uint32_t GetNumMips() const noexcept override { return m_numMips; }
	uint32_t GetNumSamples() const noexcept override { return m_numSamples; }
	Format GetFormat() const noexcept override { return m_format; }
	uint32_t GetPlaneCount() const noexcept override { return 1; }

	ResourceState GetUsageState() const noexcept override { return m_usageState; }
	void SetUsageState(ResourceState usageState) noexcept override { m_usageState = usageState; }

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
	ResourceType m_resourceType{ ResourceType::Texture2D };
	uint64_t m_width{ 0 };
	uint32_t m_height{ 0 };
	uint32_t m_arraySizeOrDepth{ 0 };
	uint32_t m_numMips{ 1 };
	uint32_t m_numSamples{ 1 };
	Format m_format{ Format::Unknown };

	const std::string m_name;
	float m_clearDepth{ 1.0f };
	uint8_t m_clearStencil{ 0 };

	VkImageHandle m_resource;
	ResourceState m_usageState{ ResourceState::Undefined };
	ResourceState m_transitioningState{ ResourceState::Undefined };

	VkImageViewHandle m_imageViewDepthStencil;
	VkImageViewHandle m_imageViewDepthOnly;
	VkImageViewHandle m_imageViewStencilOnly;
	VkDescriptorImageInfo m_imageInfoDepth{};
	VkDescriptorImageInfo m_imageInfoStencil{};
};
#pragma warning(default:4250)

} // namespace Kodiak::VK
