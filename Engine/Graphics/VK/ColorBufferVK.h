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


struct ColorBufferCreationParamsExt
{
	CVkImage* image{ nullptr };

	constexpr ColorBufferCreationParamsExt& SetImage(CVkImage* value) noexcept { image = value; return *this; }
};


class ColorBuffer : IntrusiveCounter<IColorBuffer>
{
	friend class GraphicsDevice;

public:
	~ColorBuffer() final = default;

	// IGpuResource implementation
	ResourceType GetType() const noexcept final { return m_resourceType; }

	// IPixelBuffer implementation
	uint64_t GetWidth() const noexcept final { return m_width; };
	uint32_t GetHeight() const noexcept final { return m_height; }
	uint32_t GetDepth() const noexcept final { return m_resourceType == ResourceType::Texture3D ? m_arraySizeOrDepth : 1; }
	uint32_t GetArraySize() const noexcept final { return m_resourceType == ResourceType::Texture3D ? 1 : m_arraySizeOrDepth; }
	uint32_t GetNumMips() const noexcept final { return m_numMips; }
	uint32_t GetNumSamples() const noexcept final { return m_numSamples; }
	Format GetFormat() const noexcept final { return m_format; }

	// IColorBuffer implementation
	void SetClearColor(Color clearColor) noexcept final { m_clearColor = clearColor; }
	Color GetClearColor() const noexcept final { return m_clearColor; }
	void SetMsaaMode(uint32_t numColorSamples, uint32_t numCoverageSamples) noexcept final
	{
		assert(numCoverageSamples >= numColorSamples);
		m_numFragments = numColorSamples;
		m_numSamples = numCoverageSamples;
	}

private:
	explicit ColorBuffer(const ColorBufferCreationParams& creationParams, const ColorBufferCreationParamsExt& creationParamsExt);

	void InitializeFromSwapChain(GraphicsDevice* device);
	void Initialize(GraphicsDevice* device);

	void CreateDerivedViews(GraphicsDevice* device, uint32_t numMips);

private:
	const std::string m_name;
	ResourceType m_resourceType{ ResourceType::Texture2D };
	uint64_t m_width{ 0 };
	uint32_t m_height{ 0 };
	uint32_t m_arraySizeOrDepth{ 0 };
	uint32_t m_numMips{ 1 };
	uint32_t m_numSamples{ 1 };
	Format m_format{ Format::Unknown };
	Color m_clearColor{ DirectX::Colors::Black };
	uint32_t m_numFragments{ 1 };

	VkImageHandle m_image;
	VkImageViewHandle m_imageViewRtv;
	VkImageViewHandle m_imageViewSrv;
	VkDescriptorImageInfo m_imageInfoSrv{};
	VkDescriptorImageInfo m_imageInfoUav{};
};

} // namespace Kodiak::VK