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

class __declspec(novtable) GpuImage : public virtual IGpuImage
{
public:
	ResourceType GetType() const noexcept override { return m_resourceType;	}
	ResourceState GetUsageState() const noexcept override {	return m_usageState; }
	void SetUsageState(ResourceState usageState) noexcept override { m_usageState = usageState;	}

	uint64_t GetWidth() const noexcept override { return m_width; }
	uint32_t GetHeight() const noexcept override { return m_height; }
	uint32_t GetDepth() const noexcept override { return m_resourceType == ResourceType::Texture3D ? m_arraySizeOrDepth : 1; }
	uint32_t GetArraySize() const noexcept override { return m_resourceType == ResourceType::Texture3D ? 1 : m_arraySizeOrDepth; }
	uint32_t GetNumMips() const noexcept override { return m_numMips; }
	uint32_t GetNumSamples() const noexcept override { return m_numSamples; }
	Format GetFormat() const noexcept override { return m_format; }
	uint32_t GetPlaneCount() const noexcept override { return m_planeCount; }

protected:
	GpuImage() noexcept = default;
	GpuImage(
		CVkImage* image,
		uint64_t width,
		uint32_t height,
		uint32_t arraySizeOrDepth,
		uint32_t numMips,
		uint32_t numSamples,
		ResourceType resourceType,
		ResourceState usageState,
		Format format) noexcept;

protected:
	VkImageHandle m_image;

	uint64_t m_width{ 0 };
	uint32_t m_height{ 0 };
	uint32_t m_arraySizeOrDepth{ 0 };
	uint32_t m_numMips{ 1 };
	uint32_t m_numSamples{ 1 };
	uint32_t m_planeCount{ 1 };

	ResourceType m_resourceType{ ResourceType::Unknown };
	ResourceState m_usageState{ ResourceState::Undefined };
	ResourceState m_transitioningState{ ResourceState::Undefined };

	Format m_format{ Format::Unknown };
};

} // namespace Kodiak::VK