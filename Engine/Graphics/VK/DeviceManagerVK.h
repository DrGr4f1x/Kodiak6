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

#include "Graphics\CreationParams.h"
#include "Graphics\VK\VulkanCommon.h"


namespace Kodiak::VK
{

// Forward declarations
struct DeviceCaps;
class Device;
class ExtensionManager;


class DeviceManager : public IDeviceManager, public NonCopyable
{
	IMPLEMENT_IOBJECT

public:
	explicit DeviceManager(const DeviceManagerCreationParams& creationParams);
	~DeviceManager() final;

	void BeginFrame() final;
	void Present() final;

protected:
	void Initialize();

	bool CreateInstance();
	bool CreateDevice();
	bool CreateSwapChain();

	void SetRequiredInstanceLayersAndExtensions();
	bool InstallDebugMessenger();
	std::vector<std::pair<AdapterInfo, VkPhysicalDevice>> EnumeratePhysicalDevices();
	bool CreateWindowSurface();
	bool SelectPhysicalDevice();
	void GetQueueFamilyIndices();
	int32_t GetQueueFamilyIndex(VkQueueFlags queueFlags);

private:
	// Device manager properties
	DeviceManagerCreationParams m_creationParams{};

	std::unique_ptr<ExtensionManager> m_extensionManager;
	VulkanVersionInfo m_versionInfo{};

	// Vulkan instance objects owned by the DeviceManager
	VkInstanceHandle m_vkInstance;
	VkDebugUtilsMessengerHandle m_vkDebugMessenger;
	VkPhysicalDeviceHandle m_vkPhysicalDevice;
	VkSurfaceHandle m_vkSurface;

	// Kodiak objects
	DeviceHandle m_device;

	std::unique_ptr<DeviceCaps> m_caps;

	// Queues and queue families
	// TODO - Move this stuff to GraphicsDevice and have it create it's own Vulkan object
	std::vector<VkQueueFamilyProperties> m_queueFamilyProperties;
	struct
	{
		int32_t graphics{ -1 };
		int32_t compute{ -1 };
		int32_t transfer{ -1 };
		int32_t present{ -1 };
	} m_queueFamilyIndices;
};

} // namespace Kodiak::VK