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

#include "DeviceManagerVK.h"

#include "DeviceCapsVK.h"
#include "ExtensionManagerVK.h"
#include "FormatsVK.h"
#include "Generated\LoaderVK.h"


using namespace std;


namespace
{

size_t GetDedicatedVideoMemory(VkPhysicalDevice physicalDevice)
{
	size_t memory{ 0 };

	VkPhysicalDeviceMemoryProperties memoryProperties{};
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

	for (const auto& heap : memoryProperties.memoryHeaps)
	{
		if (heap.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
		{
			memory += heap.size;
		}
	}

	return memory;
}

} // anonymous namespace


namespace Kodiak::VK
{

DeviceManagerVK::~DeviceManagerVK() = default;


bool DeviceManagerVK::CreateInstanceInternal()
{
	if (VK_SUCCESS != InitializeLoader())
	{
		LogFatal(LogVulkan) << "Failed to initialize Vulkan loader" << endl;
		return false;
	}

	if (!m_extensionManager)
	{
		m_extensionManager = make_unique<ExtensionManager>();
	}

	if (!m_extensionManager->InitializeInstance())
	{
		return false;
	}

	if (!m_caps)
	{
		m_caps = make_unique<DeviceCaps>();
	}

	SetRequiredInstanceLayersAndExtensions();

	VkApplicationInfo appInfo{ VK_STRUCTURE_TYPE_APPLICATION_INFO };
	appInfo.pApplicationName = m_desc.appName.c_str();
	appInfo.pEngineName = "Kodiak";
	appInfo.apiVersion = VK_API_VERSION_1_3;

	vector<const char*> instanceExtensions;
	vector<const char*> instanceLayers;
	m_extensionManager->GetEnabledInstanceExtensions(instanceExtensions);
	m_extensionManager->GetEnabledInstanceLayers(instanceLayers);

	VkInstanceCreateInfo createInfo{ VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = (uint32_t)instanceExtensions.size();
	createInfo.ppEnabledExtensionNames = instanceExtensions.data();
	createInfo.enabledLayerCount = (uint32_t)instanceLayers.size();
	createInfo.ppEnabledLayerNames = instanceLayers.data();

	VkInstance vkInstance{ VK_NULL_HANDLE };
	if (VK_FAILED(vkCreateInstance(&createInfo, nullptr, &vkInstance)))
	{
		LogFatal(LogVulkan) << "Failed to create Vulkan instance" << endl;
		return false;
	}

	uint32_t instanceVersion{ 0 };
	if (VK_SUCCEEDED(vkEnumerateInstanceVersion(&instanceVersion)))
	{
		m_versionInfo = DecodeVulkanVersion(instanceVersion);

		LogInfo(LogVulkan) << format("Created Vulkan instance, variant {}, API version {}",
			m_versionInfo.variant, m_versionInfo) << endl;
	}
	else
	{
		LogInfo(LogVulkan) << "Created Vulkan instance, but failed to enumerate version" << endl;
	}

	LoadInstanceFunctionsOnly(vkInstance);

	m_instance = VkInstanceHandle::Create(new CVkInstance(vkInstance));

	return true;
}


bool DeviceManagerVK::CreateDevice()
{
	// TODO - install debug callback here

	// TODO - gather application/user device extensions here

	// Adjust swap chain formats
	switch (m_desc.swapChainFormat)
	{
	case Format::SRGBA8_UNorm: m_desc.swapChainFormat = Format::SBGRA8_UNorm; break;
	case Format::RGBA8_UNorm: m_desc.swapChainFormat = Format::BGRA8_UNorm; break;
	}

	if (!CreateWindowSurface())
	{
		return false;
	}

	if (!SelectPhysicalDevice())
	{
		return false;
	}

	// Desired queues need to be requested upon logical device creation
	// Due to differing queue family configurations of Vulkan implementations this can be a bit tricky, especially if the application
	// requests different queue types

	vector<VkDeviceQueueCreateInfo> queueCreateInfos{};

	// Get queue family indices for the requested queue family types
	// Note that the indices may overlap depending on the implementation

	const float defaultQueuePriority = 0.0f;

	// Graphics queue
	if (m_queueFamilyIndices.graphics != -1)
	{
		VkDeviceQueueCreateInfo queueInfo{ VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO };
		queueInfo.queueFamilyIndex = m_queueFamilyIndices.graphics;
		queueInfo.queueCount = 1;
		queueInfo.pQueuePriorities = &defaultQueuePriority;
		queueCreateInfos.push_back(queueInfo);
	}
	else
	{
		LogError(LogVulkan) << "Failed to find graphics queue" << endl;
		return false;
	}

	// Dedicated compute queue
	if (m_queueFamilyIndices.compute != -1)
	{
		if (m_queueFamilyIndices.compute != m_queueFamilyIndices.graphics)
		{
			// If compute family index differs, we need an additional queue create info for the compute queue
			VkDeviceQueueCreateInfo queueInfo{ VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO };
			queueInfo.queueFamilyIndex = m_queueFamilyIndices.compute;
			queueInfo.queueCount = 1;
			queueInfo.pQueuePriorities = &defaultQueuePriority;
			queueCreateInfos.push_back(queueInfo);
		}
	}
	else
	{
		LogError(LogVulkan) << "Failed to find compute queue" << endl;
		return false;
	}

	// Dedicated transfer queue
	if (m_queueFamilyIndices.transfer != -1)
	{
		if ((m_queueFamilyIndices.transfer != m_queueFamilyIndices.graphics) && (m_queueFamilyIndices.transfer != m_queueFamilyIndices.compute))
		{
			// If compute family index differs, we need an additional queue create info for the transfer queue
			VkDeviceQueueCreateInfo queueInfo{ VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO };
			queueInfo.queueFamilyIndex = m_queueFamilyIndices.transfer;
			queueInfo.queueCount = 1;
			queueInfo.pQueuePriorities = &defaultQueuePriority;
			queueCreateInfos.push_back(queueInfo);
		}
	}
	else
	{
		LogError(LogVulkan) << "Failed to find transfer queue" << endl;
		return false;
	}

	return true;
}


bool DeviceManagerVK::CreateSwapChain()
{
	DestroySwapChain();

	m_swapChainFormat = { FormatToVulkan(m_desc.swapChainFormat), VK_COLOR_SPACE_SRGB_NONLINEAR_KHR	};

	VkExtent2D extent{ m_desc.backBufferHeight,	m_desc.backBufferHeight	};

	unordered_set<uint32_t> uniqueQueues{ (uint32_t)m_queueFamilyIndices.graphics, (uint32_t)m_queueFamilyIndices.present };
	vector<uint32_t> queues(uniqueQueues.begin(), uniqueQueues.end());

	const bool enableSwapChainSharing = queues.size() > 1;

	VkSwapchainCreateInfoKHR createInfo{ VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR };
	createInfo.surface = m_surface->Get();
	createInfo.minImageCount = m_desc.numSwapChainBuffers;
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
	createInfo.presentMode = m_desc.enableVSync ? VK_PRESENT_MODE_FIFO_KHR : VK_PRESENT_MODE_IMMEDIATE_KHR;
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

	return true;
}


void DeviceManagerVK::BeginFrame()
{

}


void DeviceManagerVK::Present()
{

}


void DeviceManagerVK::SetRequiredInstanceLayersAndExtensions()
{
	vector<string> requiredLayers{};
	if (m_desc.enableDebugRuntime)
	{
		requiredLayers.push_back("VK_LAYER_KHRONOS_validation");
	}
	m_extensionManager->SetRequiredInstanceLayers(requiredLayers);

	vector<string> requiredExtensions{
		"VK_EXT_debug_report",
		"VK_KHR_win32_surface",
		"VK_KHR_surface"
	};
	m_extensionManager->SetRequiredInstanceExtensions(requiredExtensions);
}


vector<pair<AdapterInfo, VkPhysicalDevice>> DeviceManagerVK::EnumeratePhysicalDevices()
{
	vector<pair<AdapterInfo, VkPhysicalDevice>> adapters;

	uint32_t gpuCount{ 0 };

	// Get number of available physical devices
	if (VK_FAILED(vkEnumeratePhysicalDevices(*m_instance, &gpuCount, nullptr)))
	{
		LogError(LogVulkan) << "Failed to get physical device count" << endl;
		return adapters;
	}

	// Enumerate physical devices
	vector<VkPhysicalDevice> physicalDevices(gpuCount);
	if (VK_FAILED(vkEnumeratePhysicalDevices(*m_instance, &gpuCount, physicalDevices.data())))
	{
		LogError(LogVulkan) << "Failed to enumerate physical devices" << endl;
		return adapters;
	}

	LogInfo(LogVulkan) << "Enumerating Vulkan physical devices" << endl;

	for (size_t deviceIdx = 0; deviceIdx < physicalDevices.size(); ++deviceIdx)
	{
		DeviceCaps caps{};
		caps.ReadCaps(physicalDevices[deviceIdx]);

		AdapterInfo adapterInfo{};
		adapterInfo.name = caps.properties.deviceName;
		adapterInfo.deviceId = caps.properties.deviceID;
		adapterInfo.vendorId = caps.properties.vendorID;
		adapterInfo.dedicatedVideoMemory = GetDedicatedVideoMemory(physicalDevices[deviceIdx]);
		adapterInfo.vendor = VendorIdToHardwareVendor(adapterInfo.vendorId);
		adapterInfo.adapterType = VkPhysicalDeviceTypeToEngine(caps.properties.deviceType);
		adapterInfo.apiVersion = caps.properties.apiVersion;

		LogInfo(LogVulkan) << format("  {} physical device {} is Vulkan-capable: {} (VendorId: {:#x}, DeviceId: {:#x}, API version: {})",
			AdapterTypeToString(adapterInfo.adapterType),
			deviceIdx,
			adapterInfo.name,
			adapterInfo.vendorId, adapterInfo.deviceId, VulkanVersionToString(adapterInfo.apiVersion))
			<< endl;

		LogInfo(LogVulkan) << format("    Physical device memory: {} MB dedicated video memory, {} MB dedicated system memory, {} MB shared memory",
			(uint32_t)(adapterInfo.dedicatedVideoMemory >> 20),
			(uint32_t)(adapterInfo.dedicatedSystemMemory >> 20),
			(uint32_t)(adapterInfo.sharedSystemMemory >> 20))
			<< endl;

		adapters.push_back(make_pair(adapterInfo, physicalDevices[deviceIdx]));
	}

	return adapters;
}


bool DeviceManagerVK::CreateWindowSurface()
{
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{ VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR };
	surfaceCreateInfo.hinstance = m_desc.hinstance;
	surfaceCreateInfo.hwnd = m_desc.hwnd;

	VkSurfaceKHR vkSurface{ VK_NULL_HANDLE };
	if (VK_FAILED(vkCreateWin32SurfaceKHR(m_instance->Get(), &surfaceCreateInfo, nullptr, &vkSurface)))
	{
		LogError(LogVulkan) << "Failed to create Win32 surface" << endl;
		return false;
	}
	m_surface = VkSurfaceHandle::Create(new CVkSurface(m_instance, vkSurface));

	return true;
}

bool DeviceManagerVK::SelectPhysicalDevice()
{
	using enum AdapterType;

	vector<pair<AdapterInfo, VkPhysicalDevice>> physicalDevices = EnumeratePhysicalDevices();

	if (physicalDevices.empty())
	{
		return false;
	}

	int32_t firstDiscreteAdapterIdx{ -1 };
	int32_t bestMemoryAdapterIdx{ -1 };
	int32_t firstAdapterIdx{ -1 };
	int32_t softwareAdapterIdx{ -1 };
	int32_t chosenAdapterIdx{ -1 };
	size_t maxMemory{ 0 };

	int32_t adapterIdx{ 0 };
	for (const auto& adapterPair : physicalDevices)
	{
		// Skip adapters that don't support the required Vulkan API version
		if (adapterPair.first.apiVersion < g_requiredVulkanApiVersion)
		{
			continue;
		}

		// Skip adapters of type 'Other'
		if (adapterPair.first.adapterType == Other)
		{
			continue;
		}

		// Skip software adapters if we disallow them
		if (adapterPair.first.adapterType == Software && !m_desc.allowSoftwareDevice)
		{
			continue;
		}

		if (firstAdapterIdx == -1)
		{
			firstAdapterIdx = adapterIdx;
		}

		if (adapterPair.first.adapterType == Discrete && firstDiscreteAdapterIdx == -1)
		{
			firstDiscreteAdapterIdx = adapterIdx;
		}

		if (adapterPair.first.adapterType == Software && softwareAdapterIdx == -1 && m_desc.allowSoftwareDevice)
		{
			softwareAdapterIdx = adapterIdx;
		}

		if (adapterPair.first.dedicatedVideoMemory > maxMemory)
		{
			maxMemory = adapterPair.first.dedicatedVideoMemory;
			bestMemoryAdapterIdx = adapterIdx;
		}

		++adapterIdx;
	}


	// Now choose our best adapter
	if (m_desc.preferDiscreteDevice)
	{
		if (bestMemoryAdapterIdx != -1)
		{
			chosenAdapterIdx = bestMemoryAdapterIdx;
		}
		else if (firstDiscreteAdapterIdx != -1)
		{
			chosenAdapterIdx = firstDiscreteAdapterIdx;
		}
		else
		{
			chosenAdapterIdx = firstAdapterIdx;
		}
	}
	else
	{
		chosenAdapterIdx = firstAdapterIdx;
	}

	if (chosenAdapterIdx == -1)
	{
		LogFatal(LogVulkan) << "Failed to select a Vulkan physical device" << endl;
		return false;
	}

	m_physicalDevice = VkPhysicalDeviceHandle::Create(new CVkPhysicalDevice(m_instance, physicalDevices[chosenAdapterIdx].second));
	LogInfo(LogVulkan) << "Selected physical device " << chosenAdapterIdx << endl;

	m_caps->ReadCaps(*m_physicalDevice);
	if (g_graphicsDeviceOptions.logDeviceFeatures)
	{
		m_caps->LogCaps();
	}

	m_extensionManager->InitializeDevice(*m_physicalDevice);

	// Get available queue family properties
	uint32_t queueCount{ 0 };
	vkGetPhysicalDeviceQueueFamilyProperties(*m_physicalDevice, &queueCount, nullptr);
	assert(queueCount >= 1);

	m_queueFamilyProperties.resize(queueCount);
	vkGetPhysicalDeviceQueueFamilyProperties(*m_physicalDevice, &queueCount, m_queueFamilyProperties.data());

	GetQueueFamilyIndices();

	return true;
}


void DeviceManagerVK::GetQueueFamilyIndices()
{
	m_queueFamilyIndices.graphics = GetQueueFamilyIndex(VK_QUEUE_GRAPHICS_BIT);
	m_queueFamilyIndices.compute = GetQueueFamilyIndex(VK_QUEUE_COMPUTE_BIT);
	m_queueFamilyIndices.transfer = GetQueueFamilyIndex(VK_QUEUE_TRANSFER_BIT);
}


int32_t DeviceManagerVK::GetQueueFamilyIndex(VkQueueFlags queueFlags)
{
	int32_t index{ 0 };

	// Dedicated queue for compute
	// Try to find a queue family index that supports compute but not graphics
	if (queueFlags & VK_QUEUE_COMPUTE_BIT)
	{
		for (const auto& properties : m_queueFamilyProperties)
		{
			if ((properties.queueFlags & queueFlags) && ((properties.queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0))
			{
				if (m_queueFamilyIndices.present == -1 && vkGetPhysicalDeviceWin32PresentationSupportKHR(m_physicalDevice->Get(), index))
				{
					m_queueFamilyIndices.present = index;
				}

				return index;
			}
			++index;
		}
	}

	// Dedicated queue for transfer
	// Try to find a queue family index that supports transfer but not graphics and compute
	if (queueFlags & VK_QUEUE_TRANSFER_BIT)
	{
		index = 0;
		for (const auto& properties : m_queueFamilyProperties)
		{
			if ((properties.queueFlags & queueFlags) && ((properties.queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0) && ((properties.queueFlags & VK_QUEUE_COMPUTE_BIT) == 0))
			{
				if (m_queueFamilyIndices.present == -1 && vkGetPhysicalDeviceWin32PresentationSupportKHR(m_physicalDevice->Get(), index))
				{
					m_queueFamilyIndices.present = index;
				}

				return index;
			}
			++index;
		}
	}

	// For other queue types or if no separate compute queue is present, return the first one to support the requested flags
	index = 0;
	for (const auto& properties : m_queueFamilyProperties)
	{
		if (properties.queueFlags & queueFlags)
		{
			if (m_queueFamilyIndices.present == -1 && vkGetPhysicalDeviceWin32PresentationSupportKHR(m_physicalDevice->Get(), index))
			{
				m_queueFamilyIndices.present = index;
			}

			return index;
		}
		++index;
	}

	LogWarning(LogVulkan) << "Failed to find a matching queue family index for queue bit(s) " << VkQueueFlagsToString(queueFlags) << endl;
	return -1;
}


void DeviceManagerVK::DestroySwapChain()
{
	if (m_swapChain)
	{
		m_swapChain->Destroy();
	}

	m_swapChainImages.clear();
}

} // namespace Kodiak::VK