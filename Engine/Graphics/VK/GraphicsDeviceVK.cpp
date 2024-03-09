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

#include "GraphicsDeviceVK.h"

#include "LoaderVk.h"

using namespace Kodiak;
using namespace Kodiak::VK;
using namespace std;


namespace
{

constexpr uint32_t g_requiredVulkanVersion{ VK_API_VERSION_1_3 };

} // anonymous namespace


namespace Kodiak::VK
{

VulkanVersionInfo DecodeVulkanVersion(uint32_t packedVersion)
{
	VulkanVersionInfo info{};
	info.variant = VK_API_VERSION_VARIANT(packedVersion);
	info.major = VK_API_VERSION_MAJOR(packedVersion);
	info.minor = VK_API_VERSION_MINOR(packedVersion);
	info.patch = VK_API_VERSION_PATCH(packedVersion);
	return info;
}


string VulkanVersionInfoToString(VulkanVersionInfo versionInfo)
{
	return format("{}.{}.{}", versionInfo.major, versionInfo.minor, versionInfo.patch);
}


string VulkanVersionToString(uint32_t packedVersion)
{
	return VulkanVersionInfoToString(DecodeVulkanVersion(packedVersion));
}

} // namespace Kodiak::VK


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
			m_versionInfo.variant, VulkanVersionInfoToString(m_versionInfo)) << endl;
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
	res = vkEnumeratePhysicalDevices(*m_instance.Get(), &gpuCount, nullptr);
	if (res != VK_SUCCESS)
	{
		LogFatal(LogVulkan) << "Failed to get physical device count" << endl;
	}

	// Enumerate physical devices
	vector<VkPhysicalDevice> physicalDevices(gpuCount);
	res = vkEnumeratePhysicalDevices(*m_instance.Get(), &gpuCount, physicalDevices.data());
	if (res != VK_SUCCESS)
	{
		LogFatal(LogVulkan) << "Failed to enumerate physical devices" << endl;
	}

	VkPhysicalDeviceProperties2 properties2{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2 };
	VkPhysicalDeviceVulkan11Properties properties11{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES };
	VkPhysicalDeviceVulkan12Properties properties12{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES };
	VkPhysicalDeviceVulkan12Properties properties13{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_PROPERTIES };
	properties2.pNext = &properties11;
	properties11.pNext = &properties12;
	properties12.pNext = &properties13;
	VkPhysicalDeviceProperties& properties{ properties2.properties };

	int32_t firstDiscreteGpu{ -1 };
	int32_t firstIntegratedGpu{ -1 };

	LogInfo(LogVulkan) << "Enumerating Vulkan physical devices..." << endl;

	for (size_t deviceIdx = 0; deviceIdx < physicalDevices.size(); ++deviceIdx)
	{
		vkGetPhysicalDeviceProperties2(physicalDevices[deviceIdx], &properties2);

		auto deviceType = properties.deviceType;

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

		string deviceName = properties.deviceName;
		LogInfo(LogVulkan) << format("  {} physical device {} is Vulkan-capable: {} (VendorId: {:#x}, DeviceId: {:#x}, API version: {})",
			deviceTypeStr,
			deviceIdx,
			deviceName,
			properties.vendorID, properties.deviceID, VulkanVersionToString(properties.apiVersion))
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

		LogInfo(LogVulkan) << "Selected integrated Vulkan physical device " << firstDiscreteGpu << endl;
	}
	else
	{
		LogFatal(LogVulkan) << "Failed to select a Vulkan physical device" << endl;
	}
}


Kodiak::VK::GraphicsDevice* Kodiak::VK::CreateDeviceVK(const Kodiak::GraphicsDeviceDesc& desc)
{
	GraphicsDevice* device = new GraphicsDevice;

	device->Initialize(desc);

	return device;
}