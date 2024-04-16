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

#include "Graphics\DX12\GpuResource12.h"

namespace Kodiak::DX12
{

#pragma warning(disable:4250)
class PixelBuffer : public virtual IPixelBuffer, public GpuResource
{
public:
	// IPixelBuffer
	uint64_t GetWidth() const noexcept override { return m_width; }
	uint32_t GetHeight() const noexcept override { return m_height;	}
	uint32_t GetDepth() const noexcept override { return m_resourceType == ResourceType::Texture3D ? m_arraySizeOrDepth : 1; }
	uint32_t GetArraySize() const noexcept override { return m_resourceType == ResourceType::Texture3D ? 1 : m_arraySizeOrDepth; }
	uint32_t GetNumMips() const noexcept override { return m_numMips; }
	uint32_t GetNumSamples() const noexcept override { return m_numSamples; }
	Format GetFormat() const noexcept override { return m_format; }
	uint8_t GetPlaneCount() const noexcept { return m_planeCount; }

protected:
	PixelBuffer(ResourceType resourceType, ID3D12Resource* resource, ResourceState usageState, uint64_t width, uint32_t height, uint32_t arraySizeOrDepth, uint32_t numMips, uint32_t numSamples, Format format, uint8_t planeCount);

protected:
	uint64_t m_width{ 0 };
	uint32_t m_height{ 0 };
	uint32_t m_arraySizeOrDepth{ 0 };
	uint32_t m_numMips{ 1 };
	uint32_t m_numSamples{ 1 };
	Format m_format{ Format::Unknown };
	uint8_t m_planeCount{ 1 };
};
#pragma warning(default:4250)

} // namespace Kodiak::DX12