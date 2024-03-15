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


// Vulkan headers
#define FORCE_VULKAN_VALIDATION 0
#define ENABLE_VULKAN_VALIDATION (ENABLE_DEBUG_LAYER || FORCE_VULKAN_VALIDATION)

#define VK_USE_PLATFORM_WIN32_KHR
#define VK_NO_PROTOTYPES 1
#include <vulkan.h>
#pragma comment(lib, "vulkan-1.lib")


#include "Graphics\GraphicsCommon.h"
#include "Graphics\VK\RefCountingVK.h"
#include "Graphics\VK\VersionVK.h"


#define VK_SUCCEEDED(res) (res == VK_SUCCESS)
#define VK_FAILED(res) (res != VK_SUCCESS)

namespace Kodiak::VK
{

inline LogCategory LogVulkan{ "LogVulkan" };

} // namespace Kodiak::VK