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

private:
	ExtensionManager* m_extensionManager{ nullptr };
	VulkanVersionInfo m_versionInfo{};

	VkInstanceHandle m_instance;
	VkPhysicalDeviceHandle m_physicalDevice;

	DeviceCaps* m_caps{ nullptr };
};

} // namespace Kodiak::VK