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

#include "Graphics\Interfaces.h"

#include "DeviceCapsVK.h"
#include "RefCountingVK.h"


namespace Kodiak::VK
{

class GraphicsDevice : public IntrusiveCounter<IGraphicsDevice>
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

	// Device caps
	DeviceCaps m_caps{};
};

GraphicsDevice* CreateDeviceVK(const GraphicsDeviceDesc& desc);

} // namespace Kodiak::VK