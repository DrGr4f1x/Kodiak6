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

protected:
	GpuResource() = default;

	GpuResource(ResourceType resourceType, CVkImage* image)
		: m_resourceType{ resourceType }
		, m_resource{ VkImageHandle::Create(image) }
	{}


	GpuResource(ResourceType resourceType, CVkBuffer* buffer)
		: m_resourceType{ resourceType }
		, m_resource{ VkBufferHandle::Create(buffer) }
	{}

protected:
	ResourceType m_resourceType{ ResourceType::Texture2D };

	std::variant<VkImageHandle, VkBufferHandle> m_resource;
};

} // namespace Kodiak::VK
