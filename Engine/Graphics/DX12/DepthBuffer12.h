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
	uint8_t planeCount{ 1 };

	std::array<D3D12_CPU_DESCRIPTOR_HANDLE, 4> dsvHandles{};
	D3D12_CPU_DESCRIPTOR_HANDLE depthSrvHandle{};
	D3D12_CPU_DESCRIPTOR_HANDLE stencilSrvHandle{};

	constexpr DepthBufferCreationParamsExt& SetResource(ID3D12Resource* value) noexcept { resource = value; return *this; }
	constexpr DepthBufferCreationParamsExt& SetUsageState(ResourceState value) noexcept { usageState = value; return *this; }
	constexpr DepthBufferCreationParamsExt& SetPlaneCount(uint8_t value) noexcept { planeCount = value; return *this; }
	DepthBufferCreationParamsExt& SetDsvHandles(const std::array<D3D12_CPU_DESCRIPTOR_HANDLE, 4>& value) noexcept { dsvHandles = value; return *this; }
	constexpr DepthBufferCreationParamsExt& SetDepthSrvHandle(D3D12_CPU_DESCRIPTOR_HANDLE value) noexcept { depthSrvHandle = value; return *this; }
	constexpr DepthBufferCreationParamsExt& SetStencilSrvHandle(D3D12_CPU_DESCRIPTOR_HANDLE value) noexcept { stencilSrvHandle = value; return *this; }
};


class DepthBuffer : public IDepthBuffer
{
	IMPLEMENT_IOBJECT

	friend class GraphicsDevice;

public:
	~DepthBuffer() final = default;

	// IObject implementation
	NativeObjectPtr GetNativeObject(NativeObjectType nativeObjectType) const noexcept override;

	// IGpuImage implementation
	ResourceType GetType() const noexcept override { return m_resourceType; }
	uint64_t GetWidth() const noexcept override { return m_width; }
	uint32_t GetHeight() const noexcept override { return m_height; }
	uint32_t GetDepth() const noexcept override { return m_resourceType == ResourceType::Texture3D ? m_arraySizeOrDepth : 1; }
	uint32_t GetArraySize() const noexcept override { return m_resourceType == ResourceType::Texture3D ? 1 : m_arraySizeOrDepth; }
	uint32_t GetNumMips() const noexcept override { return m_numMips; }
	uint32_t GetNumSamples() const noexcept override { return m_numSamples; }
	Format GetFormat() const noexcept override { return m_format; }
	uint32_t GetPlaneCount() const noexcept override { return m_planeCount; }

	ResourceState GetUsageState() const noexcept override { return m_usageState; }
	void SetUsageState(ResourceState usageState) noexcept override { m_usageState = usageState; }

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
	ResourceType m_resourceType{ ResourceType::Texture2D };
	uint64_t m_width{ 0 };
	uint32_t m_height{ 0 };
	uint32_t m_arraySizeOrDepth{ 0 };
	uint32_t m_numMips{ 1 };
	uint32_t m_numSamples{ 1 };
	Format m_format{ Format::Unknown };

	const std::string m_name;
	float m_clearDepth{ 1.0f };
	uint8_t m_clearStencil{ 0 };
	uint32_t m_planeCount{ 1 };

	IntrusivePtr<ID3D12Resource> m_resource;
	ResourceState m_usageState{ ResourceState::Undefined };
	ResourceState m_transitioningState{ ResourceState::Undefined };

	// Pre-constructed descriptors
	std::array<D3D12_CPU_DESCRIPTOR_HANDLE, 4> m_dsvHandles{};
	D3D12_CPU_DESCRIPTOR_HANDLE m_depthSrvHandle{};
	D3D12_CPU_DESCRIPTOR_HANDLE m_stencilSrvHandle{};
};

} // namespace Kodiak::DX12