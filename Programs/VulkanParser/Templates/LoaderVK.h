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

#include "Graphics\VK\VulkanCommon.h"


namespace Kodiak::VK
{

// Loads the function vkGetInstanceProcAddr, which is used to load VkInstance functions and (optionally) VkDevice functions.
VkResult InitializeLoader();

// Loads all the VkInstance and VkDevice functions for an given VkInstance.
void LoadInstanceFunctions(VkInstance instance);

// Loads only the VkInstance functions.  Must call LoadDeviceFunctions separately.
void LoadInstanceFunctionsOnly(VkInstance instance);

// Loads VkDevice functions for a given VkDevice.
void LoadDeviceFunctions(VkDevice device);

} // namespace Kodiak::VK


// KODIAK_GEN_HEADER_FUNCTION_PTRS
// KODIAK_GEN_HEADER_FUNCTION_PTRS