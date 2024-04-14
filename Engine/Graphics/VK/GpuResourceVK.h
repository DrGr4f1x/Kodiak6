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

#include "Graphics\Interfaces.h"
#include "Graphics\VK\VulkanCommon.h"


namespace Kodiak::VK
{

class GpuResource : public virtual IGpuResource
{
public:
	// IGpuResource
	ResourceType GetType() const noexcept override { return m_resourceType; }

	bool IsImageResource() const noexcept { return m_resource.index() == 0; }
	bool IsBufferResource() const noexcept { return m_resource.index() == 1; }

	VkImage GetImage() const { return *std::get<0>(m_resource); }
	VkBuffer GetBuffer() const { return *std::get<1>(m_resource); }
	ResourceState GetUsageState() const noexcept { return m_usageState; }

protected:
	GpuResource() = default;

	GpuResource(ResourceType resourceType, CVkImage* image, ResourceState usageState)
		: m_resourceType{ resourceType }
		, m_resource{ VkImageHandle::Create(image) }
		, m_usageState{ usageState }
	{}


	GpuResource(ResourceType resourceType, CVkBuffer* buffer, ResourceState usageState)
		: m_resourceType{ resourceType }
		, m_resource{ VkBufferHandle::Create(buffer) }
		, m_usageState{ usageState }
	{}

protected:
	ResourceType m_resourceType{ ResourceType::Texture2D };

	std::variant<VkImageHandle, VkBufferHandle> m_resource;
	ResourceState m_usageState{ ResourceState::Undefined };
	ResourceState m_transitioningState{ ResourceState::Undefined };
};

} // namespace Kodiak::VK
