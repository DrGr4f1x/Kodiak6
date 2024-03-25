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
class Queue;
struct DeviceCaps;


struct DeviceCreationParams
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

	constexpr DeviceCreationParams& SetDxgiFactory(IDXGIFactory4* value) noexcept { dxgiFactory = value; return *this; }
	constexpr DeviceCreationParams& SetDevice(ID3D12Device* value) noexcept { dx12Device = value; return *this; }
	constexpr DeviceCreationParams& SetBackBufferWidth(uint32_t value) noexcept { backBufferWidth = value; return *this; }
	constexpr DeviceCreationParams& SetBackBufferHeight(uint32_t value) noexcept { backBufferHeight = value; return *this; }
	constexpr DeviceCreationParams& SetNumSwapChainBuffers(uint32_t value) noexcept { numSwapChainBuffers = value; return *this; }
	constexpr DeviceCreationParams& SetSwapChainFormat(Format value) noexcept { swapChainFormat = value; return *this; }
	constexpr DeviceCreationParams& SetSwapChainSampleCount(uint32_t value) noexcept { swapChainSampleCount = value; return*this; }
	constexpr DeviceCreationParams& SetSwapChainSampleQuality(uint32_t value) noexcept { swapChainSampleQuality = value; return *this; }
	constexpr DeviceCreationParams& SetAllowModeSwitch(bool value) noexcept { allowModeSwitch = value; return *this; }
	constexpr DeviceCreationParams& SetIsTearingSupported(bool value) noexcept { isTearingSupported = value; return *this; }
	constexpr DeviceCreationParams& SetEnableVSync(bool value) noexcept { enableVSync = value; return *this; }
	constexpr DeviceCreationParams& SetMaxFramesInFlight(uint32_t value) noexcept { maxFramesInFlight = value; return *this; }
	constexpr DeviceCreationParams& SetHwnd(HWND value) noexcept { hwnd = value; return *this; }
	constexpr DeviceCreationParams& SetEnableValidation(bool value) noexcept { enableValidation = value; return *this; }
	constexpr DeviceCreationParams& SetEnableDebugMarkers(bool value) noexcept { enableDebugMarkers = value; return *this; }
};


class GraphicsDevice : public IntrusiveCounter<IGraphicsDevice>
{
public:
	GraphicsDevice(const DeviceCreationParams& deviceCreationParams) noexcept;

	~GraphicsDevice() final;

	bool Initialize() final;
	bool CreateSwapChain() final;

	void BeginFrame() final;
	void Present() final;

	CommandContextHandle BeginCommandContext(const std::string& ID = "") final;
	GraphicsContextHandle BeginGraphicsContext(const std::string& ID = "") final;
	ComputeContextHandle BeginComputeContext(const std::string& ID = "", bool bAsync = false) final;

private:
	void ReadCaps();
	void InstallDebugCallback();
	
	void CreateQueue(QueueType queueType);
	Queue& GetQueue(QueueType queueType);
	Queue& GetQueue(CommandListType commandListType);

private:
	DeviceCreationParams m_deviceCreationParams{};
	
	// DirectX 12 objects
	IntrusivePtr<IDXGIFactory4> m_dxgiFactory;
	IntrusivePtr<ID3D12Device> m_dxDevice;
	IntrusivePtr<IDXGISwapChain3> m_dxgiSwapChain;
	IntrusivePtr<ID3D12InfoQueue1> m_dxInfoQueue;
	DWORD m_callbackCookie{ 0 };

	// Present synchronization
	IntrusivePtr<ID3D12Fence> m_frameFence;
	std::vector<HANDLE> m_frameFenceEvents;
	uint32_t m_frameCount{ 0 };
	bool m_bIsWindowVisible{ true };

	// Queues
	std::array<std::unique_ptr<Queue>, (uint32_t)QueueType::Count> m_queues;

	// DirectX caps
	std::unique_ptr<DeviceCaps> m_caps;
};

} // namespace Kodiak::DX12