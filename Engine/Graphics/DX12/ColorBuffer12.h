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

struct ColorBufferCreationParamsExt
{
	ColorBufferCreationParamsExt() noexcept
	{
		rtvHandle.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
		srvHandle.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
		for (auto& handle : uavHandles)
		{
			handle.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
		}
	}

	ID3D12Resource* resource{ nullptr };
	uint32_t numFragments{ 1 };
	ResourceState usageState{ ResourceState::Undefined };
	uint8_t planeCount{ 1 };

	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle{};
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle{};
	std::array<D3D12_CPU_DESCRIPTOR_HANDLE, 12> uavHandles{};

	constexpr ColorBufferCreationParamsExt& SetResource(ID3D12Resource* value) noexcept { resource = value; return *this; }
	constexpr ColorBufferCreationParamsExt& SetNumFragments(uint32_t value) noexcept { numFragments = value; return *this; }
	constexpr ColorBufferCreationParamsExt& SetUsageState(ResourceState value) noexcept { usageState = value; return *this; }
	constexpr ColorBufferCreationParamsExt& SetPlaneCount(uint8_t value) noexcept { planeCount = value; return *this; }
	constexpr ColorBufferCreationParamsExt& SetSrvHandle(D3D12_CPU_DESCRIPTOR_HANDLE value) noexcept { srvHandle = value; return *this; }
	constexpr ColorBufferCreationParamsExt& SetRtvHandle(D3D12_CPU_DESCRIPTOR_HANDLE value) noexcept { rtvHandle = value; return *this; }
	ColorBufferCreationParamsExt& SetUavHandles(const std::array<D3D12_CPU_DESCRIPTOR_HANDLE, 12>& value) noexcept { uavHandles = value; return *this; }
};


class ColorBuffer : public IColorBuffer
{
	IMPLEMENT_IOBJECT

	friend class CommandContext;
	friend class GraphicsDevice;

public:
	~ColorBuffer() final = default;

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

	// IColorBuffer implementation
	void SetClearColor(Color clearColor) noexcept final { m_clearColor = clearColor; }
	Color GetClearColor() const noexcept final { return m_clearColor; }
	void SetMsaaMode(uint32_t numColorSamples, uint32_t numCoverageSamples) noexcept final
	{
		assert(numCoverageSamples >= numColorSamples);
		m_numFragments = numColorSamples;
		m_numSamples = numCoverageSamples;
	}

	uint32_t GetNumFragments() const noexcept { return m_numFragments; }

	// Get pre-created CPU-visible descriptor handles
	D3D12_CPU_DESCRIPTOR_HANDLE GetSRV() const noexcept { return m_srvHandle; }
	D3D12_CPU_DESCRIPTOR_HANDLE GetRTV() const noexcept { return m_rtvHandle; }
	D3D12_CPU_DESCRIPTOR_HANDLE GetUAV(uint32_t uavIndex) const noexcept { return m_uavHandles[uavIndex]; }

private:
	ColorBuffer(const ColorBufferCreationParams& creationParams, const ColorBufferCreationParamsExt& creationParamsExt);

private:
	ResourceType m_resourceType{ ResourceType::Texture2D };
	uint64_t m_width{ 0 };
	uint32_t m_height{ 0 };
	uint32_t m_arraySizeOrDepth{ 0 };
	uint32_t m_numMips{ 1 };
	uint32_t m_numSamples{ 1 };
	Format m_format{ Format::Unknown };
	uint32_t m_planeCount{ 1 };
	
	const std::string m_name;
	Color m_clearColor{ DirectX::Colors::Black };
	uint32_t m_numFragments{ 1 };

	IntrusivePtr<ID3D12Resource> m_resource;
	ResourceState m_usageState{ ResourceState::Undefined };
	ResourceState m_transitioningState{ ResourceState::Undefined };

	// Pre-constructed descriptors
	D3D12_CPU_DESCRIPTOR_HANDLE m_srvHandle;
	D3D12_CPU_DESCRIPTOR_HANDLE m_rtvHandle;
	std::array<D3D12_CPU_DESCRIPTOR_HANDLE, 12> m_uavHandles;
};

} // namespace Kodiak::DX12
