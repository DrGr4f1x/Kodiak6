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

#include "GpuImage12.h"


namespace Kodiak::DX12
{

GpuImage::GpuImage(
	ID3D12Resource* resource,
	uint64_t width,
	uint32_t height,
	uint32_t arraySizeOrDepth,
	uint32_t numMips,
	uint32_t numSamples,
	uint32_t planeCount,
	ResourceType resourceType,
	ResourceState usageState,
	Format format) noexcept
	: m_resource{ resource }
	, m_width{ width }
	, m_height{ height }
	, m_arraySizeOrDepth{ arraySizeOrDepth }
	, m_numMips{ numMips }
	, m_numSamples{ numSamples }
	, m_planeCount{ planeCount }
	, m_resourceType{ resourceType }
	, m_usageState{ usageState }
	, m_format{ format }
{}

} // namespace Kodiak::DX12