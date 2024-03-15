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
#include "Generated\LoaderVK.h"


using namespace std;


namespace Kodiak::VK
{

DeviceManagerVK::~DeviceManagerVK()
{
	delete m_extensionManager;
	m_extensionManager = nullptr;

	delete m_caps;
	m_caps = nullptr;
}

bool DeviceManagerVK::CreateInstanceInternal()
{
	if (VK_SUCCESS != InitializeLoader())
	{
		LogFatal(LogVulkan) << "Failed to initialize Vulkan loader" << endl;
		return false;
	}

	if (!m_extensionManager)
	{
		m_extensionManager = new ExtensionManager{};
	}

	if (!m_extensionManager->InitializeInstance())
	{
		return false;
	}

	if (!m_caps)
	{
		m_caps = new DeviceCaps{};
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
	SelectPhysicalDevice();

	return true;
}


bool DeviceManagerVK::CreateSwapChain()
{
	return true;
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


bool DeviceManagerVK::SelectPhysicalDevice()
{
	uint32_t gpuCount{ 0 };
	
	// Get number of available physical devices
	if (VK_FAILED(vkEnumeratePhysicalDevices(*m_instance, &gpuCount, nullptr)))
	{
		LogError(LogVulkan) << "Failed to get physical device count" << endl;
		return false;
	}

	// Enumerate physical devices
	vector<VkPhysicalDevice> physicalDevices(gpuCount);
	if (VK_FAILED(vkEnumeratePhysicalDevices(*m_instance, &gpuCount, physicalDevices.data())))
	{
		LogError(LogVulkan) << "Failed to enumerate physical devices" << endl;
		return false;
	}

	int32_t firstDiscreteGpu{ -1 };
	int32_t firstIntegratedGpu{ -1 };

	LogInfo(LogVulkan) << "Enumerating Vulkan physical devices" << endl;

	for (size_t deviceIdx = 0; deviceIdx < physicalDevices.size(); ++deviceIdx)
	{
		DeviceCaps caps{};
		caps.ReadCaps(physicalDevices[deviceIdx]);

		auto deviceType = caps.properties.deviceType;

		// Only consider discrete and integrated GPUs
		if (deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && deviceType != VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
		{
			continue;
		}

		if (deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && firstDiscreteGpu == -1)
		{
			firstDiscreteGpu = (uint32_t)deviceIdx;
		}
		else if (deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU && firstIntegratedGpu == -1)
		{
			firstIntegratedGpu = (uint32_t)deviceIdx;
		}

		const string deviceTypeStr = deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ? "Discrete" : "Integrated";

		string deviceName = caps.properties.deviceName;
		LogInfo(LogVulkan) << format("  {} physical device {} is Vulkan-capable: {} (VendorId: {:#x}, DeviceId: {:#x}, API version: {})",
			deviceTypeStr,
			deviceIdx,
			deviceName,
			caps.properties.vendorID, caps.properties.deviceID, caps.version)
			<< endl;
	}

	// Now select a device, preferring discrete if available
	if (firstDiscreteGpu != -1)
	{
		auto physicalDevice = physicalDevices[firstDiscreteGpu];
		m_physicalDevice = VkPhysicalDeviceHandle::Create(new CVkPhysicalDevice(m_instance, physicalDevice));

		LogInfo(LogVulkan) << "Selected discrete Vulkan physical device " << firstDiscreteGpu << endl;
	}
	else if (firstIntegratedGpu != -1)
	{
		auto physicalDevice = physicalDevices[firstIntegratedGpu];
		m_physicalDevice = VkPhysicalDeviceHandle::Create(new CVkPhysicalDevice(m_instance, physicalDevice));

		LogInfo(LogVulkan) << "Selected integrated Vulkan physical device " << firstIntegratedGpu << endl;
	}
	else
	{
		LogError(LogVulkan) << "Failed to select a Vulkan physical device" << endl;
		return false;
	}

	m_caps->ReadCaps(*m_physicalDevice);
	if (g_graphicsDeviceOptions.logDeviceFeatures)
	{
		m_caps->LogCaps();
	}

	m_extensionManager->InitializeDevice(*m_physicalDevice);

	return true;
}

} // namespace Kodiak::VK