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
#include "Graphics\VK\CommandContextVK.h"
#include "Graphics\VK\VulkanCommon.h"

namespace Kodiak::VK
{

// Forward declarations
class Queue;
struct ImageCreationParams;
struct ImageViewCreationParams;


struct DeviceCreationParams
{
	VkInstance instance{ VK_NULL_HANDLE };
	CVkPhysicalDevice* physicalDevice{ nullptr };
	VkDevice device{ VK_NULL_HANDLE };

	struct {
		int32_t graphics{ -1 };
		int32_t compute{ -1 };
		int32_t transfer{ -1 };
		int32_t present{ -1 };
	} queueFamilyIndices{};

	uint32_t backBufferWidth{ 0 };
	uint32_t backBufferHeight{ 0 };
	uint32_t numSwapChainBuffers{ 3 };
	Format swapChainFormat{ Format::Unknown };
	VkSurfaceKHR surface{ VK_NULL_HANDLE };
	
	bool enableVSync{ false };
	uint32_t maxFramesInFlight{ 2 };

#if ENABLE_VULKAN_VALIDATION
	bool enableValidation{ true };
#else
	bool enableValidation{ false };
#endif

#if ENABLE_VULKAN_DEBUG_MARKERS
	bool enableDebugMarkers{ true };
#else
	bool enableDebugMarkers{ false };
#endif

	constexpr DeviceCreationParams& SetInstance(VkInstance value) noexcept { instance = value; return *this; }
	constexpr DeviceCreationParams& SetPhysicalDevice(CVkPhysicalDevice* value) noexcept { physicalDevice = value; return *this; }
	constexpr DeviceCreationParams& SetDevice(VkDevice value) noexcept { device = value; return *this; }
	constexpr DeviceCreationParams& SetGraphicsQueueIndex(int32_t value) noexcept { queueFamilyIndices.graphics = value; return *this; }
	constexpr DeviceCreationParams& SetComputeQueueIndex(int32_t value) noexcept { queueFamilyIndices.compute = value; return *this; }
	constexpr DeviceCreationParams& SetTransferQueueIndex(int32_t value) noexcept { queueFamilyIndices.transfer = value; return *this; }
	constexpr DeviceCreationParams& SetPresentQueueIndex(int32_t value) noexcept { queueFamilyIndices.present = value; return *this; }
	constexpr DeviceCreationParams& SetBackBufferWidth(uint32_t value) noexcept { backBufferWidth = value; return *this; }
	constexpr DeviceCreationParams& SetBackBufferHeight(uint32_t value) noexcept { backBufferHeight = value; return *this; }
	constexpr DeviceCreationParams& SetNumSwapChainBuffers(uint32_t value) noexcept { numSwapChainBuffers = value; return *this; }
	constexpr DeviceCreationParams& SetSwapChainFormat(Format value) noexcept { swapChainFormat = value; return *this; }
	constexpr DeviceCreationParams& SetSurface(VkSurfaceKHR value) noexcept { surface = value; return *this; }
	constexpr DeviceCreationParams& SetEnableVSync(bool value) noexcept { enableVSync = value; return *this; }
	constexpr DeviceCreationParams& SetMaxFramesInFlight(uint32_t value) noexcept { maxFramesInFlight = value; return *this; }
	constexpr DeviceCreationParams& SetEnableValidation(bool value) noexcept { enableValidation = value; return *this; }
	constexpr DeviceCreationParams& SetEnableDebugMarkers(bool value) noexcept { enableDebugMarkers = value; return *this; }
};


class GraphicsDevice : public IntrusiveCounter<IGraphicsDevice>
{
	friend class CommandContext;
	friend class DeviceManagerVK;
	friend class Queue;

public:
	GraphicsDevice(DeviceCreationParams& deviceCreationParams) noexcept
		: m_deviceCreationParams{ deviceCreationParams }
	{}

	~GraphicsDevice() final;

	bool Initialize() final;
	bool CreateSwapChain() final;

	void BeginFrame() final;
	void Present() final;

	ColorBufferHandle CreateColorBuffer(const ColorBufferCreationParams& creationParams) final;
	DepthBufferHandle CreateDepthBuffer(const DepthBufferCreationParams& creationParams) final;

	CommandContextHandle BeginCommandContext(const std::string& ID) final;
	GraphicsContextHandle BeginGraphicsContext(const std::string& ID) final;
	ComputeContextHandle BeginComputeContext(const std::string& ID, bool bAsync) final;

	ColorBufferHandle GetCurrentSwapChainBuffer() final;

private:
	void DestroySwapChain();

	ColorBufferHandle CreateColorBufferFromSwapChain(uint32_t imageIndex);

	void CreateQueue(QueueType queueType);
	VkFenceHandle CreateFence(bool bSignaled) const;
	VkSemaphoreHandle CreateSemaphore(VkSemaphoreType semaphoreType, uint64_t initialValue) const;
	VkCommandPoolHandle CreateCommandPool(CommandListType commandListType) const;
	VmaAllocatorHandle CreateVmaAllocator() const;
	VkImageHandle CreateImage(const ImageCreationParams& creationParams) const;
	VkImageViewHandle CreateImageView(const ImageViewCreationParams& creationParams) const;

	VkFormatProperties GetFormatProperties(Format format) const;

	Queue& GetQueue(QueueType queueType);
	Queue& GetQueue(CommandListType commandListType);
	void QueueWaitForSemaphore(QueueType queueType, VkSemaphore semaphore, uint64_t value);
	void QueueSignalSemaphore(QueueType queueType, VkSemaphore, uint64_t value);

	// CommandContext management
	CommandContext* AllocateContext(CommandListType commandListType);
	void FreeContext(CommandContext* usedContext);
	void WaitForFence(uint64_t fenceValue);

	void WaitForGpuIdle();

	VkDevice GetVkDevice() const noexcept { return *m_vkDevice; }

private:
	DeviceCreationParams m_deviceCreationParams{};
	
	// Device owns the following Vulkan objects
	VkPhysicalDeviceHandle m_vkPhysicalDevice;
	VkDeviceHandle m_vkDevice;

	// Swapchain
	VkSwapchainHandle m_vkSwapChain;
	// TODO - get rid of this, just use m_swapChainBuffers below
	std::vector<VkImageHandle> m_vkSwapChainImages;
	uint32_t m_swapChainIndex{ (uint32_t)-1 };
	bool m_swapChainMutableFormatSupported{ false };
	VkSurfaceFormatKHR m_swapChainFormat{};

	// Swapchain color buffers
	std::vector<ColorBufferHandle> m_swapChainBuffers;

	// Present synchronization
	std::vector<VkSemaphoreHandle> m_presentSemaphores;
	std::vector<VkFenceHandle> m_presentFences;
	std::vector<uint32_t> m_presentFenceState;
	uint32_t m_presentSemaphoreIndex{ 0 };

	// Submission queues
	std::array<std::unique_ptr<Queue>, (uint32_t)QueueType::Count> m_queues;

	// Command contexts
	std::array<std::vector<CommandContextHandle>, (uint32_t)CommandListType::Count> m_contextPool;
	std::array<std::queue<CommandContext*>, (uint32_t)CommandListType::Count> m_availableContexts;
	std::mutex m_contextAllocationMutex;

	// VmaAllocator
	VmaAllocatorHandle m_vmaAllocator;
};

} // namespace Kodiak::VK