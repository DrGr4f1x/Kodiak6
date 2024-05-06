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

#include "PixelBufferVK.h"


namespace Kodiak::VK
{

PixelBuffer::PixelBuffer(
	ResourceType resourceType,
	CVkImage* image,
	ResourceState usageState,
	uint64_t width,
	uint32_t height,
	uint32_t arraySizeOrDepth,
	uint32_t numMips,
	uint32_t numSamples,
	Format format) noexcept
	: GpuImage{ resourceType, image, usageState }
	, m_width{ width }
	, m_height{ height }
	, m_arraySizeOrDepth{ arraySizeOrDepth }
	, m_numMips{ numMips }
	, m_numSamples{ numSamples }
	, m_format{ format }
{}

} // namespace Kodiak::VK