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

#include "Generated\LoaderVk.h"

#include <unordered_set>

using namespace std;


namespace Kodiak::VK
{


GraphicsDevice::~GraphicsDevice()
{
	LogInfo(LogVulkan) << "Destroying Vulkan device." << endl;
}


bool GraphicsDevice::Initialize()
{
	LogInfo(LogVulkan) << "Initializing Vulkan device." << endl;

	m_vkPhysicalDevice = m_deviceCreationParams.physicalDevice;
	m_vkDevice = VkDeviceHandle::Create(new CVkDevice(m_vkPhysicalDevice, m_deviceCreationParams.device));

	return true;
}


bool GraphicsDevice::CreateSwapChain()
{

	VkExtent2D extent{ 
		m_deviceCreationParams.backBufferWidth,	
		m_deviceCreationParams.backBufferHeight };

	unordered_set<uint32_t> uniqueQueues{ 
		(uint32_t)m_deviceCreationParams.queueFamilyIndices.graphics, 
		(uint32_t)m_deviceCreationParams.queueFamilyIndices.present };
	vector<uint32_t> queues(uniqueQueues.begin(), uniqueQueues.end());

	const bool enableSwapChainSharing = queues.size() > 1;

	VkSwapchainCreateInfoKHR createInfo{ VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR };
	createInfo.surface = m_deviceCreationParams.surface;
	createInfo.minImageCount = m_deviceCreationParams.numSwapChainBuffers;
	createInfo.imageFormat = m_swapChainFormat.format;
	createInfo.imageColorSpace = m_swapChainFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
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

	m_presentSemaphores.reserve(m_deviceCreationParams.maxFramesInFlight);
	for (uint32_t i = 0; i < m_deviceCreationParams.maxFramesInFlight; ++i)
	{
		VkSemaphore semaphore{ VK_NULL_HANDLE };
		VkSemaphoreCreateInfo createInfo{ VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };

		if (VK_FAILED(vkCreateSemaphore(*m_vkDevice, &createInfo, nullptr, &semaphore)))
		{
			LogError(LogVulkan) << "Failed to create present semaphore.  Error code: " << res << endl;
			return false;
		}
		m_presentSemaphores.push_back(VkSemaphoreHandle::Create(new CVkSemaphore(m_vkDevice, semaphore)));
	}

	return true;
}


void GraphicsDevice::DestroySwapChain()
{
	if (m_vkSwapChain)
	{
		m_vkSwapChain->Destroy();
	}

	m_vkSwapChainImages.clear();
}

} // namespace Kodiak::VK