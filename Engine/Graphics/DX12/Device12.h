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

#include "Graphics\Interfaces.h"
#include "Graphics\DX12\DirectXCommon.h"

namespace Kodiak::DX12
{

// Forward declarations
class DescriptorAllocator;
class Queue;
struct DeviceCaps;


struct DeviceRLDOHelper
{
	ID3D12Device* device{ nullptr };
	const bool doReport{ false };

	DeviceRLDOHelper(ID3D12Device* device, bool bDoReport) noexcept
		: device{ device }
		, doReport{ bDoReport }
	{}

	~DeviceRLDOHelper();
};

class GraphicsDevice : public IntrusiveCounter<IGraphicsDevice>
{
	friend class ColorBuffer;

public:
	struct CreationParams
	{
		IDXGIFactory4* dxgiFactory{ nullptr };
		ID3D12Device* dx12Device{ nullptr };

		uint32_t backBufferWidth{ 0 };
		uint32_t backBufferHeight{ 0 };
		uint32_t numSwapChainBuffers{ 3 };
		Format swapChainFormat{ Format::Unknown };
		uint32_t swapChainSampleCount{ 1 };
		uint32_t swapChainSampleQuality{ 0 };
		bool allowModeSwitch{ false };
		bool isTearingSupported{ false };

		bool enableVSync{ false };
		uint32_t maxFramesInFlight{ 2 };

		HWND hwnd{ nullptr };

#if ENABLE_D3D12_VALIDATION
		bool enableValidation{ true };
#else
		bool enableValidation{ false };
#endif

#if ENABLE_D3D12_DEBUG_MARKERS
		bool enableDebugMarkers{ true };
#else
		bool enableDebugMarkers{ false };
#endif

		constexpr CreationParams& SetDxgiFactory(IDXGIFactory4* value) noexcept { dxgiFactory = value; return *this; }
		constexpr CreationParams& SetDevice(ID3D12Device* value) noexcept { dx12Device = value; return *this; }
		constexpr CreationParams& SetBackBufferWidth(uint32_t value) noexcept { backBufferWidth = value; return *this; }
		constexpr CreationParams& SetBackBufferHeight(uint32_t value) noexcept { backBufferHeight = value; return *this; }
		constexpr CreationParams& SetNumSwapChainBuffers(uint32_t value) noexcept { numSwapChainBuffers = value; return *this; }
		constexpr CreationParams& SetSwapChainFormat(Format value) noexcept { swapChainFormat = value; return *this; }
		constexpr CreationParams& SetSwapChainSampleCount(uint32_t value) noexcept { swapChainSampleCount = value; return*this; }
		constexpr CreationParams& SetSwapChainSampleQuality(uint32_t value) noexcept { swapChainSampleQuality = value; return *this; }
		constexpr CreationParams& SetAllowModeSwitch(bool value) noexcept { allowModeSwitch = value; return *this; }
		constexpr CreationParams& SetIsTearingSupported(bool value) noexcept { isTearingSupported = value; return *this; }
		constexpr CreationParams& SetEnableVSync(bool value) noexcept { enableVSync = value; return *this; }
		constexpr CreationParams& SetMaxFramesInFlight(uint32_t value) noexcept { maxFramesInFlight = value; return *this; }
		constexpr CreationParams& SetHwnd(HWND value) noexcept { hwnd = value; return *this; }
		constexpr CreationParams& SetEnableValidation(bool value) noexcept { enableValidation = value; return *this; }
		constexpr CreationParams& SetEnableDebugMarkers(bool value) noexcept { enableDebugMarkers = value; return *this; }
	};

public:
	explicit GraphicsDevice(const CreationParams& creationParams) noexcept;
	~GraphicsDevice() final;

	bool Initialize() final;
	bool CreateSwapChain() final;

	void BeginFrame() final;
	void Present() final;

	ColorBufferHandle CreateColorBuffer(const ColorBufferCreationParams& creationParams) final;

	CommandContextHandle BeginCommandContext(const std::string& ID = "") final;
	GraphicsContextHandle BeginGraphicsContext(const std::string& ID = "") final;
	ComputeContextHandle BeginComputeContext(const std::string& ID = "", bool bAsync = false) final;

private:
	void ReadCaps();
	void InstallDebugCallback();
	
	ColorBufferHandle CreateColorBufferFromSwapChain(uint32_t imageIndex);

	void CreateQueue(QueueType queueType);
	Queue& GetQueue(QueueType queueType);
	Queue& GetQueue(CommandListType commandListType);

	D3D12_CPU_DESCRIPTOR_HANDLE AllocateDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t count = 1);
	void CreateDescriptorAllocators();

	ID3D12Device* GetD3D12Device() noexcept { return m_dxDevice; }

private:
	CreationParams m_creationParams{};
	
	// DirectX 12 objects
	IntrusivePtr<IDXGIFactory4> m_dxgiFactory;
	IntrusivePtr<ID3D12Device> m_dxDevice;
	DeviceRLDOHelper m_deviceRLDOHelper;
	IntrusivePtr<IDXGISwapChain3> m_dxgiSwapChain;
	IntrusivePtr<ID3D12InfoQueue1> m_dxInfoQueue;
	DWORD m_callbackCookie{ 0 };

	// Swapchain color buffers
	std::vector<ColorBufferHandle> m_swapChainBuffers;
	uint32_t m_currentBufferIndex{ 0 };

	// Present synchronization
	IntrusivePtr<ID3D12Fence> m_frameFence;
	std::vector<HANDLE> m_frameFenceEvents;
	uint32_t m_frameCount{ 0 };
	bool m_bIsWindowVisible{ true };

	// Queues
	std::array<std::unique_ptr<Queue>, (uint32_t)QueueType::Count> m_queues;

	// Descriptor allocators
	std::array<std::unique_ptr<DescriptorAllocator>, D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES> m_descriptorAllocators;

	// DirectX caps
	std::unique_ptr<DeviceCaps> m_caps;
};

} // namespace Kodiak::DX12