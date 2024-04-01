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

// Forward declarations
class GraphicsDevice;


struct DepthBufferCreationParamsExt
{
	DepthBufferCreationParamsExt()
	{
		for (auto& handle : dsvHandles)
		{
			handle.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
		}
		depthSrvHandle.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
		stencilSrvHandle.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
	}

	ID3D12Resource* resource{ nullptr };
	ResourceState usageState{ ResourceState::Undefined };

	std::array<D3D12_CPU_DESCRIPTOR_HANDLE, 4> dsvHandles{};
	D3D12_CPU_DESCRIPTOR_HANDLE depthSrvHandle{};
	D3D12_CPU_DESCRIPTOR_HANDLE stencilSrvHandle{};

	constexpr DepthBufferCreationParamsExt& SetResource(ID3D12Resource* value) noexcept { resource = value; return *this; }
	constexpr DepthBufferCreationParamsExt& SetUsageState(ResourceState value) noexcept { usageState = value; return *this; }
	DepthBufferCreationParamsExt& SetDsvHandles(const std::array<D3D12_CPU_DESCRIPTOR_HANDLE, 4>& value) noexcept { dsvHandles = value; return *this; }
	constexpr DepthBufferCreationParamsExt& SetDepthSrvHandle(D3D12_CPU_DESCRIPTOR_HANDLE value) noexcept { depthSrvHandle = value; return *this; }
	constexpr DepthBufferCreationParamsExt& SetStencilSrvHandle(D3D12_CPU_DESCRIPTOR_HANDLE value) noexcept { stencilSrvHandle = value; return *this; }
};


class DepthBuffer : IntrusiveCounter<IDepthBuffer>
{
	friend class GraphicsDevice;

public:
	~DepthBuffer() final = default;

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

	// IDepthBuffer implementation
	float GetClearDepth() const noexcept final { return m_clearDepth; }
	uint8_t GetClearStencil() const noexcept final { return m_clearStencil; }

	// Get pre-created CPU-visible descriptor handles
	const D3D12_CPU_DESCRIPTOR_HANDLE& GetDSV() const noexcept { return m_dsvHandles[0]; }
	const D3D12_CPU_DESCRIPTOR_HANDLE& GetDSV_DepthReadOnly() const noexcept { return m_dsvHandles[1]; }
	const D3D12_CPU_DESCRIPTOR_HANDLE& GetDSV_StencilReadOnly() const noexcept { return m_dsvHandles[2]; }
	const D3D12_CPU_DESCRIPTOR_HANDLE& GetDSV_ReadOnly() const noexcept { return m_dsvHandles[3]; }
	const D3D12_CPU_DESCRIPTOR_HANDLE& GetDepthSRV() const noexcept { return m_depthSrvHandle; }
	const D3D12_CPU_DESCRIPTOR_HANDLE& GetStencilSRV() const noexcept { return m_stencilSrvHandle; }

private:
	DepthBuffer(const DepthBufferCreationParams& creationParams, const DepthBufferCreationParamsExt& creationParamsExt) noexcept;

private:
	const std::string m_name;
	ResourceType m_resourceType{ ResourceType::Texture2D };
	uint64_t m_width{ 0 };
	uint32_t m_height{ 0 };
	uint32_t m_arraySizeOrDepth{ 0 };
	uint32_t m_numMips{ 1 };
	uint32_t m_numSamples{ 1 };
	Format m_format{ Format::Unknown };
	float m_clearDepth{ 1.0f };
	uint8_t m_clearStencil{ 0 };

	IntrusivePtr<ID3D12Resource> m_resource;
	ResourceState m_usageState{ ResourceState::Undefined };
	ResourceState m_transitioningState{ ResourceState::Undefined };

	std::array<D3D12_CPU_DESCRIPTOR_HANDLE, 4> m_dsvHandles{};
	D3D12_CPU_DESCRIPTOR_HANDLE m_depthSrvHandle{};
	D3D12_CPU_DESCRIPTOR_HANDLE m_stencilSrvHandle{};
};

} // namespace Kodiak::DX12