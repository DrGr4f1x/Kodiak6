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

#include "Graphics\CreationParams.h"

#include "DeviceVK.h"
#include "DeviceCapsVK.h"
#include "ExtensionManagerVK.h"
#include "FormatsVK.h"
#include "QueueVK.h"

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


VkBool32 DebugMessageCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageTypes,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData)
{
	using namespace Kodiak;
	using namespace Kodiak::VK;

	string prefix;

	if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
	{
		prefix += prefix.empty() ? "[Performance]" : " [Performance]";
	}
	if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
	{
		prefix += prefix.empty() ? "[Validation]" : " [Validation]";
	}
	if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
	{
		prefix += prefix.empty() ? "[General]" : " [General]";
	}

	string debugMessage = format("{} [{}] Code {} : {}", prefix, pCallbackData->pMessageIdName, pCallbackData->messageIdNumber, pCallbackData->pMessage);

	if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
	{
		LogError(LogVulkan) << debugMessage << endl;
	}
	else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
	{
		LogWarning(LogVulkan) << debugMessage << endl;
	}
	else
	{
		LogInfo(LogVulkan) << debugMessage << endl;
	}

	// The return value of this callback controls whether the Vulkan call that caused
	// the validation message will be aborted or not
	// We return VK_FALSE as we DON'T want Vulkan calls that cause a validation message 
	// (and return a VkResult) to abort
	// If you instead want to have calls abort, pass in VK_TRUE and the function will 
	// return VK_ERROR_VALIDATION_FAILED_EXT 
	return VK_FALSE;
}

} // anonymous namespace


