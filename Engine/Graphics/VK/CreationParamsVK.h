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

struct ImageCreationParams
{
	std::string name;
	uint64_t width{ 0 };
	uint32_t height{ 0 };
	uint32_t arraySizeOrDepth{ 1 };
	Format format{ Format::Unknown };
	uint32_t numMips{ 1 };
	uint32_t numSamples{ 1 };
	ResourceType resourceType{ ResourceType::Unknown };
	GpuImageUsage imageUsage{ GpuImageUsage::Unknown };
	MemoryAccess memoryAccess{ MemoryAccess::Unknown };

	ImageCreationParams& SetName(const std::string& value) { name = value; return *this; }
	constexpr ImageCreationParams& SetWidth(uint64_t value) noexcept { width = value; return *this; }
	constexpr ImageCreationParams& SetHeight(uint32_t value) noexcept { height = value; return *this; }
	constexpr ImageCreationParams& SetArraySize(uint32_t value) noexcept { arraySizeOrDepth = value; return *this; }
	constexpr ImageCreationParams& SetDepth(uint32_t value) noexcept { arraySizeOrDepth = value; return *this; }
	constexpr ImageCreationParams& SetFormat(Format value) noexcept { format = value; return *this; }
	constexpr ImageCreationParams& SetNumMips(uint32_t value) noexcept { numMips = value; return *this; }
	constexpr ImageCreationParams& SetNumSamples(uint32_t value) noexcept { numSamples = value; return *this; }
	constexpr ImageCreationParams& SetResourceType(ResourceType value) noexcept { resourceType = value; return *this; }
	constexpr ImageCreationParams& SetImageUsage(GpuImageUsage value) noexcept { imageUsage = value; return *this; }
	constexpr ImageCreationParams& SetMemoryAccess(MemoryAccess value) noexcept { memoryAccess = value; return *this; }
};


struct ImageViewCreationParams
{
	CVkImage* image{ nullptr };
	std::string name;
	ResourceType resourceType{ ResourceType::Unknown };
	GpuImageUsage imageUsage{ GpuImageUsage::Unknown };
	Format format{ Format::Unknown };
	ImageAspect imageAspect{ 0 };
	uint32_t baseMipLevel{ 0 };
	uint32_t mipCount{ 1 };
	uint32_t baseArraySlice{ 0 };
	uint32_t arraySize{ 1 };

	constexpr ImageViewCreationParams& SetImage(CVkImage* value) noexcept { image = value; return *this; }
	ImageViewCreationParams& SetName(const std::string& value) { name = value; return *this; }
	constexpr ImageViewCreationParams& SetResourceType(ResourceType value) noexcept { resourceType = value; return *this; }
	constexpr ImageViewCreationParams& SetImageUsage(GpuImageUsage value) noexcept { imageUsage = value; return *this; }
	constexpr ImageViewCreationParams& SetFormat(Format value) noexcept { format = value; return *this; }
	constexpr ImageViewCreationParams& SetImageAspect(ImageAspect value) noexcept { imageAspect = value; return *this; }
	constexpr ImageViewCreationParams& SetBaseMipLevel(uint32_t value) noexcept { baseMipLevel = value; return *this; }
	constexpr ImageViewCreationParams& SetMipCount(uint32_t value) noexcept { mipCount = value; return *this; }
	constexpr ImageViewCreationParams& SetBaseArraySlice(uint32_t value) noexcept { baseArraySlice = value; return *this; }
	constexpr ImageViewCreationParams& SetArraySize(uint32_t value) noexcept { arraySize = value; return *this; }
};

} // namespace Kodiak::VK