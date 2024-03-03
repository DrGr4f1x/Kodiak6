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

using namespace Kodiak;
using namespace Kodiak::VK;
using namespace std;


GraphicsDevice::GraphicsDevice()
{
	LOG_INFO << "Creating Vulkan device";
}


GraphicsDevice::~GraphicsDevice()
{
	LOG_INFO << "Destroying Vulkan device";
}


Kodiak::VK::GraphicsDevice* Kodiak::VK::CreateDeviceVK(const Kodiak::GraphicsDeviceDesc& desc)
{
	GraphicsDevice* device = new GraphicsDevice;
	return device;
}