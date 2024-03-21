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
#include "Graphics\VK\VulkanCommon.h"

namespace Kodiak::VK
{

struct DeviceCreationParams
{
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

	constexpr DeviceCreationParams& SetPhysicalDevice(CVkPhysicalDevice* value) { physicalDevice = value; return *this; }
	constexpr DeviceCreationParams& SetDevice(VkDevice value) { device = value; return *this; }
	constexpr DeviceCreationParams& SetGraphicsQueueIndex(int32_t value) { queueFamilyIndices.graphics = value; return *this; }
	constexpr DeviceCreationParams& SetComputeQueueIndex(int32_t value) { queueFamilyIndices.compute = value; return *this; }
	constexpr DeviceCreationParams& SetTransferQueueIndex(int32_t value) { queueFamilyIndices.transfer = value; return *this; }
	constexpr DeviceCreationParams& SetPresentQueueIndex(int32_t value) { queueFamilyIndices.present = value; return *this; }
	constexpr DeviceCreationParams& SetBackBufferWidth(uint32_t value) { backBufferWidth = value; return *this; }
	constexpr DeviceCreationParams& SetBackBufferHeight(uint32_t value) { backBufferHeight = value; return *this; }
	constexpr DeviceCreationParams& SetNumSwapChainBuffers(uint32_t value) { numSwapChainBuffers = value; return *this; }
	constexpr DeviceCreationParams& SetSwapChainFormat(Format value) { swapChainFormat = value; return *this; }
	constexpr DeviceCreationParams& SetSurface(VkSurfaceKHR value) { surface = value; return *this; }
	constexpr DeviceCreationParams& SetEnableVSync(bool value) { enableVSync = value; return *this; }
	constexpr DeviceCreationParams& SetMaxFramesInFlight(uint32_t value) { maxFramesInFlight = value; return *this; }
};


class GraphicsDevice : public IntrusiveCounter<IGraphicsDevice>
{
	friend class DeviceManagerVK;

public:
	GraphicsDevice(DeviceCreationParams& deviceCreationParams) noexcept
		: m_deviceCreationParams{ deviceCreationParams }
	{}

	~GraphicsDevice() final;

	bool Initialize() final;
	bool CreateSwapChain() final;

private:
	void DestroySwapChain();

	void GetQueueFamilyIndices();
	int32_t GetQueueFamilyIndex(VkQueueFlags queueFlags);

private:
	DeviceCreationParams m_deviceCreationParams{};
	bool m_bIsInitialize{ false };

	// Device owns the following Vulkan objects
	VkPhysicalDeviceHandle m_vkPhysicalDevice;
	VkDeviceHandle m_vkDevice;

	// Swapchain
	VkSwapchainHandle m_vkSwapChain;
	std::vector<VkImageHandle> m_vkSwapChainImages;
	uint32_t m_swapChainIndex{ (uint32_t)-1 };
	bool m_swapChainMutableFormatSupported{ false };
	VkSurfaceFormatKHR m_swapChainFormat{};

	// Present synchronization
	std::vector<VkSemaphoreHandle> m_presentSemaphores;
	uint32_t m_presentSemaphoreIndex{ 0 };
};

} // namespace Kodiak::VK