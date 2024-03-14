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


using namespace Kodiak;
using namespace Kodiak::VK;
using namespace std;


namespace
{

constexpr uint32_t g_requiredVulkanVersion{ VK_API_VERSION_1_3 };

} // anonymous namespace


GraphicsDevice::GraphicsDevice()
{
	LogInfo(LogVulkan) << "Creating Vulkan device" << endl;
}


GraphicsDevice::~GraphicsDevice()
{
	LogInfo(LogVulkan) << "Destroying Vulkan device" << endl;
}


void GraphicsDevice::Initialize(const GraphicsDeviceDesc& desc)
{
	m_deviceDesc = desc;

	if (VK_SUCCESS != InitializeLoader())
	{
		LogFatal(LogVulkan) << "Failed to initialize Vulkan loader";
	}

	CreateInstance();

	SelectPhysicalDevice();
}


void GraphicsDevice::CreateInstance()
{
	VkApplicationInfo appInfo{ VK_STRUCTURE_TYPE_APPLICATION_INFO };
	appInfo.pApplicationName = m_deviceDesc.appName.c_str();
	appInfo.pEngineName = "Kodiak";
	appInfo.apiVersion = g_requiredVulkanVersion;

	const vector<const char*> instanceExtensions =
	{
#if ENABLE_VULKAN_VALIDATION
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
		VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME,
#endif
		VK_KHR_SURFACE_EXTENSION_NAME,
		VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME
	};

	const vector<const char*> instanceLayers =
	{
#if ENABLE_VULKAN_VALIDATION
		"VK_LAYER_KHRONOS_validation"
#endif
	};

	VkInstanceCreateInfo createInfo{ VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = (uint32_t)instanceExtensions.size();
	createInfo.ppEnabledExtensionNames = instanceExtensions.data();
	createInfo.enabledLayerCount = (uint32_t)instanceLayers.size();
	createInfo.ppEnabledLayerNames = instanceLayers.data();

	VkInstance vkInstance{ VK_NULL_HANDLE };
	auto res = vkCreateInstance(&createInfo, nullptr, &vkInstance);
	if (VK_SUCCESS != res)
	{
		LogFatal(LogVulkan) << "Failed to create Vulkan instance";
	}

	uint32_t instanceVersion{ 0 };
	res = vkEnumerateInstanceVersion(&instanceVersion);
	if (res == VK_SUCCESS)
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
}


void GraphicsDevice::SelectPhysicalDevice()
{
	uint32_t gpuCount{ 0 };
	VkResult res{ VK_SUCCESS };

	// Get number of available physical devices
	res = vkEnumeratePhysicalDevices(*m_instance, &gpuCount, nullptr);
	if (res != VK_SUCCESS)
	{
		LogFatal(LogVulkan) << "Failed to get physical device count" << endl;
	}

	// Enumerate physical devices
	vector<VkPhysicalDevice> physicalDevices(gpuCount);
	res = vkEnumeratePhysicalDevices(*m_instance, &gpuCount, physicalDevices.data());
	if (res != VK_SUCCESS)
	{
		LogFatal(LogVulkan) << "Failed to enumerate physical devices" << endl;
	}

	int32_t firstDiscreteGpu{ -1 };
	int32_t firstIntegratedGpu{ -1 };

	LogInfo(LogVulkan) << "Enumerating Vulkan physical devices..." << endl;

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
		LogFatal(LogVulkan) << "Failed to select a Vulkan physical device" << endl;
	}

	m_caps.ReadCaps(*m_physicalDevice);
	if (g_graphicsDeviceOptions.logDeviceFeatures)
	{
		m_caps.LogCaps();
	}
}


Kodiak::VK::GraphicsDevice* Kodiak::VK::CreateDeviceVK(const Kodiak::GraphicsDeviceDesc& desc)
{
	GraphicsDevice* device = new GraphicsDevice;

	device->Initialize(desc);

	return device;
}