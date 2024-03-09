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
		LogFatal(LogVulkan) << "Unable to initialize Vulkan loader";
	}

	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = desc.appName.c_str();
	appInfo.pEngineName = "Kodiak";
	appInfo.apiVersion = VK_API_VERSION_1_3;
}


Kodiak::VK::GraphicsDevice* Kodiak::VK::CreateDeviceVK(const Kodiak::GraphicsDeviceDesc& desc)
{
	GraphicsDevice* device = new GraphicsDevice;

	device->Initialize(desc);

	return device;
}