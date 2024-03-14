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

#include "Graphics\DX12\DirectXCommon.h"


namespace Kodiak::DX12
{

class ColorBuffer : IntrusiveCounter<IColorBuffer>
{
public:
	~ColorBuffer() final;

	// IGpuResource implementation
	ResourceType GetType() const noexcept final { return m_resourceType; }

	// IPixelBuffer implementation
	uint32_t GetWidth() const noexcept final { return m_width; };
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
	void CreateDerivedViews(Format format, uint32_t arraySize, uint32_t numMips);

private:
	ResourceType m_resourceType{ ResourceType::Texture2D };
	uint32_t m_width{ 0 };
	uint32_t m_height{ 0 };
	uint32_t m_arraySizeOrDepth{ 0 };
	uint32_t m_numMips{ 1 };
	uint32_t m_numSamples{ 1 };
	Format m_format{ Format::Unknown };
	Color m_clearColor{ DirectX::Colors::Black };
	uint32_t m_numFragments{ 1 };

	Microsoft::WRL::ComPtr<ID3D12Resource> m_resource;
	ResourceState m_usageState{ ResourceState::Undefined };
	ResourceState m_transitioningState{ ResourceState::Undefined };

	// Pre-constructed descriptors
	D3D12_CPU_DESCRIPTOR_HANDLE m_srvHandle;
	D3D12_CPU_DESCRIPTOR_HANDLE m_rtvHandle;
	D3D12_CPU_DESCRIPTOR_HANDLE m_uavHandle[12];
};

} // namespace Kodiak::DX12
