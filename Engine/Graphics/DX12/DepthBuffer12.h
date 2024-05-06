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

#include "Graphics\DX12\PixelBuffer12.h"


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


class DepthBuffer : public IDepthBuffer, public PixelBuffer
{
	IMPLEMENT_IOBJECT

	friend class GraphicsDevice;

public:
	~DepthBuffer() final = default;

	// IObject implementation
	NativeObjectPtr GetNativeObject(NativeObjectType nativeObjectType) const noexcept override;

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
	float m_clearDepth{ 1.0f };
	uint8_t m_clearStencil{ 0 };

	// Pre-constructed descriptors
	std::array<D3D12_CPU_DESCRIPTOR_HANDLE, 4> m_dsvHandles{};
	D3D12_CPU_DESCRIPTOR_HANDLE m_depthSrvHandle{};
	D3D12_CPU_DESCRIPTOR_HANDLE m_stencilSrvHandle{};
};

} // namespace Kodiak::DX12