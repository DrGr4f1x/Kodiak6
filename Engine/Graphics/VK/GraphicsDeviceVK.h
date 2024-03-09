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

class GraphicsDevice : public IntrusiveCounter<Kodiak::IGraphicsDevice>
{
public:
	GraphicsDevice();
	~GraphicsDevice() final;

	void Initialize(const GraphicsDeviceDesc& desc);

private:
	void CreateInstance();

private:
	// Device info
	GraphicsDeviceDesc m_deviceDesc{};
	std::string m_deviceName{ "Unknown" };

	 // Vulkan objects
	VkInstanceHandle m_instance;
};

using DeviceHandle = IntrusivePtr<GraphicsDevice>;

GraphicsDevice* CreateDeviceVK(const GraphicsDeviceDesc& desc);

inline LogCategory LogVulkan{ "LogVulkan" };

} // namespace Kodiak::VK