//
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Author:  David Elder
//

#include "Stdafx.h"

#include "DeviceVK.h"

#include "FormatsVK.h"
#include "QueueVK.h"
#include "Generated\LoaderVk.h"

#include <unordered_set>

using namespace std;


namespace Kodiak::VK
{

GraphicsDevice::~GraphicsDevice()
{
	LogInfo(LogVulkan) << "Destroying Vulkan device." << endl;
	WaitForGpuIdle();
}


bool GraphicsDevice::Initialize()
{
	LogInfo(LogVulkan) << "Initializing Vulkan device." << endl;

	m_vkPhysicalDevice = m_deviceCreationParams.physicalDevice;
	m_vkDevice = VkDeviceHandle::Create(new CVkDevice(m_vkPhysicalDevice, m_deviceCreationParams.device));

	CreateQueue(QueueType::Graphics);
	CreateQueue(QueueType::Compute);
	CreateQueue(QueueType::Copy);

	return true;
}


bool GraphicsDevice::CreateSwapChain()
{
	m_swapChainFormat = { FormatToVulkan(m_deviceCreationParams.swapChainFormat), VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };

	VkExtent2D extent{ 
		m_deviceCreationParams.backBufferWidth,	
		m_deviceCreationParams.backBufferHeight };

	unordered_set<uint32_t> uniqueQueues{ 
		(uint32_t)m_deviceCreationParams.queueFamilyIndices.graphics, 
		(uint32_t)m_deviceCreationParams.queueFamilyIndices.present };
	vector<uint32_t> queues(uniqueQueues.begin(), uniqueQueues.end());

	VkImageUsageFlags usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
	usage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;

	m_swapChainMutableFormatSupported = true;

	const bool enableSwapChainSharing = queues.size() > 1;

	VkSwapchainCreateInfoKHR createInfo{ VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR };
	createInfo.surface = m_deviceCreationParams.surface;
	createInfo.minImageCount = m_deviceCreationParams.numSwapChainBuffers;
	createInfo.imageFormat = m_swapChainFormat.format;
	createInfo.imageColorSpace = m_swapChainFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = usage;
	createInfo.imageSharingMode = enableSwapChainSharing ? VK_SHARING_MODE_CONCURRENT : VK_SHARING_MODE_EXCLUSIVE;
	createInfo.flags = m_swapChainMutableFormatSupported ? VK_SWAPCHAIN_CREATE_MUTABLE_FORMAT_BIT_KHR : 0;
	createInfo.queueFamilyIndexCount = enableSwapChainSharing ? (uint32_t)queues.size() : 0;
	createInfo.pQueueFamilyIndices = enableSwapChainSharing ? queues.data() : nullptr;
	createInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = m_deviceCreationParams.enableVSync ? VK_PRESENT_MODE_FIFO_KHR : VK_PRESENT_MODE_IMMEDIATE_KHR;
	createInfo.clipped = true;
	createInfo.oldSwapchain = nullptr;

	vector<VkFormat> imageFormats{ m_swapChainFormat.format };
	switch (m_swapChainFormat.format)
	{
	case VK_FORMAT_R8G8B8A8_UNORM:
		imageFormats.push_back(VK_FORMAT_R8G8B8A8_SRGB);
		break;
	case VK_FORMAT_R8G8B8A8_SRGB:
		imageFormats.push_back(VK_FORMAT_R8G8B8A8_UNORM);
		break;
	case VK_FORMAT_B8G8R8A8_UNORM:
		imageFormats.push_back(VK_FORMAT_B8G8R8A8_SRGB);
		break;
	case VK_FORMAT_B8G8R8A8_SRGB:
		imageFormats.push_back(VK_FORMAT_B8G8R8A8_UNORM);
		break;
	}

	VkImageFormatListCreateInfo imageFormatListCreateInfo{ VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO };
	imageFormatListCreateInfo.viewFormatCount = (uint32_t)imageFormats.size();
	imageFormatListCreateInfo.pViewFormats = imageFormats.data();

	if (m_swapChainMutableFormatSupported)
	{
		createInfo.pNext = &imageFormatListCreateInfo;
	}

	VkSwapchainKHR swapchain{ VK_NULL_HANDLE };
	if (VK_FAILED(vkCreateSwapchainKHR(*m_vkDevice, &createInfo, nullptr, &swapchain)))
	{
		LogError(LogVulkan) << "Failed to create Vulkan swapchain.  Error code: " << res << endl;
		return false;
	}
	m_vkSwapChain = VkSwapchainHandle::Create(new CVkSwapchain(m_vkDevice, swapchain));

	// Get swapchain images
	uint32_t imageCount{ 0 };
	if (VK_FAILED(vkGetSwapchainImagesKHR(*m_vkDevice, *m_vkSwapChain, &imageCount, nullptr)))
	{
		LogError(LogVulkan) << "Failed to get swapchain image count.  Error code: " << res << endl;
		return false;
	}

	vector<VkImage> images{ imageCount };
	if (VK_FAILED(vkGetSwapchainImagesKHR(*m_vkDevice, *m_vkSwapChain, &imageCount, images.data())))
	{
		LogError(LogVulkan) << "Failed to get swapchain images.  Error code: " << res << endl;
		return false;
	}
	m_vkSwapChainImages.reserve(imageCount);
	for (auto image : images)
	{
		m_vkSwapChainImages.push_back(VkImageHandle::Create(new CVkImage(m_vkDevice, image)));
	}

	// Create the semaphores and fences for present
	m_presentSemaphores.reserve(m_deviceCreationParams.maxFramesInFlight + 1);
	m_presentFences.reserve(m_deviceCreationParams.maxFramesInFlight + 1);
	for (uint32_t i = 0; i < m_deviceCreationParams.maxFramesInFlight + 1; ++i)
	{
		VkSemaphoreHandle semaphore;
		if (VK_FAILED(CreateSemaphore(VK_SEMAPHORE_TYPE_BINARY, 0, &semaphore)))
		{
			LogError(LogVulkan) << "Failed to create present semaphore.  Error code: " << res << endl;
			return false;
		}
		m_presentSemaphores.push_back(semaphore);

		VkFenceHandle fence;
		if (VK_FAILED(CreateFence(false, &fence)))
		{
			LogError(LogVulkan) << "Failed to create present fence.  Error code: " << res << endl;
			return false;
		}
		m_presentFences.push_back(fence);
	}

	return true;
}


VkResult GraphicsDevice::CreateFence(bool bSignalled, CVkFence** ppFence) const
{
	VkFenceCreateInfo createInfo{ VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
	createInfo.flags = bSignalled ? VK_FENCE_CREATE_SIGNALED_BIT : 0;

	VkFence fence{ VK_NULL_HANDLE };
	auto res = vkCreateFence(*m_vkDevice, &createInfo, nullptr, &fence);

	*ppFence = nullptr;
	if (res == VK_SUCCESS)
	{
		*ppFence = new CVkFence(m_vkDevice, fence);
	}

	return res;
}

VkResult GraphicsDevice::CreateSemaphore(VkSemaphoreType semaphoreType, uint64_t initialValue, CVkSemaphore** ppSemaphore) const
{
	VkSemaphoreTypeCreateInfo typeCreateInfo{ VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO };
	typeCreateInfo.semaphoreType = semaphoreType;
	typeCreateInfo.initialValue = initialValue;

	VkSemaphoreCreateInfo createInfo{ VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
	createInfo.pNext = &typeCreateInfo;

	VkSemaphore semaphore{ VK_NULL_HANDLE };
	auto result = vkCreateSemaphore(*m_vkDevice, &createInfo, nullptr, &semaphore);

	*ppSemaphore = nullptr;
	if (VK_SUCCEEDED(result))
	{
		*ppSemaphore = new CVkSemaphore(m_vkDevice, semaphore);
	}

	return result;
}


VkResult GraphicsDevice::CreateCommandPool(CommandListType commandListType, CVkCommandPool** ppCommandPool) const
{
	uint32_t queueFamilyIndex{ 0 };
	switch (commandListType)
	{
	case CommandListType::Compute: queueFamilyIndex = m_deviceCreationParams.queueFamilyIndices.compute; break;
	case CommandListType::Copy: queueFamilyIndex = m_deviceCreationParams.queueFamilyIndices.transfer; break;
	default: queueFamilyIndex = m_deviceCreationParams.queueFamilyIndices.graphics; break;
	}

	VkCommandPoolCreateInfo createInfo{ VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };
	createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	createInfo.queueFamilyIndex = queueFamilyIndex;

	VkCommandPool vkCommandPool{ VK_NULL_HANDLE };
	auto result = vkCreateCommandPool(*m_vkDevice, &createInfo, nullptr, &vkCommandPool);

	*ppCommandPool = nullptr;
	if (VK_SUCCEEDED(result))
	{
		*ppCommandPool = new CVkCommandPool(m_vkDevice, vkCommandPool);
	}

	return result;
}


void GraphicsDevice::BeginFrame()
{
	// TODO
	const auto& semaphore = m_presentSemaphores[m_presentSemaphoreIndex];
	const auto& fence = m_presentFences[m_presentSemaphoreIndex];

	if (VK_FAILED(vkAcquireNextImageKHR(*m_vkDevice, *m_vkSwapChain, numeric_limits<uint64_t>::max(), *semaphore, *fence, &m_swapChainIndex)))
	{
		LogFatal(LogVulkan) << "Failed to acquire next swapchain image in BeginFrame.  Error code: " << res << endl;
		return;
	}

	QueueWaitForSemaphore(QueueType::Graphics, *semaphore, 0);
}


void GraphicsDevice::Present()
{
	const auto& semaphore = m_presentSemaphores[m_presentSemaphoreIndex];
	const auto& fence = m_presentFences[m_presentSemaphoreIndex];

	QueueSignalSemaphore(QueueType::Graphics, *semaphore, 0);

	// Need to submit a command list to kick Present...
	auto context = BeginCommandContext("Present");
	auto vkContext = dynamic_cast<CommandContext*>(context.Get());
	vkContext->HACK_TransitionImageToPresent(*m_vkSwapChainImages[m_swapChainIndex]);
	context->Finish();

	VkSwapchainKHR swapchain = *m_vkSwapChain;
	VkSemaphore waitSemaphore = *semaphore;

	VkPresentInfoKHR presentInfo = { VK_STRUCTURE_TYPE_PRESENT_INFO_KHR };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &swapchain;
	presentInfo.pImageIndices = &m_swapChainIndex;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &waitSemaphore;

	vkQueuePresentKHR(GetQueue(QueueType::Graphics).GetVkQueue(), &presentInfo);

	m_presentSemaphoreIndex = (m_presentSemaphoreIndex + 1) % m_presentSemaphores.size();

	const auto& nextFence = m_presentFences[m_presentSemaphoreIndex];
	VkFence vkFence = *nextFence;
	vkWaitForFences(*m_vkDevice, 1, &vkFence, TRUE, numeric_limits<uint64_t>::max());
	vkResetFences(*m_vkDevice, 1, &vkFence);
}


CommandContextHandle GraphicsDevice::BeginCommandContext(const std::string& ID)
{
	auto* newContext = AllocateContext(CommandListType::Direct);

	// TODO
#if 0
	NewContext->SetID(ID);
	if (ID.length() > 0)
	{
		EngineProfiling::BeginBlock(ID, NewContext);
	}
#endif

	newContext->m_device = this;
	newContext->m_bInvertedViewport = true;

	VkCommandBufferBeginInfo beginInfo{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
	vkBeginCommandBuffer(newContext->m_commandBuffer, &beginInfo);

#if ENABLE_VULKAN_DEBUG_MARKERS
	if (!ID.empty())
	{
		newContext->BeginEvent(ID);
		newContext->m_hasPendingDebugEvent = true;
	}
#endif

	return newContext;
}


GraphicsContextHandle GraphicsDevice::BeginGraphicsContext(const std::string& ID)
{
	return nullptr;
}


ComputeContextHandle GraphicsDevice::BeginComputeContext(const std::string& ID, bool bAsync)
{
	return nullptr;
}


void GraphicsDevice::DestroySwapChain()
{
	if (m_vkSwapChain)
	{
		m_vkSwapChain->Destroy();
	}

	m_vkSwapChainImages.clear();
}


void GraphicsDevice::CreateQueue(QueueType queueType)
{
	VkQueue vkQueue{ VK_NULL_HANDLE };
	vkGetDeviceQueue(*m_vkDevice, m_deviceCreationParams.queueFamilyIndices.graphics, 0, &vkQueue);
	m_queues[(uint32_t)queueType] = make_unique<Queue>(this, vkQueue, queueType);
}


Queue& GraphicsDevice::GetQueue(QueueType queueType)
{
	return *m_queues[(uint32_t)queueType];
}


Queue& GraphicsDevice::GetQueue(CommandListType commandListType)
{
	switch (commandListType)
	{
	case CommandListType::Compute: return GetQueue(QueueType::Compute); break;
	case CommandListType::Copy: return GetQueue(QueueType::Copy); break;
	default: return GetQueue(QueueType::Graphics); break;
	}
}


void GraphicsDevice::QueueWaitForSemaphore(QueueType queueType, VkSemaphore semaphore, uint64_t value)
{
	m_queues[(uint32_t)queueType]->AddWaitSemaphore(semaphore, value);
}


void GraphicsDevice::QueueSignalSemaphore(QueueType queueType, VkSemaphore semaphore, uint64_t value)
{
	m_queues[(uint32_t)queueType]->AddSignalSemaphore(semaphore, value);
}


CommandContext* GraphicsDevice::AllocateContext(CommandListType commandListType)
{
	lock_guard<mutex> guard{ m_contextAllocationMutex };

	auto& availableContexts = m_availableContexts[(uint32_t)commandListType];

	CommandContext* context{ nullptr };
	if (availableContexts.empty())
	{
		context = new CommandContext(commandListType);
		CommandContextHandle handle;
		handle.Attach(context);
		m_contextPool[(uint32_t)commandListType].emplace_back(handle);
		
		context->m_commandBuffer = GetQueue(commandListType).RequestCommandBuffer();
	}
	else
	{
		context = availableContexts.front();
		availableContexts.pop();
		context->Reset();
	}

	assert(context != nullptr);
	assert(context->m_type == commandListType);

	return context;
}


void GraphicsDevice::FreeContext(CommandContext* usedContext)
{
	lock_guard<mutex> guard{ m_contextAllocationMutex };

	m_availableContexts[(uint32_t)usedContext->m_type].push(usedContext);
}


void GraphicsDevice::WaitForFence(uint64_t fenceValue)
{
	auto& queue = GetQueue((CommandListType)(fenceValue >> 56));
	queue.WaitForFence(fenceValue);
}


void GraphicsDevice::UnblockPresent(QueueType queueType, VkSemaphore signalSemaphore, uint64_t waitValue, VkFence signalFence)
{
	m_queues[(uint32_t)queueType]->UnblockPresent(signalSemaphore, waitValue, signalFence);
}


void GraphicsDevice::WaitForGpuIdle()
{
	for (auto& queue : m_queues)
	{
		queue->WaitForIdle();
	}
}

} // namespace Kodiak::VK