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


#include "Graphics\VK\PixelBufferVK.h"


namespace Kodiak::VK
{

// Forward declarations
class GraphicsDevice;


struct ColorBufferCreationParamsExt
{
	VkImageHandle image;
	VkImageViewHandle imageViewRtv;
	VkImageViewHandle imageViewSrv;
	VkDescriptorImageInfo imageInfoSrv{};
	VkDescriptorImageInfo imageInfoUav{};
	ResourceState usageState{ ResourceState::Undefined };

	ColorBufferCreationParamsExt& SetImage(CVkImage* value) noexcept { image = value; return *this; }
	ColorBufferCreationParamsExt& SetImageViewRtv(CVkImageView* value) noexcept { imageViewRtv = value; return *this; }
	ColorBufferCreationParamsExt& SetImageViewSrv(CVkImageView* value) noexcept { imageViewSrv = value; return *this; }
	ColorBufferCreationParamsExt& SetImageInfoSrv(const VkDescriptorImageInfo& value) noexcept { imageInfoSrv = value; return *this; }
	ColorBufferCreationParamsExt& SetImageInfoUav(const VkDescriptorImageInfo& value) noexcept { imageInfoUav = value; return *this; }
	ColorBufferCreationParamsExt& SetUsageState(const ResourceState value) noexcept { usageState = value; return *this; }
};


class ColorBuffer : public IColorBuffer, public PixelBuffer
{
	IMPLEMENT_IOBJECT

	friend class GraphicsDevice;

public:
	~ColorBuffer() final = default;

	// IObject implementation
	NativeObjectPtr GetNativeObject(NativeObjectType nativeObjectType) const noexcept override;

	// IColorBuffer implementation
	void SetClearColor(Color clearColor) noexcept final { m_clearColor = clearColor; }
	Color GetClearColor() const noexcept final { return m_clearColor; }
	void SetMsaaMode(uint32_t numColorSamples, uint32_t numCoverageSamples) noexcept final
	{
		assert(numCoverageSamples >= numColorSamples);
		m_numFragments = numColorSamples;
		m_numSamples = numCoverageSamples;
	}

	// Get pre-created CPU-visible descriptor handles
	VkImageView GetImageViewRTV() const noexcept { return *m_imageViewRtv; }
	VkImageView GetImageViewSRV() const noexcept { return *m_imageViewSrv; }
	VkDescriptorImageInfo GetSRVImageInfo() const noexcept { return m_imageInfoSrv; }
	VkDescriptorImageInfo GetUAVImageInfo() const noexcept { return m_imageInfoUav; }

private:
	ColorBuffer(const ColorBufferCreationParams& creationParams, const ColorBufferCreationParamsExt& creationParamsExt);

private:
	const std::string m_name;
	Color m_clearColor{ DirectX::Colors::Black };
	uint32_t m_numFragments{ 1 };

	VkImageViewHandle m_imageViewRtv;
	VkImageViewHandle m_imageViewSrv;
	VkDescriptorImageInfo m_imageInfoSrv{};
	VkDescriptorImageInfo m_imageInfoUav{};
};

} // namespace Kodiak::VK