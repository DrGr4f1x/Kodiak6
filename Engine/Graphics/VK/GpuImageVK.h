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

class GpuImage : public virtual IGpuImage
{
public:
	ResourceType GetType() const noexcept override
	{
		return m_resourceType;
	}

	ResourceState GetUsageState() const noexcept override
	{
		return m_usageState;
	}

	void SetUsageState(ResourceState usageState) noexcept override
	{
		m_usageState = usageState;
	}

protected:
	GpuImage() noexcept = default;
	GpuImage(ResourceType resourceType, CVkImage* image, ResourceState usageState) noexcept;

protected:
	ResourceType m_resourceType{ ResourceType::Unknown };

	VkImageHandle m_image;
	ResourceState m_usageState{ ResourceState::Undefined };
	ResourceState m_transitioningState{ ResourceState::Undefined };
};

} // namespace Kodiak::VK