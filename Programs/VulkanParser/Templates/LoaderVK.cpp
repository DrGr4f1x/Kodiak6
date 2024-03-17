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

#include "LoaderVk.h"


static void LoadRootInternal(void* context, PFN_vkVoidFunction (*load)(void*, const char*));
static void LoadInstanceInternal(void* context, PFN_vkVoidFunction (*load)(void*, const char*));
static void LoadDeviceInternal(void* context, PFN_vkVoidFunction (*load)(void*, const char*));

static PFN_vkVoidFunction vkGetInstanceProcAddrInternal(void* context, const char* name)
{
	return vkGetInstanceProcAddr((VkInstance)context, name);
}

static PFN_vkVoidFunction vkGetDeviceProcAddrInternal(void* context, const char* name)
{
	return vkGetDeviceProcAddr((VkDevice)context, name);
}


namespace Kodiak::VK
{

VkResult InitializeLoader()
{
	HMODULE module = LoadLibraryA("vulkan-1.dll");
	if (!module)
	{
		return VK_ERROR_INITIALIZATION_FAILED;
	}

	vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)(void(*)(void))GetProcAddress(module, "vkGetInstanceProcAddr");

	LoadRootInternal(nullptr, vkGetInstanceProcAddrInternal);

	return VK_SUCCESS;
}


void LoadInstanceFunctions(VkInstance instance)
{
	LoadInstanceInternal(instance, vkGetInstanceProcAddrInternal);
	LoadDeviceInternal(instance, vkGetInstanceProcAddrInternal);
}


void LoadInstanceFunctionsOnly(VkInstance instance)
{
	LoadInstanceInternal(instance, vkGetInstanceProcAddrInternal);
}


void LoadDeviceFunctions(VkDevice device)
{
	LoadDeviceInternal(device, vkGetDeviceProcAddrInternal);
}

} // namespace Kodiak::VK


static void LoadRootInternal(void* context, PFN_vkVoidFunction(*load)(void*, const char*))
{
	// KODIAK_GEN_INIT_LOADER
	// KODIAK_GEN_INIT_LOADER
}


static void LoadInstanceInternal(void* context, PFN_vkVoidFunction(*load)(void*, const char*))
{
	// KODIAK_GEN_LOAD_INSTANCE
	// KODIAK_GEN_LOAD_INSTANCE
}


static void LoadDeviceInternal(void* context, PFN_vkVoidFunction(*load)(void*, const char*))
{
	// KODIAK_GEN_LOAD_DEVICE
	// KODIAK_GEN_LOAD_DEVICE
}


// KODIAK_GEN_SOURCE_FUNCTION_PTRS
// KODIAK_GEN_SOURCE_FUNCTION_PTRS