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

#include "Graphics\GraphicsDevice.h"

#include "Graphics\VK\RefCountingVK.h"


namespace Kodiak::VK
{

struct VulkanVersionInfo
{
	uint32_t variant{ 0 };
	uint32_t major{ 0 };
	uint32_t minor{ 0 };
	uint32_t patch{ 0 };
};

VulkanVersionInfo DecodeVulkanVersion(uint32_t packedVersion);
std::string VulkanVersionInfoToString(VulkanVersionInfo versionInfo);
std::string VulkanVersionToString(uint32_t packedVersion);


class GraphicsDevice : public IntrusiveCounter<Kodiak::IGraphicsDevice>
{
public:
	GraphicsDevice();
	~GraphicsDevice() final;

	void Initialize(const GraphicsDeviceDesc& desc);

private:
	void CreateInstance();
	void SelectPhysicalDevice();

private:
	// Device info
	// TODO - put this stuff in a struct
	GraphicsDeviceDesc m_deviceDesc{};
	std::string m_deviceName{ "Unknown" };
	VulkanVersionInfo m_versionInfo{};

	 // Vulkan objects
	VkInstanceHandle m_instance;
	VkPhysicalDeviceHandle m_physicalDevice;
};

using DeviceHandle = IntrusivePtr<GraphicsDevice>;

GraphicsDevice* CreateDeviceVK(const GraphicsDeviceDesc& desc);

inline LogCategory LogVulkan{ "LogVulkan" };

} // namespace Kodiak::VK