namespace Kodiak::VK
{

DeviceManager::DeviceManager(const DeviceManagerCreationParams& creationParams)
	: m_creationParams{ creationParams }
{
	Initialize();
}


DeviceManager::~DeviceManager()
{
	LogInfo(LogVulkan) << "Destroying Vulkan DeviceManager." << endl;
}


void DeviceManager::BeginFrame()
{
	m_device->BeginFrame();
}


void DeviceManager::Present()
{
	m_device->Present();
}


void DeviceManager::Initialize()
{
	if (!CreateInstance())
	{
		LogFatal(LogVulkan) << "Failed to create Vulkan instance." << endl;
		return;
	}

	if (!CreateDevice())
	{
		LogFatal(LogVulkan) << "Failed to create Vulkan device." << endl;
		return;
	}

	if (!CreateSwapChain())
	{
		LogFatal(LogVulkan) << "Failed to create Vulkan swapchain." << endl;
	}
}


bool DeviceManager::CreateInstance()
{
	if (VK_FAILED(InitializeLoader()))
	{
		LogFatal(LogVulkan) << "Failed to initialize Vulkan loader.  Error code: " << endl;
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
	appInfo.pApplicationName = m_creationParams.appName.c_str();
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
		LogFatal(LogVulkan) << "Failed to create Vulkan instance.  Error code: " << res << endl;
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
		LogInfo(LogVulkan) << "Created Vulkan instance, but failed to enumerate version.  Error code: " << res << endl;
	}

	LoadInstanceFunctionsOnly(vkInstance);

	m_vkInstance = VkInstanceHandle::Create(new CVkInstance(vkInstance));

	InstallDebugMessenger();

	return true;
}


bool DeviceManager::CreateDevice()
{
	// TODO - gather application/user device extensions here

	// Adjust swap chain formats
	switch (m_creationParams.swapChainFormat)
	{
	case Format::SRGBA8_UNorm: m_creationParams.swapChainFormat = Format::SBGRA8_UNorm; break;
	case Format::RGBA8_UNorm: m_creationParams.swapChainFormat = Format::BGRA8_UNorm; break;
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
		LogError(LogVulkan) << "Failed to find graphics queue." << endl;
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
		LogError(LogVulkan) << "Failed to find compute queue." << endl;
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
		LogError(LogVulkan) << "Failed to find transfer queue." << endl;
		return false;
	}

	// HACK - replace with real device extension handling
	vector<const char*> extensions{ "VK_KHR_swapchain", "VK_KHR_swapchain_mutable_format" };

	VkDeviceCreateInfo createInfo{ VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO };
	createInfo.queueCreateInfoCount = (uint32_t)queueCreateInfos.size();
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.pEnabledFeatures = nullptr;
	// TODO - device extensions
	createInfo.enabledExtensionCount = (uint32_t)extensions.size();;
	createInfo.ppEnabledExtensionNames = extensions.data();
	createInfo.enabledLayerCount = 0;
	createInfo.ppEnabledLayerNames = nullptr;
	createInfo.pNext = m_caps->GetPhysicalDeviceFeatures2();

	VkDevice device{ VK_NULL_HANDLE };
	if (VK_FAILED(vkCreateDevice(*m_vkPhysicalDevice, &createInfo, nullptr, &device)))
	{
		LogError(LogVulkan) << "Failed to create Vulkan device.  Error code: " << res << endl;
		return false;
	}
	
	LoadDeviceFunctions(device);

	// Create the Kodiak GraphicsDevice
	auto creationParams = DeviceCreationParams{}
		.SetInstance(*m_vkInstance)
		.SetPhysicalDevice(m_vkPhysicalDevice)
		.SetDevice(device)
		.SetGraphicsQueueIndex(m_queueFamilyIndices.graphics)
		.SetComputeQueueIndex(m_queueFamilyIndices.compute)
		.SetTransferQueueIndex(m_queueFamilyIndices.transfer)
		.SetPresentQueueIndex(m_queueFamilyIndices.present)
		.SetBackBufferWidth(m_creationParams.backBufferWidth)
		.SetBackBufferHeight(m_creationParams.backBufferHeight)
		.SetNumSwapChainBuffers(m_creationParams.numSwapChainBuffers)
		.SetSwapChainFormat(m_creationParams.swapChainFormat)
		.SetSurface(*m_vkSurface)
		.SetEnableVSync(m_creationParams.enableVSync)
		.SetMaxFramesInFlight(m_creationParams.maxFramesInFlight)
		.SetEnableValidation(m_creationParams.enableValidation)
		.SetEnableDebugMarkers(m_creationParams.enableDebugMarkers);

	m_device = DeviceHandle::Create(new GraphicsDevice(creationParams));

	if (!m_device->Initialize())
	{
		LogError(LogVulkan) << "Failed to initialize Vulkan GraphicsDevice." << endl;
		return false;
	}

	return true;
}


bool DeviceManager::CreateSwapChain()
{
	return m_device->CreateSwapChain();
}


void DeviceManager::SetRequiredInstanceLayersAndExtensions()
{
	vector<string> requiredLayers{};
	if (m_creationParams.enableValidation)
	{
		requiredLayers.push_back("VK_LAYER_KHRONOS_validation");
	}
	m_extensionManager->SetRequiredInstanceLayers(requiredLayers);

	vector<string> requiredExtensions{
		"VK_EXT_debug_utils",
		"VK_KHR_win32_surface",
		"VK_KHR_surface"
	};
	m_extensionManager->SetRequiredInstanceExtensions(requiredExtensions);
}


bool DeviceManager::InstallDebugMessenger()
{
	if (!m_creationParams.enableValidation)
	{
		return true;
	}

	VkDebugUtilsMessengerCreateInfoEXT createInfo{ VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT };
	createInfo.messageSeverity =
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
	createInfo.pfnUserCallback = DebugMessageCallback;

	VkDebugUtilsMessengerEXT messenger{ VK_NULL_HANDLE };
	if (VK_FAILED(vkCreateDebugUtilsMessengerEXT(*m_vkInstance, &createInfo, nullptr, &messenger)))
	{
		LogWarning(LogVulkan) << "Failed to create Vulkan debug messenger.  Error Code: " << res << endl;
		return false;
	}

	m_vkDebugMessenger = VkDebugUtilsMessengerHandle::Create(new CVkDebugUtilsMessenger(m_vkInstance, messenger));

	return true;
}


vector<pair<AdapterInfo, VkPhysicalDevice>> DeviceManager::EnumeratePhysicalDevices()
{
	vector<pair<AdapterInfo, VkPhysicalDevice>> adapters;

	uint32_t gpuCount{ 0 };

	// Get number of available physical devices
	if (VK_FAILED(vkEnumeratePhysicalDevices(*m_vkInstance, &gpuCount, nullptr)))
	{
		LogError(LogVulkan) << "Failed to get physical device count.  Error code: " << res << endl;
		return adapters;
	}

	// Enumerate physical devices
	vector<VkPhysicalDevice> physicalDevices(gpuCount);
	if (VK_FAILED(vkEnumeratePhysicalDevices(*m_vkInstance, &gpuCount, physicalDevices.data())))
	{
		LogError(LogVulkan) << "Failed to enumerate physical devices.  Error code: " << res << endl;
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


bool DeviceManager::CreateWindowSurface()
{
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{ VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR };
	surfaceCreateInfo.hinstance = m_creationParams.hinstance;
	surfaceCreateInfo.hwnd = m_creationParams.hwnd;

	VkSurfaceKHR vkSurface{ VK_NULL_HANDLE };
	if (VK_FAILED(vkCreateWin32SurfaceKHR(*m_vkInstance, &surfaceCreateInfo, nullptr, &vkSurface)))
	{
		LogError(LogVulkan) << "Failed to create Win32 surface.  Error code: " << res << endl;
		return false;
	}
	m_vkSurface = VkSurfaceHandle::Create(new CVkSurface(m_vkInstance, vkSurface));

	return true;
}


bool DeviceManager::SelectPhysicalDevice()
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
		if (adapterPair.first.adapterType == Software && !m_creationParams.allowSoftwareDevice)
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

		if (adapterPair.first.adapterType == Software && softwareAdapterIdx == -1 && m_creationParams.allowSoftwareDevice)
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
	if (m_creationParams.preferDiscreteDevice)
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
		LogFatal(LogVulkan) << "Failed to select a Vulkan physical device." << endl;
		return false;
	}

	m_vkPhysicalDevice = VkPhysicalDeviceHandle::Create(new CVkPhysicalDevice(m_vkInstance, physicalDevices[chosenAdapterIdx].second));
	LogInfo(LogVulkan) << "Selected physical device " << chosenAdapterIdx << endl;

	m_caps->ReadCaps(*m_vkPhysicalDevice);
	// TODO
	//if (g_graphicsDeviceOptions.logDeviceFeatures)
	if (false)
	{
		m_caps->LogCaps();
	}

	m_extensionManager->InitializeDevice(*m_vkPhysicalDevice);

	// Get available queue family properties
	uint32_t queueCount{ 0 };
	vkGetPhysicalDeviceQueueFamilyProperties(*m_vkPhysicalDevice, &queueCount, nullptr);
	assert(queueCount >= 1);

	m_queueFamilyProperties.resize(queueCount);
	vkGetPhysicalDeviceQueueFamilyProperties(*m_vkPhysicalDevice, &queueCount, m_queueFamilyProperties.data());

	GetQueueFamilyIndices();

	return true;
}


void DeviceManager::GetQueueFamilyIndices()
{
	m_queueFamilyIndices.graphics = GetQueueFamilyIndex(VK_QUEUE_GRAPHICS_BIT);
	m_queueFamilyIndices.compute = GetQueueFamilyIndex(VK_QUEUE_COMPUTE_BIT);
	m_queueFamilyIndices.transfer = GetQueueFamilyIndex(VK_QUEUE_TRANSFER_BIT);
}


int32_t DeviceManager::GetQueueFamilyIndex(VkQueueFlags queueFlags)
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
				if (m_queueFamilyIndices.present == -1 && vkGetPhysicalDeviceWin32PresentationSupportKHR(*m_vkPhysicalDevice, index))
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
				if (m_queueFamilyIndices.present == -1 && vkGetPhysicalDeviceWin32PresentationSupportKHR(*m_vkPhysicalDevice, index))
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
			if (m_queueFamilyIndices.present == -1 && vkGetPhysicalDeviceWin32PresentationSupportKHR(*m_vkPhysicalDevice, index))
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

} // namespace Kodiak::VK