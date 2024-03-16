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

#include "Graphics\DeviceManager.h"
#include "Graphics\VK\VulkanCommon.h"


namespace Kodiak::VK
{

// Forward declarations
struct DeviceCaps;
class ExtensionManager;


class DeviceManagerVK : public DeviceManager
{
public:
	DeviceManagerVK() = default;
	~DeviceManagerVK() final;

protected:
	bool CreateInstanceInternal() final;
	bool CreateDevice() final;
	bool CreateSwapChain() final;

	void SetRequiredInstanceLayersAndExtensions();
	std::vector<std::pair<AdapterInfo, VkPhysicalDevice>> EnumeratePhysicalDevices();
	bool SelectPhysicalDevice();
	void GetQueueFamilyIndices();
	int32_t GetQueueFamilyIndex(VkQueueFlags queueFlags);

private:
	ExtensionManager* m_extensionManager{ nullptr };
	VulkanVersionInfo m_versionInfo{};

	VkInstanceHandle m_instance;
	VkPhysicalDeviceHandle m_physicalDevice;

	std::unique_ptr<DeviceCaps> m_caps;

	// Queues and queue families
	std::vector<VkQueueFamilyProperties> m_queueFamilyProperties;
	struct
	{
		int32_t graphics{ -1 };
		int32_t compute{ -1 };
		int32_t transfer{ -1 };
	} m_queueFamilyIndices;
};

} // namespace Kodiak::VK