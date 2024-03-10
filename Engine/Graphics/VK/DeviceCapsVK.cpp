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

#include "DeviceCapsVK.h"

#include "Graphics\GraphicsEnums.h"

#include "GraphicsDeviceVK.h"
#include "LoaderVk.h"
#include "StringsVK.h"


using namespace Kodiak;
using namespace Kodiak::VK;
using namespace std;


DeviceCaps::DeviceCaps()
{
	// Attach pNext pointers
	properties2.pNext = &properties11;
	properties11.pNext = &properties12;
	properties12.pNext = &properties13;
	properties13.pNext = nullptr;

	memoryProperties2.pNext = &memoryBudgetProperties;
	memoryBudgetProperties.pNext = nullptr;

	features2.pNext = &features11;
	features11.pNext = &features12;
	features12.pNext = &features13;
	features13.pNext = nullptr;
}


void DeviceCaps::ReadCaps(VkPhysicalDevice physicalDevice)
{
	if (!m_capsRead)
	{
		vkGetPhysicalDeviceProperties2(physicalDevice, &properties2);
		vkGetPhysicalDeviceMemoryProperties2(physicalDevice, &memoryProperties2);
		vkGetPhysicalDeviceFeatures2(physicalDevice, &features2);

		version = DecodeVulkanVersion(properties.apiVersion);

		m_capsRead = true;
	}
}


void DeviceCaps::LogCaps()
{
	LogInfo(LogVulkan) << "  Device Caps" << endl;

	constexpr const char* formatStr = "      {:48} {}";
	constexpr const char* formatStr2 = "        {:46} {}";

	// Vulkan 1.0 properties
	LogInfo(LogVulkan) << "    Vulkan 1.0 properties" << endl;
	LogInfo(LogVulkan) << format(formatStr, "apiVersion:", VulkanVersionInfoToString(version)) << endl;
	LogInfo(LogVulkan) << format("      {:48} {:#x}", "driverVersion:", properties.driverVersion) << endl;
	LogInfo(LogVulkan) << format("      {:48} {} ({:#x})", "vendorID:", VendorIdToString(properties.vendorID), properties.vendorID) << endl;
	LogInfo(LogVulkan) << format("      {:48} {:#x}", "deviceID:", properties.deviceID) << endl;
	LogInfo(LogVulkan) << format(formatStr, "deviceType:", VkTypeToString(properties.deviceType)) << endl;
	// Vulkan 1.0 properties - limits
	LogInfo(LogVulkan) << "    Vulkan 1.0 properties.limits" << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxImageDimension1D:", properties.limits.maxImageDimension1D) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxImageDimension2D:", properties.limits.maxImageDimension2D) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxImageDimension3D:", properties.limits.maxImageDimension3D) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxImageDimensionCube:", properties.limits.maxImageDimensionCube) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxImageArrayLayers:", properties.limits.maxImageArrayLayers) << endl;
}