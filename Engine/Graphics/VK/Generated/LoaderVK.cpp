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
#if defined(VK_VERSION_1_0)
	vkCreateInstance = (PFN_vkCreateInstance)load(context, "vkCreateInstance");
	vkEnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties)load(context, "vkEnumerateInstanceExtensionProperties");
	vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties)load(context, "vkEnumerateInstanceLayerProperties");
#endif // defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
	vkEnumerateInstanceVersion = (PFN_vkEnumerateInstanceVersion)load(context, "vkEnumerateInstanceVersion");
#endif // defined(VK_VERSION_1_1)
	// KODIAK_GEN_INIT_LOADER
}


static void LoadInstanceInternal(void* context, PFN_vkVoidFunction(*load)(void*, const char*))
{
	// KODIAK_GEN_LOAD_INSTANCE
#if defined(VK_VERSION_1_0)
	vkDestroyInstance = (PFN_vkDestroyInstance)load(context, "vkDestroyInstance");
	vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices)load(context, "vkEnumeratePhysicalDevices");
	vkGetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures)load(context, "vkGetPhysicalDeviceFeatures");
	vkGetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties)load(context, "vkGetPhysicalDeviceFormatProperties");
	vkGetPhysicalDeviceImageFormatProperties = (PFN_vkGetPhysicalDeviceImageFormatProperties)load(context, "vkGetPhysicalDeviceImageFormatProperties");
	vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)load(context, "vkGetPhysicalDeviceProperties");
	vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties)load(context, "vkGetPhysicalDeviceQueueFamilyProperties");
	vkGetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties)load(context, "vkGetPhysicalDeviceMemoryProperties");
	vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr)load(context, "vkGetDeviceProcAddr");
	vkCreateDevice = (PFN_vkCreateDevice)load(context, "vkCreateDevice");
	vkEnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties)load(context, "vkEnumerateDeviceExtensionProperties");
	vkEnumerateDeviceLayerProperties = (PFN_vkEnumerateDeviceLayerProperties)load(context, "vkEnumerateDeviceLayerProperties");
	vkGetPhysicalDeviceSparseImageFormatProperties = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties)load(context, "vkGetPhysicalDeviceSparseImageFormatProperties");
#endif // defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
	vkEnumeratePhysicalDeviceGroups = (PFN_vkEnumeratePhysicalDeviceGroups)load(context, "vkEnumeratePhysicalDeviceGroups");
	vkGetPhysicalDeviceFeatures2 = (PFN_vkGetPhysicalDeviceFeatures2)load(context, "vkGetPhysicalDeviceFeatures2");
	vkGetPhysicalDeviceProperties2 = (PFN_vkGetPhysicalDeviceProperties2)load(context, "vkGetPhysicalDeviceProperties2");
	vkGetPhysicalDeviceFormatProperties2 = (PFN_vkGetPhysicalDeviceFormatProperties2)load(context, "vkGetPhysicalDeviceFormatProperties2");
	vkGetPhysicalDeviceImageFormatProperties2 = (PFN_vkGetPhysicalDeviceImageFormatProperties2)load(context, "vkGetPhysicalDeviceImageFormatProperties2");
	vkGetPhysicalDeviceQueueFamilyProperties2 = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2)load(context, "vkGetPhysicalDeviceQueueFamilyProperties2");
	vkGetPhysicalDeviceMemoryProperties2 = (PFN_vkGetPhysicalDeviceMemoryProperties2)load(context, "vkGetPhysicalDeviceMemoryProperties2");
	vkGetPhysicalDeviceSparseImageFormatProperties2 = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2)load(context, "vkGetPhysicalDeviceSparseImageFormatProperties2");
	vkGetPhysicalDeviceExternalBufferProperties = (PFN_vkGetPhysicalDeviceExternalBufferProperties)load(context, "vkGetPhysicalDeviceExternalBufferProperties");
	vkGetPhysicalDeviceExternalFenceProperties = (PFN_vkGetPhysicalDeviceExternalFenceProperties)load(context, "vkGetPhysicalDeviceExternalFenceProperties");
	vkGetPhysicalDeviceExternalSemaphoreProperties = (PFN_vkGetPhysicalDeviceExternalSemaphoreProperties)load(context, "vkGetPhysicalDeviceExternalSemaphoreProperties");
#endif // defined(VK_VERSION_1_1)
#if defined(VK_VERSION_1_3)
	vkGetPhysicalDeviceToolProperties = (PFN_vkGetPhysicalDeviceToolProperties)load(context, "vkGetPhysicalDeviceToolProperties");
#endif // defined(VK_VERSION_1_3)
#if defined(VK_EXT_acquire_drm_display)
	vkAcquireDrmDisplayEXT = (PFN_vkAcquireDrmDisplayEXT)load(context, "vkAcquireDrmDisplayEXT");
	vkGetDrmDisplayEXT = (PFN_vkGetDrmDisplayEXT)load(context, "vkGetDrmDisplayEXT");
#endif // defined(VK_EXT_acquire_drm_display)
#if defined(VK_EXT_acquire_xlib_display)
	vkAcquireXlibDisplayEXT = (PFN_vkAcquireXlibDisplayEXT)load(context, "vkAcquireXlibDisplayEXT");
	vkGetRandROutputDisplayEXT = (PFN_vkGetRandROutputDisplayEXT)load(context, "vkGetRandROutputDisplayEXT");
#endif // defined(VK_EXT_acquire_xlib_display)
#if defined(VK_EXT_calibrated_timestamps)
	vkGetPhysicalDeviceCalibrateableTimeDomainsEXT = (PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT)load(context, "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT");
#endif // defined(VK_EXT_calibrated_timestamps)
#if defined(VK_EXT_debug_report)
	vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)load(context, "vkCreateDebugReportCallbackEXT");
	vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)load(context, "vkDestroyDebugReportCallbackEXT");
	vkDebugReportMessageEXT = (PFN_vkDebugReportMessageEXT)load(context, "vkDebugReportMessageEXT");
#endif // defined(VK_EXT_debug_report)
#if defined(VK_EXT_debug_utils)
	vkSetDebugUtilsObjectNameEXT = (PFN_vkSetDebugUtilsObjectNameEXT)load(context, "vkSetDebugUtilsObjectNameEXT");
	vkSetDebugUtilsObjectTagEXT = (PFN_vkSetDebugUtilsObjectTagEXT)load(context, "vkSetDebugUtilsObjectTagEXT");
	vkQueueBeginDebugUtilsLabelEXT = (PFN_vkQueueBeginDebugUtilsLabelEXT)load(context, "vkQueueBeginDebugUtilsLabelEXT");
	vkQueueEndDebugUtilsLabelEXT = (PFN_vkQueueEndDebugUtilsLabelEXT)load(context, "vkQueueEndDebugUtilsLabelEXT");
	vkQueueInsertDebugUtilsLabelEXT = (PFN_vkQueueInsertDebugUtilsLabelEXT)load(context, "vkQueueInsertDebugUtilsLabelEXT");
	vkCmdBeginDebugUtilsLabelEXT = (PFN_vkCmdBeginDebugUtilsLabelEXT)load(context, "vkCmdBeginDebugUtilsLabelEXT");
	vkCmdEndDebugUtilsLabelEXT = (PFN_vkCmdEndDebugUtilsLabelEXT)load(context, "vkCmdEndDebugUtilsLabelEXT");
	vkCmdInsertDebugUtilsLabelEXT = (PFN_vkCmdInsertDebugUtilsLabelEXT)load(context, "vkCmdInsertDebugUtilsLabelEXT");
	vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)load(context, "vkCreateDebugUtilsMessengerEXT");
	vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)load(context, "vkDestroyDebugUtilsMessengerEXT");
	vkSubmitDebugUtilsMessageEXT = (PFN_vkSubmitDebugUtilsMessageEXT)load(context, "vkSubmitDebugUtilsMessageEXT");
#endif // defined(VK_EXT_debug_utils)
#if defined(VK_EXT_direct_mode_display)
	vkReleaseDisplayEXT = (PFN_vkReleaseDisplayEXT)load(context, "vkReleaseDisplayEXT");
#endif // defined(VK_EXT_direct_mode_display)
#if defined(VK_EXT_directfb_surface)
	vkCreateDirectFBSurfaceEXT = (PFN_vkCreateDirectFBSurfaceEXT)load(context, "vkCreateDirectFBSurfaceEXT");
	vkGetPhysicalDeviceDirectFBPresentationSupportEXT = (PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT)load(context, "vkGetPhysicalDeviceDirectFBPresentationSupportEXT");
#endif // defined(VK_EXT_directfb_surface)
#if defined(VK_EXT_display_surface_counter)
	vkGetPhysicalDeviceSurfaceCapabilities2EXT = (PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT)load(context, "vkGetPhysicalDeviceSurfaceCapabilities2EXT");
#endif // defined(VK_EXT_display_surface_counter)
#if defined(VK_EXT_full_screen_exclusive)
	vkGetPhysicalDeviceSurfacePresentModes2EXT = (PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT)load(context, "vkGetPhysicalDeviceSurfacePresentModes2EXT");
#endif // defined(VK_EXT_full_screen_exclusive)
#if defined(VK_EXT_headless_surface)
	vkCreateHeadlessSurfaceEXT = (PFN_vkCreateHeadlessSurfaceEXT)load(context, "vkCreateHeadlessSurfaceEXT");
#endif // defined(VK_EXT_headless_surface)
#if defined(VK_EXT_metal_surface)
	vkCreateMetalSurfaceEXT = (PFN_vkCreateMetalSurfaceEXT)load(context, "vkCreateMetalSurfaceEXT");
#endif // defined(VK_EXT_metal_surface)
#if defined(VK_EXT_sample_locations)
	vkGetPhysicalDeviceMultisamplePropertiesEXT = (PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT)load(context, "vkGetPhysicalDeviceMultisamplePropertiesEXT");
#endif // defined(VK_EXT_sample_locations)
#if defined(VK_EXT_tooling_info)
	vkGetPhysicalDeviceToolPropertiesEXT = (PFN_vkGetPhysicalDeviceToolPropertiesEXT)load(context, "vkGetPhysicalDeviceToolPropertiesEXT");
#endif // defined(VK_EXT_tooling_info)
#if defined(VK_FUCHSIA_imagepipe_surface)
	vkCreateImagePipeSurfaceFUCHSIA = (PFN_vkCreateImagePipeSurfaceFUCHSIA)load(context, "vkCreateImagePipeSurfaceFUCHSIA");
#endif // defined(VK_FUCHSIA_imagepipe_surface)
#if defined(VK_GGP_stream_descriptor_surface)
	vkCreateStreamDescriptorSurfaceGGP = (PFN_vkCreateStreamDescriptorSurfaceGGP)load(context, "vkCreateStreamDescriptorSurfaceGGP");
#endif // defined(VK_GGP_stream_descriptor_surface)
#if defined(VK_KHR_android_surface)
	vkCreateAndroidSurfaceKHR = (PFN_vkCreateAndroidSurfaceKHR)load(context, "vkCreateAndroidSurfaceKHR");
#endif // defined(VK_KHR_android_surface)
#if defined(VK_KHR_calibrated_timestamps)
	vkGetPhysicalDeviceCalibrateableTimeDomainsKHR = (PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR)load(context, "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR");
#endif // defined(VK_KHR_calibrated_timestamps)
#if defined(VK_KHR_cooperative_matrix)
	vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR = (PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR)load(context, "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR");
#endif // defined(VK_KHR_cooperative_matrix)
#if defined(VK_KHR_device_group_creation)
	vkEnumeratePhysicalDeviceGroupsKHR = (PFN_vkEnumeratePhysicalDeviceGroupsKHR)load(context, "vkEnumeratePhysicalDeviceGroupsKHR");
#endif // defined(VK_KHR_device_group_creation)
#if defined(VK_KHR_display)
	vkGetPhysicalDeviceDisplayPropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPropertiesKHR)load(context, "vkGetPhysicalDeviceDisplayPropertiesKHR");
	vkGetPhysicalDeviceDisplayPlanePropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR)load(context, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR");
	vkGetDisplayPlaneSupportedDisplaysKHR = (PFN_vkGetDisplayPlaneSupportedDisplaysKHR)load(context, "vkGetDisplayPlaneSupportedDisplaysKHR");
	vkGetDisplayModePropertiesKHR = (PFN_vkGetDisplayModePropertiesKHR)load(context, "vkGetDisplayModePropertiesKHR");
	vkCreateDisplayModeKHR = (PFN_vkCreateDisplayModeKHR)load(context, "vkCreateDisplayModeKHR");
	vkGetDisplayPlaneCapabilitiesKHR = (PFN_vkGetDisplayPlaneCapabilitiesKHR)load(context, "vkGetDisplayPlaneCapabilitiesKHR");
	vkCreateDisplayPlaneSurfaceKHR = (PFN_vkCreateDisplayPlaneSurfaceKHR)load(context, "vkCreateDisplayPlaneSurfaceKHR");
#endif // defined(VK_KHR_display)
#if defined(VK_KHR_external_fence_capabilities)
	vkGetPhysicalDeviceExternalFencePropertiesKHR = (PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR)load(context, "vkGetPhysicalDeviceExternalFencePropertiesKHR");
#endif // defined(VK_KHR_external_fence_capabilities)
#if defined(VK_KHR_external_memory_capabilities)
	vkGetPhysicalDeviceExternalBufferPropertiesKHR = (PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR)load(context, "vkGetPhysicalDeviceExternalBufferPropertiesKHR");
#endif // defined(VK_KHR_external_memory_capabilities)
#if defined(VK_KHR_external_semaphore_capabilities)
	vkGetPhysicalDeviceExternalSemaphorePropertiesKHR = (PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR)load(context, "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR");
#endif // defined(VK_KHR_external_semaphore_capabilities)
#if defined(VK_KHR_fragment_shading_rate)
	vkGetPhysicalDeviceFragmentShadingRatesKHR = (PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR)load(context, "vkGetPhysicalDeviceFragmentShadingRatesKHR");
#endif // defined(VK_KHR_fragment_shading_rate)
#if defined(VK_KHR_get_display_properties2)
	vkGetPhysicalDeviceDisplayProperties2KHR = (PFN_vkGetPhysicalDeviceDisplayProperties2KHR)load(context, "vkGetPhysicalDeviceDisplayProperties2KHR");
	vkGetPhysicalDeviceDisplayPlaneProperties2KHR = (PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR)load(context, "vkGetPhysicalDeviceDisplayPlaneProperties2KHR");
	vkGetDisplayModeProperties2KHR = (PFN_vkGetDisplayModeProperties2KHR)load(context, "vkGetDisplayModeProperties2KHR");
	vkGetDisplayPlaneCapabilities2KHR = (PFN_vkGetDisplayPlaneCapabilities2KHR)load(context, "vkGetDisplayPlaneCapabilities2KHR");
#endif // defined(VK_KHR_get_display_properties2)
#if defined(VK_KHR_get_physical_device_properties2)
	vkGetPhysicalDeviceFeatures2KHR = (PFN_vkGetPhysicalDeviceFeatures2KHR)load(context, "vkGetPhysicalDeviceFeatures2KHR");
	vkGetPhysicalDeviceProperties2KHR = (PFN_vkGetPhysicalDeviceProperties2KHR)load(context, "vkGetPhysicalDeviceProperties2KHR");
	vkGetPhysicalDeviceFormatProperties2KHR = (PFN_vkGetPhysicalDeviceFormatProperties2KHR)load(context, "vkGetPhysicalDeviceFormatProperties2KHR");
	vkGetPhysicalDeviceImageFormatProperties2KHR = (PFN_vkGetPhysicalDeviceImageFormatProperties2KHR)load(context, "vkGetPhysicalDeviceImageFormatProperties2KHR");
	vkGetPhysicalDeviceQueueFamilyProperties2KHR = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR)load(context, "vkGetPhysicalDeviceQueueFamilyProperties2KHR");
	vkGetPhysicalDeviceMemoryProperties2KHR = (PFN_vkGetPhysicalDeviceMemoryProperties2KHR)load(context, "vkGetPhysicalDeviceMemoryProperties2KHR");
	vkGetPhysicalDeviceSparseImageFormatProperties2KHR = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR)load(context, "vkGetPhysicalDeviceSparseImageFormatProperties2KHR");
#endif // defined(VK_KHR_get_physical_device_properties2)
#if defined(VK_KHR_get_surface_capabilities2)
	vkGetPhysicalDeviceSurfaceCapabilities2KHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR)load(context, "vkGetPhysicalDeviceSurfaceCapabilities2KHR");
	vkGetPhysicalDeviceSurfaceFormats2KHR = (PFN_vkGetPhysicalDeviceSurfaceFormats2KHR)load(context, "vkGetPhysicalDeviceSurfaceFormats2KHR");
#endif // defined(VK_KHR_get_surface_capabilities2)
#if defined(VK_KHR_performance_query)
	vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = (PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR)load(context, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR");
	vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = (PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR)load(context, "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR");
#endif // defined(VK_KHR_performance_query)
#if defined(VK_KHR_surface)
	vkDestroySurfaceKHR = (PFN_vkDestroySurfaceKHR)load(context, "vkDestroySurfaceKHR");
	vkGetPhysicalDeviceSurfaceSupportKHR = (PFN_vkGetPhysicalDeviceSurfaceSupportKHR)load(context, "vkGetPhysicalDeviceSurfaceSupportKHR");
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR)load(context, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
	vkGetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR)load(context, "vkGetPhysicalDeviceSurfaceFormatsKHR");
	vkGetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR)load(context, "vkGetPhysicalDeviceSurfacePresentModesKHR");
#endif // defined(VK_KHR_surface)
#if defined(VK_KHR_video_encode_queue)
	vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR = (PFN_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR)load(context, "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR");
#endif // defined(VK_KHR_video_encode_queue)
#if defined(VK_KHR_video_queue)
	vkGetPhysicalDeviceVideoCapabilitiesKHR = (PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR)load(context, "vkGetPhysicalDeviceVideoCapabilitiesKHR");
	vkGetPhysicalDeviceVideoFormatPropertiesKHR = (PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR)load(context, "vkGetPhysicalDeviceVideoFormatPropertiesKHR");
#endif // defined(VK_KHR_video_queue)
#if defined(VK_KHR_wayland_surface)
	vkCreateWaylandSurfaceKHR = (PFN_vkCreateWaylandSurfaceKHR)load(context, "vkCreateWaylandSurfaceKHR");
	vkGetPhysicalDeviceWaylandPresentationSupportKHR = (PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR)load(context, "vkGetPhysicalDeviceWaylandPresentationSupportKHR");
#endif // defined(VK_KHR_wayland_surface)
#if defined(VK_KHR_win32_surface)
	vkCreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)load(context, "vkCreateWin32SurfaceKHR");
	vkGetPhysicalDeviceWin32PresentationSupportKHR = (PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)load(context, "vkGetPhysicalDeviceWin32PresentationSupportKHR");
#endif // defined(VK_KHR_win32_surface)
#if defined(VK_KHR_xcb_surface)
	vkCreateXcbSurfaceKHR = (PFN_vkCreateXcbSurfaceKHR)load(context, "vkCreateXcbSurfaceKHR");
	vkGetPhysicalDeviceXcbPresentationSupportKHR = (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)load(context, "vkGetPhysicalDeviceXcbPresentationSupportKHR");
#endif // defined(VK_KHR_xcb_surface)
#if defined(VK_KHR_xlib_surface)
	vkCreateXlibSurfaceKHR = (PFN_vkCreateXlibSurfaceKHR)load(context, "vkCreateXlibSurfaceKHR");
	vkGetPhysicalDeviceXlibPresentationSupportKHR = (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)load(context, "vkGetPhysicalDeviceXlibPresentationSupportKHR");
#endif // defined(VK_KHR_xlib_surface)
#if defined(VK_MVK_ios_surface)
	vkCreateIOSSurfaceMVK = (PFN_vkCreateIOSSurfaceMVK)load(context, "vkCreateIOSSurfaceMVK");
#endif // defined(VK_MVK_ios_surface)
#if defined(VK_MVK_macos_surface)
	vkCreateMacOSSurfaceMVK = (PFN_vkCreateMacOSSurfaceMVK)load(context, "vkCreateMacOSSurfaceMVK");
#endif // defined(VK_MVK_macos_surface)
#if defined(VK_NN_vi_surface)
	vkCreateViSurfaceNN = (PFN_vkCreateViSurfaceNN)load(context, "vkCreateViSurfaceNN");
#endif // defined(VK_NN_vi_surface)
#if defined(VK_NV_acquire_winrt_display)
	vkAcquireWinrtDisplayNV = (PFN_vkAcquireWinrtDisplayNV)load(context, "vkAcquireWinrtDisplayNV");
	vkGetWinrtDisplayNV = (PFN_vkGetWinrtDisplayNV)load(context, "vkGetWinrtDisplayNV");
#endif // defined(VK_NV_acquire_winrt_display)
#if defined(VK_NV_cooperative_matrix)
	vkGetPhysicalDeviceCooperativeMatrixPropertiesNV = (PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV)load(context, "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV");
#endif // defined(VK_NV_cooperative_matrix)
#if defined(VK_NV_coverage_reduction_mode)
	vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = (PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV)load(context, "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV");
#endif // defined(VK_NV_coverage_reduction_mode)
#if defined(VK_NV_external_memory_capabilities)
	vkGetPhysicalDeviceExternalImageFormatPropertiesNV = (PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV)load(context, "vkGetPhysicalDeviceExternalImageFormatPropertiesNV");
#endif // defined(VK_NV_external_memory_capabilities)
#if defined(VK_NV_optical_flow)
	vkGetPhysicalDeviceOpticalFlowImageFormatsNV = (PFN_vkGetPhysicalDeviceOpticalFlowImageFormatsNV)load(context, "vkGetPhysicalDeviceOpticalFlowImageFormatsNV");
#endif // defined(VK_NV_optical_flow)
#if defined(VK_QNX_screen_surface)
	vkCreateScreenSurfaceQNX = (PFN_vkCreateScreenSurfaceQNX)load(context, "vkCreateScreenSurfaceQNX");
	vkGetPhysicalDeviceScreenPresentationSupportQNX = (PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)load(context, "vkGetPhysicalDeviceScreenPresentationSupportQNX");
#endif // defined(VK_QNX_screen_surface)
#if defined(VK_KHR_device_group) && defined(VK_KHR_surface) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
	vkGetPhysicalDevicePresentRectanglesKHR = (PFN_vkGetPhysicalDevicePresentRectanglesKHR)load(context, "vkGetPhysicalDevicePresentRectanglesKHR");
#endif // defined(VK_KHR_device_group) && defined(VK_KHR_surface) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
	// KODIAK_GEN_LOAD_INSTANCE
}


static void LoadDeviceInternal(void* context, PFN_vkVoidFunction(*load)(void*, const char*))
{
	// KODIAK_GEN_LOAD_DEVICE
#if defined(VK_VERSION_1_0)
	vkDestroyDevice = (PFN_vkDestroyDevice)load(context, "vkDestroyDevice");
	vkGetDeviceQueue = (PFN_vkGetDeviceQueue)load(context, "vkGetDeviceQueue");
	vkQueueSubmit = (PFN_vkQueueSubmit)load(context, "vkQueueSubmit");
	vkQueueWaitIdle = (PFN_vkQueueWaitIdle)load(context, "vkQueueWaitIdle");
	vkDeviceWaitIdle = (PFN_vkDeviceWaitIdle)load(context, "vkDeviceWaitIdle");
	vkAllocateMemory = (PFN_vkAllocateMemory)load(context, "vkAllocateMemory");
	vkFreeMemory = (PFN_vkFreeMemory)load(context, "vkFreeMemory");
	vkMapMemory = (PFN_vkMapMemory)load(context, "vkMapMemory");
	vkUnmapMemory = (PFN_vkUnmapMemory)load(context, "vkUnmapMemory");
	vkFlushMappedMemoryRanges = (PFN_vkFlushMappedMemoryRanges)load(context, "vkFlushMappedMemoryRanges");
	vkInvalidateMappedMemoryRanges = (PFN_vkInvalidateMappedMemoryRanges)load(context, "vkInvalidateMappedMemoryRanges");
	vkGetDeviceMemoryCommitment = (PFN_vkGetDeviceMemoryCommitment)load(context, "vkGetDeviceMemoryCommitment");
	vkBindBufferMemory = (PFN_vkBindBufferMemory)load(context, "vkBindBufferMemory");
	vkBindImageMemory = (PFN_vkBindImageMemory)load(context, "vkBindImageMemory");
	vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements)load(context, "vkGetBufferMemoryRequirements");
	vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements)load(context, "vkGetImageMemoryRequirements");
	vkGetImageSparseMemoryRequirements = (PFN_vkGetImageSparseMemoryRequirements)load(context, "vkGetImageSparseMemoryRequirements");
	vkQueueBindSparse = (PFN_vkQueueBindSparse)load(context, "vkQueueBindSparse");
	vkCreateFence = (PFN_vkCreateFence)load(context, "vkCreateFence");
	vkDestroyFence = (PFN_vkDestroyFence)load(context, "vkDestroyFence");
	vkResetFences = (PFN_vkResetFences)load(context, "vkResetFences");
	vkGetFenceStatus = (PFN_vkGetFenceStatus)load(context, "vkGetFenceStatus");
	vkWaitForFences = (PFN_vkWaitForFences)load(context, "vkWaitForFences");
	vkCreateSemaphore = (PFN_vkCreateSemaphore)load(context, "vkCreateSemaphore");
	vkDestroySemaphore = (PFN_vkDestroySemaphore)load(context, "vkDestroySemaphore");
	vkCreateEvent = (PFN_vkCreateEvent)load(context, "vkCreateEvent");
	vkDestroyEvent = (PFN_vkDestroyEvent)load(context, "vkDestroyEvent");
	vkGetEventStatus = (PFN_vkGetEventStatus)load(context, "vkGetEventStatus");
	vkSetEvent = (PFN_vkSetEvent)load(context, "vkSetEvent");
	vkResetEvent = (PFN_vkResetEvent)load(context, "vkResetEvent");
	vkCreateQueryPool = (PFN_vkCreateQueryPool)load(context, "vkCreateQueryPool");
	vkDestroyQueryPool = (PFN_vkDestroyQueryPool)load(context, "vkDestroyQueryPool");
	vkGetQueryPoolResults = (PFN_vkGetQueryPoolResults)load(context, "vkGetQueryPoolResults");
	vkCreateBuffer = (PFN_vkCreateBuffer)load(context, "vkCreateBuffer");
	vkDestroyBuffer = (PFN_vkDestroyBuffer)load(context, "vkDestroyBuffer");
	vkCreateBufferView = (PFN_vkCreateBufferView)load(context, "vkCreateBufferView");
	vkDestroyBufferView = (PFN_vkDestroyBufferView)load(context, "vkDestroyBufferView");
	vkCreateImage = (PFN_vkCreateImage)load(context, "vkCreateImage");
	vkDestroyImage = (PFN_vkDestroyImage)load(context, "vkDestroyImage");
	vkGetImageSubresourceLayout = (PFN_vkGetImageSubresourceLayout)load(context, "vkGetImageSubresourceLayout");
	vkCreateImageView = (PFN_vkCreateImageView)load(context, "vkCreateImageView");
	vkDestroyImageView = (PFN_vkDestroyImageView)load(context, "vkDestroyImageView");
	vkCreateShaderModule = (PFN_vkCreateShaderModule)load(context, "vkCreateShaderModule");
	vkDestroyShaderModule = (PFN_vkDestroyShaderModule)load(context, "vkDestroyShaderModule");
	vkCreatePipelineCache = (PFN_vkCreatePipelineCache)load(context, "vkCreatePipelineCache");
	vkDestroyPipelineCache = (PFN_vkDestroyPipelineCache)load(context, "vkDestroyPipelineCache");
	vkGetPipelineCacheData = (PFN_vkGetPipelineCacheData)load(context, "vkGetPipelineCacheData");
	vkMergePipelineCaches = (PFN_vkMergePipelineCaches)load(context, "vkMergePipelineCaches");
	vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines)load(context, "vkCreateGraphicsPipelines");
	vkCreateComputePipelines = (PFN_vkCreateComputePipelines)load(context, "vkCreateComputePipelines");
	vkDestroyPipeline = (PFN_vkDestroyPipeline)load(context, "vkDestroyPipeline");
	vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout)load(context, "vkCreatePipelineLayout");
	vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout)load(context, "vkDestroyPipelineLayout");
	vkCreateSampler = (PFN_vkCreateSampler)load(context, "vkCreateSampler");
	vkDestroySampler = (PFN_vkDestroySampler)load(context, "vkDestroySampler");
	vkCreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout)load(context, "vkCreateDescriptorSetLayout");
	vkDestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout)load(context, "vkDestroyDescriptorSetLayout");
	vkCreateDescriptorPool = (PFN_vkCreateDescriptorPool)load(context, "vkCreateDescriptorPool");
	vkDestroyDescriptorPool = (PFN_vkDestroyDescriptorPool)load(context, "vkDestroyDescriptorPool");
	vkResetDescriptorPool = (PFN_vkResetDescriptorPool)load(context, "vkResetDescriptorPool");
	vkAllocateDescriptorSets = (PFN_vkAllocateDescriptorSets)load(context, "vkAllocateDescriptorSets");
	vkFreeDescriptorSets = (PFN_vkFreeDescriptorSets)load(context, "vkFreeDescriptorSets");
	vkUpdateDescriptorSets = (PFN_vkUpdateDescriptorSets)load(context, "vkUpdateDescriptorSets");
	vkCreateFramebuffer = (PFN_vkCreateFramebuffer)load(context, "vkCreateFramebuffer");
	vkDestroyFramebuffer = (PFN_vkDestroyFramebuffer)load(context, "vkDestroyFramebuffer");
	vkCreateRenderPass = (PFN_vkCreateRenderPass)load(context, "vkCreateRenderPass");
	vkDestroyRenderPass = (PFN_vkDestroyRenderPass)load(context, "vkDestroyRenderPass");
	vkGetRenderAreaGranularity = (PFN_vkGetRenderAreaGranularity)load(context, "vkGetRenderAreaGranularity");
	vkCreateCommandPool = (PFN_vkCreateCommandPool)load(context, "vkCreateCommandPool");
	vkDestroyCommandPool = (PFN_vkDestroyCommandPool)load(context, "vkDestroyCommandPool");
	vkResetCommandPool = (PFN_vkResetCommandPool)load(context, "vkResetCommandPool");
	vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)load(context, "vkAllocateCommandBuffers");
	vkFreeCommandBuffers = (PFN_vkFreeCommandBuffers)load(context, "vkFreeCommandBuffers");
	vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer)load(context, "vkBeginCommandBuffer");
	vkEndCommandBuffer = (PFN_vkEndCommandBuffer)load(context, "vkEndCommandBuffer");
	vkResetCommandBuffer = (PFN_vkResetCommandBuffer)load(context, "vkResetCommandBuffer");
	vkCmdBindPipeline = (PFN_vkCmdBindPipeline)load(context, "vkCmdBindPipeline");
	vkCmdSetViewport = (PFN_vkCmdSetViewport)load(context, "vkCmdSetViewport");
	vkCmdSetScissor = (PFN_vkCmdSetScissor)load(context, "vkCmdSetScissor");
	vkCmdSetLineWidth = (PFN_vkCmdSetLineWidth)load(context, "vkCmdSetLineWidth");
	vkCmdSetDepthBias = (PFN_vkCmdSetDepthBias)load(context, "vkCmdSetDepthBias");
	vkCmdSetBlendConstants = (PFN_vkCmdSetBlendConstants)load(context, "vkCmdSetBlendConstants");
	vkCmdSetDepthBounds = (PFN_vkCmdSetDepthBounds)load(context, "vkCmdSetDepthBounds");
	vkCmdSetStencilCompareMask = (PFN_vkCmdSetStencilCompareMask)load(context, "vkCmdSetStencilCompareMask");
	vkCmdSetStencilWriteMask = (PFN_vkCmdSetStencilWriteMask)load(context, "vkCmdSetStencilWriteMask");
	vkCmdSetStencilReference = (PFN_vkCmdSetStencilReference)load(context, "vkCmdSetStencilReference");
	vkCmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets)load(context, "vkCmdBindDescriptorSets");
	vkCmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer)load(context, "vkCmdBindIndexBuffer");
	vkCmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers)load(context, "vkCmdBindVertexBuffers");
	vkCmdDraw = (PFN_vkCmdDraw)load(context, "vkCmdDraw");
	vkCmdDrawIndexed = (PFN_vkCmdDrawIndexed)load(context, "vkCmdDrawIndexed");
	vkCmdDrawIndirect = (PFN_vkCmdDrawIndirect)load(context, "vkCmdDrawIndirect");
	vkCmdDrawIndexedIndirect = (PFN_vkCmdDrawIndexedIndirect)load(context, "vkCmdDrawIndexedIndirect");
	vkCmdDispatch = (PFN_vkCmdDispatch)load(context, "vkCmdDispatch");
	vkCmdDispatchIndirect = (PFN_vkCmdDispatchIndirect)load(context, "vkCmdDispatchIndirect");
	vkCmdCopyBuffer = (PFN_vkCmdCopyBuffer)load(context, "vkCmdCopyBuffer");
	vkCmdCopyImage = (PFN_vkCmdCopyImage)load(context, "vkCmdCopyImage");
	vkCmdBlitImage = (PFN_vkCmdBlitImage)load(context, "vkCmdBlitImage");
	vkCmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage)load(context, "vkCmdCopyBufferToImage");
	vkCmdCopyImageToBuffer = (PFN_vkCmdCopyImageToBuffer)load(context, "vkCmdCopyImageToBuffer");
	vkCmdUpdateBuffer = (PFN_vkCmdUpdateBuffer)load(context, "vkCmdUpdateBuffer");
	vkCmdFillBuffer = (PFN_vkCmdFillBuffer)load(context, "vkCmdFillBuffer");
	vkCmdClearColorImage = (PFN_vkCmdClearColorImage)load(context, "vkCmdClearColorImage");
	vkCmdClearDepthStencilImage = (PFN_vkCmdClearDepthStencilImage)load(context, "vkCmdClearDepthStencilImage");
	vkCmdClearAttachments = (PFN_vkCmdClearAttachments)load(context, "vkCmdClearAttachments");
	vkCmdResolveImage = (PFN_vkCmdResolveImage)load(context, "vkCmdResolveImage");
	vkCmdSetEvent = (PFN_vkCmdSetEvent)load(context, "vkCmdSetEvent");
	vkCmdResetEvent = (PFN_vkCmdResetEvent)load(context, "vkCmdResetEvent");
	vkCmdWaitEvents = (PFN_vkCmdWaitEvents)load(context, "vkCmdWaitEvents");
	vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier)load(context, "vkCmdPipelineBarrier");
	vkCmdBeginQuery = (PFN_vkCmdBeginQuery)load(context, "vkCmdBeginQuery");
	vkCmdEndQuery = (PFN_vkCmdEndQuery)load(context, "vkCmdEndQuery");
	vkCmdResetQueryPool = (PFN_vkCmdResetQueryPool)load(context, "vkCmdResetQueryPool");
	vkCmdWriteTimestamp = (PFN_vkCmdWriteTimestamp)load(context, "vkCmdWriteTimestamp");
	vkCmdCopyQueryPoolResults = (PFN_vkCmdCopyQueryPoolResults)load(context, "vkCmdCopyQueryPoolResults");
	vkCmdPushConstants = (PFN_vkCmdPushConstants)load(context, "vkCmdPushConstants");
	vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass)load(context, "vkCmdBeginRenderPass");
	vkCmdNextSubpass = (PFN_vkCmdNextSubpass)load(context, "vkCmdNextSubpass");
	vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass)load(context, "vkCmdEndRenderPass");
	vkCmdExecuteCommands = (PFN_vkCmdExecuteCommands)load(context, "vkCmdExecuteCommands");
#endif // defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
	vkBindBufferMemory2 = (PFN_vkBindBufferMemory2)load(context, "vkBindBufferMemory2");
	vkBindImageMemory2 = (PFN_vkBindImageMemory2)load(context, "vkBindImageMemory2");
	vkGetDeviceGroupPeerMemoryFeatures = (PFN_vkGetDeviceGroupPeerMemoryFeatures)load(context, "vkGetDeviceGroupPeerMemoryFeatures");
	vkCmdSetDeviceMask = (PFN_vkCmdSetDeviceMask)load(context, "vkCmdSetDeviceMask");
	vkCmdDispatchBase = (PFN_vkCmdDispatchBase)load(context, "vkCmdDispatchBase");
	vkGetImageMemoryRequirements2 = (PFN_vkGetImageMemoryRequirements2)load(context, "vkGetImageMemoryRequirements2");
	vkGetBufferMemoryRequirements2 = (PFN_vkGetBufferMemoryRequirements2)load(context, "vkGetBufferMemoryRequirements2");
	vkGetImageSparseMemoryRequirements2 = (PFN_vkGetImageSparseMemoryRequirements2)load(context, "vkGetImageSparseMemoryRequirements2");
	vkTrimCommandPool = (PFN_vkTrimCommandPool)load(context, "vkTrimCommandPool");
	vkGetDeviceQueue2 = (PFN_vkGetDeviceQueue2)load(context, "vkGetDeviceQueue2");
	vkCreateSamplerYcbcrConversion = (PFN_vkCreateSamplerYcbcrConversion)load(context, "vkCreateSamplerYcbcrConversion");
	vkDestroySamplerYcbcrConversion = (PFN_vkDestroySamplerYcbcrConversion)load(context, "vkDestroySamplerYcbcrConversion");
	vkCreateDescriptorUpdateTemplate = (PFN_vkCreateDescriptorUpdateTemplate)load(context, "vkCreateDescriptorUpdateTemplate");
	vkDestroyDescriptorUpdateTemplate = (PFN_vkDestroyDescriptorUpdateTemplate)load(context, "vkDestroyDescriptorUpdateTemplate");
	vkUpdateDescriptorSetWithTemplate = (PFN_vkUpdateDescriptorSetWithTemplate)load(context, "vkUpdateDescriptorSetWithTemplate");
	vkGetDescriptorSetLayoutSupport = (PFN_vkGetDescriptorSetLayoutSupport)load(context, "vkGetDescriptorSetLayoutSupport");
#endif // defined(VK_VERSION_1_1)
#if defined(VK_VERSION_1_2)
	vkCmdDrawIndirectCount = (PFN_vkCmdDrawIndirectCount)load(context, "vkCmdDrawIndirectCount");
	vkCmdDrawIndexedIndirectCount = (PFN_vkCmdDrawIndexedIndirectCount)load(context, "vkCmdDrawIndexedIndirectCount");
	vkCreateRenderPass2 = (PFN_vkCreateRenderPass2)load(context, "vkCreateRenderPass2");
	vkCmdBeginRenderPass2 = (PFN_vkCmdBeginRenderPass2)load(context, "vkCmdBeginRenderPass2");
	vkCmdNextSubpass2 = (PFN_vkCmdNextSubpass2)load(context, "vkCmdNextSubpass2");
	vkCmdEndRenderPass2 = (PFN_vkCmdEndRenderPass2)load(context, "vkCmdEndRenderPass2");
	vkResetQueryPool = (PFN_vkResetQueryPool)load(context, "vkResetQueryPool");
	vkGetSemaphoreCounterValue = (PFN_vkGetSemaphoreCounterValue)load(context, "vkGetSemaphoreCounterValue");
	vkWaitSemaphores = (PFN_vkWaitSemaphores)load(context, "vkWaitSemaphores");
	vkSignalSemaphore = (PFN_vkSignalSemaphore)load(context, "vkSignalSemaphore");
	vkGetBufferDeviceAddress = (PFN_vkGetBufferDeviceAddress)load(context, "vkGetBufferDeviceAddress");
	vkGetBufferOpaqueCaptureAddress = (PFN_vkGetBufferOpaqueCaptureAddress)load(context, "vkGetBufferOpaqueCaptureAddress");
	vkGetDeviceMemoryOpaqueCaptureAddress = (PFN_vkGetDeviceMemoryOpaqueCaptureAddress)load(context, "vkGetDeviceMemoryOpaqueCaptureAddress");
#endif // defined(VK_VERSION_1_2)
#if defined(VK_VERSION_1_3)
	vkCreatePrivateDataSlot = (PFN_vkCreatePrivateDataSlot)load(context, "vkCreatePrivateDataSlot");
	vkDestroyPrivateDataSlot = (PFN_vkDestroyPrivateDataSlot)load(context, "vkDestroyPrivateDataSlot");
	vkSetPrivateData = (PFN_vkSetPrivateData)load(context, "vkSetPrivateData");
	vkGetPrivateData = (PFN_vkGetPrivateData)load(context, "vkGetPrivateData");
	vkCmdSetEvent2 = (PFN_vkCmdSetEvent2)load(context, "vkCmdSetEvent2");
	vkCmdResetEvent2 = (PFN_vkCmdResetEvent2)load(context, "vkCmdResetEvent2");
	vkCmdWaitEvents2 = (PFN_vkCmdWaitEvents2)load(context, "vkCmdWaitEvents2");
	vkCmdPipelineBarrier2 = (PFN_vkCmdPipelineBarrier2)load(context, "vkCmdPipelineBarrier2");
	vkCmdWriteTimestamp2 = (PFN_vkCmdWriteTimestamp2)load(context, "vkCmdWriteTimestamp2");
	vkQueueSubmit2 = (PFN_vkQueueSubmit2)load(context, "vkQueueSubmit2");
	vkCmdCopyBuffer2 = (PFN_vkCmdCopyBuffer2)load(context, "vkCmdCopyBuffer2");
	vkCmdCopyImage2 = (PFN_vkCmdCopyImage2)load(context, "vkCmdCopyImage2");
	vkCmdCopyBufferToImage2 = (PFN_vkCmdCopyBufferToImage2)load(context, "vkCmdCopyBufferToImage2");
	vkCmdCopyImageToBuffer2 = (PFN_vkCmdCopyImageToBuffer2)load(context, "vkCmdCopyImageToBuffer2");
	vkCmdBlitImage2 = (PFN_vkCmdBlitImage2)load(context, "vkCmdBlitImage2");
	vkCmdResolveImage2 = (PFN_vkCmdResolveImage2)load(context, "vkCmdResolveImage2");
	vkCmdBeginRendering = (PFN_vkCmdBeginRendering)load(context, "vkCmdBeginRendering");
	vkCmdEndRendering = (PFN_vkCmdEndRendering)load(context, "vkCmdEndRendering");
	vkCmdSetCullMode = (PFN_vkCmdSetCullMode)load(context, "vkCmdSetCullMode");
	vkCmdSetFrontFace = (PFN_vkCmdSetFrontFace)load(context, "vkCmdSetFrontFace");
	vkCmdSetPrimitiveTopology = (PFN_vkCmdSetPrimitiveTopology)load(context, "vkCmdSetPrimitiveTopology");
	vkCmdSetViewportWithCount = (PFN_vkCmdSetViewportWithCount)load(context, "vkCmdSetViewportWithCount");
	vkCmdSetScissorWithCount = (PFN_vkCmdSetScissorWithCount)load(context, "vkCmdSetScissorWithCount");
	vkCmdBindVertexBuffers2 = (PFN_vkCmdBindVertexBuffers2)load(context, "vkCmdBindVertexBuffers2");
	vkCmdSetDepthTestEnable = (PFN_vkCmdSetDepthTestEnable)load(context, "vkCmdSetDepthTestEnable");
	vkCmdSetDepthWriteEnable = (PFN_vkCmdSetDepthWriteEnable)load(context, "vkCmdSetDepthWriteEnable");
	vkCmdSetDepthCompareOp = (PFN_vkCmdSetDepthCompareOp)load(context, "vkCmdSetDepthCompareOp");
	vkCmdSetDepthBoundsTestEnable = (PFN_vkCmdSetDepthBoundsTestEnable)load(context, "vkCmdSetDepthBoundsTestEnable");
	vkCmdSetStencilTestEnable = (PFN_vkCmdSetStencilTestEnable)load(context, "vkCmdSetStencilTestEnable");
	vkCmdSetStencilOp = (PFN_vkCmdSetStencilOp)load(context, "vkCmdSetStencilOp");
	vkCmdSetRasterizerDiscardEnable = (PFN_vkCmdSetRasterizerDiscardEnable)load(context, "vkCmdSetRasterizerDiscardEnable");
	vkCmdSetDepthBiasEnable = (PFN_vkCmdSetDepthBiasEnable)load(context, "vkCmdSetDepthBiasEnable");
	vkCmdSetPrimitiveRestartEnable = (PFN_vkCmdSetPrimitiveRestartEnable)load(context, "vkCmdSetPrimitiveRestartEnable");
	vkGetDeviceBufferMemoryRequirements = (PFN_vkGetDeviceBufferMemoryRequirements)load(context, "vkGetDeviceBufferMemoryRequirements");
	vkGetDeviceImageMemoryRequirements = (PFN_vkGetDeviceImageMemoryRequirements)load(context, "vkGetDeviceImageMemoryRequirements");
	vkGetDeviceImageSparseMemoryRequirements = (PFN_vkGetDeviceImageSparseMemoryRequirements)load(context, "vkGetDeviceImageSparseMemoryRequirements");
#endif // defined(VK_VERSION_1_3)
#if defined(VK_AMD_buffer_marker)
	vkCmdWriteBufferMarkerAMD = (PFN_vkCmdWriteBufferMarkerAMD)load(context, "vkCmdWriteBufferMarkerAMD");
#endif // defined(VK_AMD_buffer_marker)
#if defined(VK_AMD_display_native_hdr)
	vkSetLocalDimmingAMD = (PFN_vkSetLocalDimmingAMD)load(context, "vkSetLocalDimmingAMD");
#endif // defined(VK_AMD_display_native_hdr)
#if defined(VK_AMD_draw_indirect_count)
	vkCmdDrawIndirectCountAMD = (PFN_vkCmdDrawIndirectCountAMD)load(context, "vkCmdDrawIndirectCountAMD");
	vkCmdDrawIndexedIndirectCountAMD = (PFN_vkCmdDrawIndexedIndirectCountAMD)load(context, "vkCmdDrawIndexedIndirectCountAMD");
#endif // defined(VK_AMD_draw_indirect_count)
#if defined(VK_AMD_shader_info)
	vkGetShaderInfoAMD = (PFN_vkGetShaderInfoAMD)load(context, "vkGetShaderInfoAMD");
#endif // defined(VK_AMD_shader_info)
#if defined(VK_AMDX_shader_enqueue)
	vkCreateExecutionGraphPipelinesAMDX = (PFN_vkCreateExecutionGraphPipelinesAMDX)load(context, "vkCreateExecutionGraphPipelinesAMDX");
	vkGetExecutionGraphPipelineScratchSizeAMDX = (PFN_vkGetExecutionGraphPipelineScratchSizeAMDX)load(context, "vkGetExecutionGraphPipelineScratchSizeAMDX");
	vkGetExecutionGraphPipelineNodeIndexAMDX = (PFN_vkGetExecutionGraphPipelineNodeIndexAMDX)load(context, "vkGetExecutionGraphPipelineNodeIndexAMDX");
	vkCmdInitializeGraphScratchMemoryAMDX = (PFN_vkCmdInitializeGraphScratchMemoryAMDX)load(context, "vkCmdInitializeGraphScratchMemoryAMDX");
	vkCmdDispatchGraphAMDX = (PFN_vkCmdDispatchGraphAMDX)load(context, "vkCmdDispatchGraphAMDX");
	vkCmdDispatchGraphIndirectAMDX = (PFN_vkCmdDispatchGraphIndirectAMDX)load(context, "vkCmdDispatchGraphIndirectAMDX");
	vkCmdDispatchGraphIndirectCountAMDX = (PFN_vkCmdDispatchGraphIndirectCountAMDX)load(context, "vkCmdDispatchGraphIndirectCountAMDX");
#endif // defined(VK_AMDX_shader_enqueue)
#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
	vkGetAndroidHardwareBufferPropertiesANDROID = (PFN_vkGetAndroidHardwareBufferPropertiesANDROID)load(context, "vkGetAndroidHardwareBufferPropertiesANDROID");
	vkGetMemoryAndroidHardwareBufferANDROID = (PFN_vkGetMemoryAndroidHardwareBufferANDROID)load(context, "vkGetMemoryAndroidHardwareBufferANDROID");
#endif // defined(VK_ANDROID_external_memory_android_hardware_buffer)
#if defined(VK_EXT_attachment_feedback_loop_dynamic_state)
	vkCmdSetAttachmentFeedbackLoopEnableEXT = (PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT)load(context, "vkCmdSetAttachmentFeedbackLoopEnableEXT");
#endif // defined(VK_EXT_attachment_feedback_loop_dynamic_state)
#if defined(VK_EXT_buffer_device_address)
	vkGetBufferDeviceAddressEXT = (PFN_vkGetBufferDeviceAddressEXT)load(context, "vkGetBufferDeviceAddressEXT");
#endif // defined(VK_EXT_buffer_device_address)
#if defined(VK_EXT_calibrated_timestamps)
	vkGetCalibratedTimestampsEXT = (PFN_vkGetCalibratedTimestampsEXT)load(context, "vkGetCalibratedTimestampsEXT");
#endif // defined(VK_EXT_calibrated_timestamps)
#if defined(VK_EXT_color_write_enable)
	vkCmdSetColorWriteEnableEXT = (PFN_vkCmdSetColorWriteEnableEXT)load(context, "vkCmdSetColorWriteEnableEXT");
#endif // defined(VK_EXT_color_write_enable)
#if defined(VK_EXT_conditional_rendering)
	vkCmdBeginConditionalRenderingEXT = (PFN_vkCmdBeginConditionalRenderingEXT)load(context, "vkCmdBeginConditionalRenderingEXT");
	vkCmdEndConditionalRenderingEXT = (PFN_vkCmdEndConditionalRenderingEXT)load(context, "vkCmdEndConditionalRenderingEXT");
#endif // defined(VK_EXT_conditional_rendering)
#if defined(VK_EXT_debug_marker)
	vkDebugMarkerSetObjectTagEXT = (PFN_vkDebugMarkerSetObjectTagEXT)load(context, "vkDebugMarkerSetObjectTagEXT");
	vkDebugMarkerSetObjectNameEXT = (PFN_vkDebugMarkerSetObjectNameEXT)load(context, "vkDebugMarkerSetObjectNameEXT");
	vkCmdDebugMarkerBeginEXT = (PFN_vkCmdDebugMarkerBeginEXT)load(context, "vkCmdDebugMarkerBeginEXT");
	vkCmdDebugMarkerEndEXT = (PFN_vkCmdDebugMarkerEndEXT)load(context, "vkCmdDebugMarkerEndEXT");
	vkCmdDebugMarkerInsertEXT = (PFN_vkCmdDebugMarkerInsertEXT)load(context, "vkCmdDebugMarkerInsertEXT");
#endif // defined(VK_EXT_debug_marker)
#if defined(VK_EXT_depth_bias_control)
	vkCmdSetDepthBias2EXT = (PFN_vkCmdSetDepthBias2EXT)load(context, "vkCmdSetDepthBias2EXT");
#endif // defined(VK_EXT_depth_bias_control)
#if defined(VK_EXT_descriptor_buffer)
	vkGetDescriptorSetLayoutSizeEXT = (PFN_vkGetDescriptorSetLayoutSizeEXT)load(context, "vkGetDescriptorSetLayoutSizeEXT");
	vkGetDescriptorSetLayoutBindingOffsetEXT = (PFN_vkGetDescriptorSetLayoutBindingOffsetEXT)load(context, "vkGetDescriptorSetLayoutBindingOffsetEXT");
	vkGetDescriptorEXT = (PFN_vkGetDescriptorEXT)load(context, "vkGetDescriptorEXT");
	vkCmdBindDescriptorBuffersEXT = (PFN_vkCmdBindDescriptorBuffersEXT)load(context, "vkCmdBindDescriptorBuffersEXT");
	vkCmdSetDescriptorBufferOffsetsEXT = (PFN_vkCmdSetDescriptorBufferOffsetsEXT)load(context, "vkCmdSetDescriptorBufferOffsetsEXT");
	vkCmdBindDescriptorBufferEmbeddedSamplersEXT = (PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT)load(context, "vkCmdBindDescriptorBufferEmbeddedSamplersEXT");
	vkGetBufferOpaqueCaptureDescriptorDataEXT = (PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT)load(context, "vkGetBufferOpaqueCaptureDescriptorDataEXT");
	vkGetImageOpaqueCaptureDescriptorDataEXT = (PFN_vkGetImageOpaqueCaptureDescriptorDataEXT)load(context, "vkGetImageOpaqueCaptureDescriptorDataEXT");
	vkGetImageViewOpaqueCaptureDescriptorDataEXT = (PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT)load(context, "vkGetImageViewOpaqueCaptureDescriptorDataEXT");
	vkGetSamplerOpaqueCaptureDescriptorDataEXT = (PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT)load(context, "vkGetSamplerOpaqueCaptureDescriptorDataEXT");
#endif // defined(VK_EXT_descriptor_buffer)
#if defined(VK_EXT_descriptor_buffer) && (defined(VK_KHR_acceleration_structure) || defined(VK_NV_ray_tracing))
	vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT = (PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT)load(context, "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT");
#endif // defined(VK_EXT_descriptor_buffer) && (defined(VK_KHR_acceleration_structure) || defined(VK_NV_ray_tracing))
#if defined(VK_EXT_device_fault)
	vkGetDeviceFaultInfoEXT = (PFN_vkGetDeviceFaultInfoEXT)load(context, "vkGetDeviceFaultInfoEXT");
#endif // defined(VK_EXT_device_fault)
#if defined(VK_EXT_discard_rectangles)
	vkCmdSetDiscardRectangleEXT = (PFN_vkCmdSetDiscardRectangleEXT)load(context, "vkCmdSetDiscardRectangleEXT");
	vkCmdSetDiscardRectangleEnableEXT = (PFN_vkCmdSetDiscardRectangleEnableEXT)load(context, "vkCmdSetDiscardRectangleEnableEXT");
	vkCmdSetDiscardRectangleModeEXT = (PFN_vkCmdSetDiscardRectangleModeEXT)load(context, "vkCmdSetDiscardRectangleModeEXT");
#endif // defined(VK_EXT_discard_rectangles)
#if defined(VK_EXT_display_control)
	vkDisplayPowerControlEXT = (PFN_vkDisplayPowerControlEXT)load(context, "vkDisplayPowerControlEXT");
	vkRegisterDeviceEventEXT = (PFN_vkRegisterDeviceEventEXT)load(context, "vkRegisterDeviceEventEXT");
	vkRegisterDisplayEventEXT = (PFN_vkRegisterDisplayEventEXT)load(context, "vkRegisterDisplayEventEXT");
	vkGetSwapchainCounterEXT = (PFN_vkGetSwapchainCounterEXT)load(context, "vkGetSwapchainCounterEXT");
#endif // defined(VK_EXT_display_control)
#if defined(VK_EXT_external_memory_host)
	vkGetMemoryHostPointerPropertiesEXT = (PFN_vkGetMemoryHostPointerPropertiesEXT)load(context, "vkGetMemoryHostPointerPropertiesEXT");
#endif // defined(VK_EXT_external_memory_host)
#if defined(VK_EXT_full_screen_exclusive)
	vkAcquireFullScreenExclusiveModeEXT = (PFN_vkAcquireFullScreenExclusiveModeEXT)load(context, "vkAcquireFullScreenExclusiveModeEXT");
	vkReleaseFullScreenExclusiveModeEXT = (PFN_vkReleaseFullScreenExclusiveModeEXT)load(context, "vkReleaseFullScreenExclusiveModeEXT");
#endif // defined(VK_EXT_full_screen_exclusive)
#if defined(VK_EXT_hdr_metadata)
	vkSetHdrMetadataEXT = (PFN_vkSetHdrMetadataEXT)load(context, "vkSetHdrMetadataEXT");
#endif // defined(VK_EXT_hdr_metadata)
#if defined(VK_EXT_host_image_copy)
	vkCopyMemoryToImageEXT = (PFN_vkCopyMemoryToImageEXT)load(context, "vkCopyMemoryToImageEXT");
	vkCopyImageToMemoryEXT = (PFN_vkCopyImageToMemoryEXT)load(context, "vkCopyImageToMemoryEXT");
	vkCopyImageToImageEXT = (PFN_vkCopyImageToImageEXT)load(context, "vkCopyImageToImageEXT");
	vkTransitionImageLayoutEXT = (PFN_vkTransitionImageLayoutEXT)load(context, "vkTransitionImageLayoutEXT");
#endif // defined(VK_EXT_host_image_copy)
#if defined(VK_EXT_host_query_reset)
	vkResetQueryPoolEXT = (PFN_vkResetQueryPoolEXT)load(context, "vkResetQueryPoolEXT");
#endif // defined(VK_EXT_host_query_reset)
#if defined(VK_EXT_image_drm_format_modifier)
	vkGetImageDrmFormatModifierPropertiesEXT = (PFN_vkGetImageDrmFormatModifierPropertiesEXT)load(context, "vkGetImageDrmFormatModifierPropertiesEXT");
#endif // defined(VK_EXT_image_drm_format_modifier)
#if defined(VK_EXT_line_rasterization)
	vkCmdSetLineStippleEXT = (PFN_vkCmdSetLineStippleEXT)load(context, "vkCmdSetLineStippleEXT");
#endif // defined(VK_EXT_line_rasterization)
#if defined(VK_EXT_mesh_shader)
	vkCmdDrawMeshTasksEXT = (PFN_vkCmdDrawMeshTasksEXT)load(context, "vkCmdDrawMeshTasksEXT");
	vkCmdDrawMeshTasksIndirectEXT = (PFN_vkCmdDrawMeshTasksIndirectEXT)load(context, "vkCmdDrawMeshTasksIndirectEXT");
	vkCmdDrawMeshTasksIndirectCountEXT = (PFN_vkCmdDrawMeshTasksIndirectCountEXT)load(context, "vkCmdDrawMeshTasksIndirectCountEXT");
#endif // defined(VK_EXT_mesh_shader)
#if defined(VK_EXT_metal_objects)
	vkExportMetalObjectsEXT = (PFN_vkExportMetalObjectsEXT)load(context, "vkExportMetalObjectsEXT");
#endif // defined(VK_EXT_metal_objects)
#if defined(VK_EXT_multi_draw)
	vkCmdDrawMultiEXT = (PFN_vkCmdDrawMultiEXT)load(context, "vkCmdDrawMultiEXT");
	vkCmdDrawMultiIndexedEXT = (PFN_vkCmdDrawMultiIndexedEXT)load(context, "vkCmdDrawMultiIndexedEXT");
#endif // defined(VK_EXT_multi_draw)
#if defined(VK_EXT_opacity_micromap)
	vkCreateMicromapEXT = (PFN_vkCreateMicromapEXT)load(context, "vkCreateMicromapEXT");
	vkDestroyMicromapEXT = (PFN_vkDestroyMicromapEXT)load(context, "vkDestroyMicromapEXT");
	vkCmdBuildMicromapsEXT = (PFN_vkCmdBuildMicromapsEXT)load(context, "vkCmdBuildMicromapsEXT");
	vkBuildMicromapsEXT = (PFN_vkBuildMicromapsEXT)load(context, "vkBuildMicromapsEXT");
	vkCopyMicromapEXT = (PFN_vkCopyMicromapEXT)load(context, "vkCopyMicromapEXT");
	vkCopyMicromapToMemoryEXT = (PFN_vkCopyMicromapToMemoryEXT)load(context, "vkCopyMicromapToMemoryEXT");
	vkCopyMemoryToMicromapEXT = (PFN_vkCopyMemoryToMicromapEXT)load(context, "vkCopyMemoryToMicromapEXT");
	vkWriteMicromapsPropertiesEXT = (PFN_vkWriteMicromapsPropertiesEXT)load(context, "vkWriteMicromapsPropertiesEXT");
	vkCmdCopyMicromapEXT = (PFN_vkCmdCopyMicromapEXT)load(context, "vkCmdCopyMicromapEXT");
	vkCmdCopyMicromapToMemoryEXT = (PFN_vkCmdCopyMicromapToMemoryEXT)load(context, "vkCmdCopyMicromapToMemoryEXT");
	vkCmdCopyMemoryToMicromapEXT = (PFN_vkCmdCopyMemoryToMicromapEXT)load(context, "vkCmdCopyMemoryToMicromapEXT");
	vkCmdWriteMicromapsPropertiesEXT = (PFN_vkCmdWriteMicromapsPropertiesEXT)load(context, "vkCmdWriteMicromapsPropertiesEXT");
	vkGetDeviceMicromapCompatibilityEXT = (PFN_vkGetDeviceMicromapCompatibilityEXT)load(context, "vkGetDeviceMicromapCompatibilityEXT");
	vkGetMicromapBuildSizesEXT = (PFN_vkGetMicromapBuildSizesEXT)load(context, "vkGetMicromapBuildSizesEXT");
#endif // defined(VK_EXT_opacity_micromap)
#if defined(VK_EXT_pageable_device_local_memory)
	vkSetDeviceMemoryPriorityEXT = (PFN_vkSetDeviceMemoryPriorityEXT)load(context, "vkSetDeviceMemoryPriorityEXT");
#endif // defined(VK_EXT_pageable_device_local_memory)
#if defined(VK_EXT_pipeline_properties)
	vkGetPipelinePropertiesEXT = (PFN_vkGetPipelinePropertiesEXT)load(context, "vkGetPipelinePropertiesEXT");
#endif // defined(VK_EXT_pipeline_properties)
#if defined(VK_EXT_private_data)
	vkCreatePrivateDataSlotEXT = (PFN_vkCreatePrivateDataSlotEXT)load(context, "vkCreatePrivateDataSlotEXT");
	vkDestroyPrivateDataSlotEXT = (PFN_vkDestroyPrivateDataSlotEXT)load(context, "vkDestroyPrivateDataSlotEXT");
	vkSetPrivateDataEXT = (PFN_vkSetPrivateDataEXT)load(context, "vkSetPrivateDataEXT");
	vkGetPrivateDataEXT = (PFN_vkGetPrivateDataEXT)load(context, "vkGetPrivateDataEXT");
#endif // defined(VK_EXT_private_data)
#if defined(VK_EXT_sample_locations)
	vkCmdSetSampleLocationsEXT = (PFN_vkCmdSetSampleLocationsEXT)load(context, "vkCmdSetSampleLocationsEXT");
#endif // defined(VK_EXT_sample_locations)
#if defined(VK_EXT_shader_module_identifier)
	vkGetShaderModuleIdentifierEXT = (PFN_vkGetShaderModuleIdentifierEXT)load(context, "vkGetShaderModuleIdentifierEXT");
	vkGetShaderModuleCreateInfoIdentifierEXT = (PFN_vkGetShaderModuleCreateInfoIdentifierEXT)load(context, "vkGetShaderModuleCreateInfoIdentifierEXT");
#endif // defined(VK_EXT_shader_module_identifier)
#if defined(VK_EXT_shader_object)
	vkCreateShadersEXT = (PFN_vkCreateShadersEXT)load(context, "vkCreateShadersEXT");
	vkDestroyShaderEXT = (PFN_vkDestroyShaderEXT)load(context, "vkDestroyShaderEXT");
	vkGetShaderBinaryDataEXT = (PFN_vkGetShaderBinaryDataEXT)load(context, "vkGetShaderBinaryDataEXT");
	vkCmdBindShadersEXT = (PFN_vkCmdBindShadersEXT)load(context, "vkCmdBindShadersEXT");
#endif // defined(VK_EXT_shader_object)
#if defined(VK_EXT_swapchain_maintenance1)
	vkReleaseSwapchainImagesEXT = (PFN_vkReleaseSwapchainImagesEXT)load(context, "vkReleaseSwapchainImagesEXT");
#endif // defined(VK_EXT_swapchain_maintenance1)
#if defined(VK_EXT_transform_feedback)
	vkCmdBindTransformFeedbackBuffersEXT = (PFN_vkCmdBindTransformFeedbackBuffersEXT)load(context, "vkCmdBindTransformFeedbackBuffersEXT");
	vkCmdBeginTransformFeedbackEXT = (PFN_vkCmdBeginTransformFeedbackEXT)load(context, "vkCmdBeginTransformFeedbackEXT");
	vkCmdEndTransformFeedbackEXT = (PFN_vkCmdEndTransformFeedbackEXT)load(context, "vkCmdEndTransformFeedbackEXT");
	vkCmdBeginQueryIndexedEXT = (PFN_vkCmdBeginQueryIndexedEXT)load(context, "vkCmdBeginQueryIndexedEXT");
	vkCmdEndQueryIndexedEXT = (PFN_vkCmdEndQueryIndexedEXT)load(context, "vkCmdEndQueryIndexedEXT");
	vkCmdDrawIndirectByteCountEXT = (PFN_vkCmdDrawIndirectByteCountEXT)load(context, "vkCmdDrawIndirectByteCountEXT");
#endif // defined(VK_EXT_transform_feedback)
#if defined(VK_EXT_validation_cache)
	vkCreateValidationCacheEXT = (PFN_vkCreateValidationCacheEXT)load(context, "vkCreateValidationCacheEXT");
	vkDestroyValidationCacheEXT = (PFN_vkDestroyValidationCacheEXT)load(context, "vkDestroyValidationCacheEXT");
	vkMergeValidationCachesEXT = (PFN_vkMergeValidationCachesEXT)load(context, "vkMergeValidationCachesEXT");
	vkGetValidationCacheDataEXT = (PFN_vkGetValidationCacheDataEXT)load(context, "vkGetValidationCacheDataEXT");
#endif // defined(VK_EXT_validation_cache)
#if defined(VK_FUCHSIA_buffer_collection)
	vkCreateBufferCollectionFUCHSIA = (PFN_vkCreateBufferCollectionFUCHSIA)load(context, "vkCreateBufferCollectionFUCHSIA");
	vkSetBufferCollectionImageConstraintsFUCHSIA = (PFN_vkSetBufferCollectionImageConstraintsFUCHSIA)load(context, "vkSetBufferCollectionImageConstraintsFUCHSIA");
	vkSetBufferCollectionBufferConstraintsFUCHSIA = (PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA)load(context, "vkSetBufferCollectionBufferConstraintsFUCHSIA");
	vkDestroyBufferCollectionFUCHSIA = (PFN_vkDestroyBufferCollectionFUCHSIA)load(context, "vkDestroyBufferCollectionFUCHSIA");
	vkGetBufferCollectionPropertiesFUCHSIA = (PFN_vkGetBufferCollectionPropertiesFUCHSIA)load(context, "vkGetBufferCollectionPropertiesFUCHSIA");
#endif // defined(VK_FUCHSIA_buffer_collection)
#if defined(VK_FUCHSIA_external_memory)
	vkGetMemoryZirconHandleFUCHSIA = (PFN_vkGetMemoryZirconHandleFUCHSIA)load(context, "vkGetMemoryZirconHandleFUCHSIA");
	vkGetMemoryZirconHandlePropertiesFUCHSIA = (PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA)load(context, "vkGetMemoryZirconHandlePropertiesFUCHSIA");
#endif // defined(VK_FUCHSIA_external_memory)
#if defined(VK_FUCHSIA_external_semaphore)
	vkImportSemaphoreZirconHandleFUCHSIA = (PFN_vkImportSemaphoreZirconHandleFUCHSIA)load(context, "vkImportSemaphoreZirconHandleFUCHSIA");
	vkGetSemaphoreZirconHandleFUCHSIA = (PFN_vkGetSemaphoreZirconHandleFUCHSIA)load(context, "vkGetSemaphoreZirconHandleFUCHSIA");
#endif // defined(VK_FUCHSIA_external_semaphore)
#if defined(VK_GOOGLE_display_timing)
	vkGetRefreshCycleDurationGOOGLE = (PFN_vkGetRefreshCycleDurationGOOGLE)load(context, "vkGetRefreshCycleDurationGOOGLE");
	vkGetPastPresentationTimingGOOGLE = (PFN_vkGetPastPresentationTimingGOOGLE)load(context, "vkGetPastPresentationTimingGOOGLE");
#endif // defined(VK_GOOGLE_display_timing)
#if defined(VK_HUAWEI_cluster_culling_shader)
	vkCmdDrawClusterHUAWEI = (PFN_vkCmdDrawClusterHUAWEI)load(context, "vkCmdDrawClusterHUAWEI");
	vkCmdDrawClusterIndirectHUAWEI = (PFN_vkCmdDrawClusterIndirectHUAWEI)load(context, "vkCmdDrawClusterIndirectHUAWEI");
#endif // defined(VK_HUAWEI_cluster_culling_shader)
#if defined(VK_HUAWEI_invocation_mask)
	vkCmdBindInvocationMaskHUAWEI = (PFN_vkCmdBindInvocationMaskHUAWEI)load(context, "vkCmdBindInvocationMaskHUAWEI");
#endif // defined(VK_HUAWEI_invocation_mask)
#if defined(VK_HUAWEI_subpass_shading)
	vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI = (PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI)load(context, "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI");
	vkCmdSubpassShadingHUAWEI = (PFN_vkCmdSubpassShadingHUAWEI)load(context, "vkCmdSubpassShadingHUAWEI");
#endif // defined(VK_HUAWEI_subpass_shading)
#if defined(VK_INTEL_performance_query)
	vkInitializePerformanceApiINTEL = (PFN_vkInitializePerformanceApiINTEL)load(context, "vkInitializePerformanceApiINTEL");
	vkUninitializePerformanceApiINTEL = (PFN_vkUninitializePerformanceApiINTEL)load(context, "vkUninitializePerformanceApiINTEL");
	vkCmdSetPerformanceMarkerINTEL = (PFN_vkCmdSetPerformanceMarkerINTEL)load(context, "vkCmdSetPerformanceMarkerINTEL");
	vkCmdSetPerformanceStreamMarkerINTEL = (PFN_vkCmdSetPerformanceStreamMarkerINTEL)load(context, "vkCmdSetPerformanceStreamMarkerINTEL");
	vkCmdSetPerformanceOverrideINTEL = (PFN_vkCmdSetPerformanceOverrideINTEL)load(context, "vkCmdSetPerformanceOverrideINTEL");
	vkAcquirePerformanceConfigurationINTEL = (PFN_vkAcquirePerformanceConfigurationINTEL)load(context, "vkAcquirePerformanceConfigurationINTEL");
	vkReleasePerformanceConfigurationINTEL = (PFN_vkReleasePerformanceConfigurationINTEL)load(context, "vkReleasePerformanceConfigurationINTEL");
	vkQueueSetPerformanceConfigurationINTEL = (PFN_vkQueueSetPerformanceConfigurationINTEL)load(context, "vkQueueSetPerformanceConfigurationINTEL");
	vkGetPerformanceParameterINTEL = (PFN_vkGetPerformanceParameterINTEL)load(context, "vkGetPerformanceParameterINTEL");
#endif // defined(VK_INTEL_performance_query)
#if defined(VK_KHR_acceleration_structure)
	vkCreateAccelerationStructureKHR = (PFN_vkCreateAccelerationStructureKHR)load(context, "vkCreateAccelerationStructureKHR");
	vkDestroyAccelerationStructureKHR = (PFN_vkDestroyAccelerationStructureKHR)load(context, "vkDestroyAccelerationStructureKHR");
	vkCmdBuildAccelerationStructuresKHR = (PFN_vkCmdBuildAccelerationStructuresKHR)load(context, "vkCmdBuildAccelerationStructuresKHR");
	vkCmdBuildAccelerationStructuresIndirectKHR = (PFN_vkCmdBuildAccelerationStructuresIndirectKHR)load(context, "vkCmdBuildAccelerationStructuresIndirectKHR");
	vkBuildAccelerationStructuresKHR = (PFN_vkBuildAccelerationStructuresKHR)load(context, "vkBuildAccelerationStructuresKHR");
	vkCopyAccelerationStructureKHR = (PFN_vkCopyAccelerationStructureKHR)load(context, "vkCopyAccelerationStructureKHR");
	vkCopyAccelerationStructureToMemoryKHR = (PFN_vkCopyAccelerationStructureToMemoryKHR)load(context, "vkCopyAccelerationStructureToMemoryKHR");
	vkCopyMemoryToAccelerationStructureKHR = (PFN_vkCopyMemoryToAccelerationStructureKHR)load(context, "vkCopyMemoryToAccelerationStructureKHR");
	vkWriteAccelerationStructuresPropertiesKHR = (PFN_vkWriteAccelerationStructuresPropertiesKHR)load(context, "vkWriteAccelerationStructuresPropertiesKHR");
	vkCmdCopyAccelerationStructureKHR = (PFN_vkCmdCopyAccelerationStructureKHR)load(context, "vkCmdCopyAccelerationStructureKHR");
	vkCmdCopyAccelerationStructureToMemoryKHR = (PFN_vkCmdCopyAccelerationStructureToMemoryKHR)load(context, "vkCmdCopyAccelerationStructureToMemoryKHR");
	vkCmdCopyMemoryToAccelerationStructureKHR = (PFN_vkCmdCopyMemoryToAccelerationStructureKHR)load(context, "vkCmdCopyMemoryToAccelerationStructureKHR");
	vkGetAccelerationStructureDeviceAddressKHR = (PFN_vkGetAccelerationStructureDeviceAddressKHR)load(context, "vkGetAccelerationStructureDeviceAddressKHR");
	vkCmdWriteAccelerationStructuresPropertiesKHR = (PFN_vkCmdWriteAccelerationStructuresPropertiesKHR)load(context, "vkCmdWriteAccelerationStructuresPropertiesKHR");
	vkGetDeviceAccelerationStructureCompatibilityKHR = (PFN_vkGetDeviceAccelerationStructureCompatibilityKHR)load(context, "vkGetDeviceAccelerationStructureCompatibilityKHR");
	vkGetAccelerationStructureBuildSizesKHR = (PFN_vkGetAccelerationStructureBuildSizesKHR)load(context, "vkGetAccelerationStructureBuildSizesKHR");
#endif // defined(VK_KHR_acceleration_structure)
#if defined(VK_KHR_bind_memory2)
	vkBindBufferMemory2KHR = (PFN_vkBindBufferMemory2KHR)load(context, "vkBindBufferMemory2KHR");
	vkBindImageMemory2KHR = (PFN_vkBindImageMemory2KHR)load(context, "vkBindImageMemory2KHR");
#endif // defined(VK_KHR_bind_memory2)
#if defined(VK_KHR_buffer_device_address)
	vkGetBufferDeviceAddressKHR = (PFN_vkGetBufferDeviceAddressKHR)load(context, "vkGetBufferDeviceAddressKHR");
	vkGetBufferOpaqueCaptureAddressKHR = (PFN_vkGetBufferOpaqueCaptureAddressKHR)load(context, "vkGetBufferOpaqueCaptureAddressKHR");
	vkGetDeviceMemoryOpaqueCaptureAddressKHR = (PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR)load(context, "vkGetDeviceMemoryOpaqueCaptureAddressKHR");
#endif // defined(VK_KHR_buffer_device_address)
#if defined(VK_KHR_calibrated_timestamps)
	vkGetCalibratedTimestampsKHR = (PFN_vkGetCalibratedTimestampsKHR)load(context, "vkGetCalibratedTimestampsKHR");
#endif // defined(VK_KHR_calibrated_timestamps)
#if defined(VK_KHR_copy_commands2)
	vkCmdCopyBuffer2KHR = (PFN_vkCmdCopyBuffer2KHR)load(context, "vkCmdCopyBuffer2KHR");
	vkCmdCopyImage2KHR = (PFN_vkCmdCopyImage2KHR)load(context, "vkCmdCopyImage2KHR");
	vkCmdCopyBufferToImage2KHR = (PFN_vkCmdCopyBufferToImage2KHR)load(context, "vkCmdCopyBufferToImage2KHR");
	vkCmdCopyImageToBuffer2KHR = (PFN_vkCmdCopyImageToBuffer2KHR)load(context, "vkCmdCopyImageToBuffer2KHR");
	vkCmdBlitImage2KHR = (PFN_vkCmdBlitImage2KHR)load(context, "vkCmdBlitImage2KHR");
	vkCmdResolveImage2KHR = (PFN_vkCmdResolveImage2KHR)load(context, "vkCmdResolveImage2KHR");
#endif // defined(VK_KHR_copy_commands2)
#if defined(VK_KHR_create_renderpass2)
	vkCreateRenderPass2KHR = (PFN_vkCreateRenderPass2KHR)load(context, "vkCreateRenderPass2KHR");
	vkCmdBeginRenderPass2KHR = (PFN_vkCmdBeginRenderPass2KHR)load(context, "vkCmdBeginRenderPass2KHR");
	vkCmdNextSubpass2KHR = (PFN_vkCmdNextSubpass2KHR)load(context, "vkCmdNextSubpass2KHR");
	vkCmdEndRenderPass2KHR = (PFN_vkCmdEndRenderPass2KHR)load(context, "vkCmdEndRenderPass2KHR");
#endif // defined(VK_KHR_create_renderpass2)
#if defined(VK_KHR_deferred_host_operations)
	vkCreateDeferredOperationKHR = (PFN_vkCreateDeferredOperationKHR)load(context, "vkCreateDeferredOperationKHR");
	vkDestroyDeferredOperationKHR = (PFN_vkDestroyDeferredOperationKHR)load(context, "vkDestroyDeferredOperationKHR");
	vkGetDeferredOperationMaxConcurrencyKHR = (PFN_vkGetDeferredOperationMaxConcurrencyKHR)load(context, "vkGetDeferredOperationMaxConcurrencyKHR");
	vkGetDeferredOperationResultKHR = (PFN_vkGetDeferredOperationResultKHR)load(context, "vkGetDeferredOperationResultKHR");
	vkDeferredOperationJoinKHR = (PFN_vkDeferredOperationJoinKHR)load(context, "vkDeferredOperationJoinKHR");
#endif // defined(VK_KHR_deferred_host_operations)
#if defined(VK_KHR_descriptor_update_template)
	vkCreateDescriptorUpdateTemplateKHR = (PFN_vkCreateDescriptorUpdateTemplateKHR)load(context, "vkCreateDescriptorUpdateTemplateKHR");
	vkDestroyDescriptorUpdateTemplateKHR = (PFN_vkDestroyDescriptorUpdateTemplateKHR)load(context, "vkDestroyDescriptorUpdateTemplateKHR");
	vkUpdateDescriptorSetWithTemplateKHR = (PFN_vkUpdateDescriptorSetWithTemplateKHR)load(context, "vkUpdateDescriptorSetWithTemplateKHR");
#endif // defined(VK_KHR_descriptor_update_template)
#if defined(VK_KHR_device_group)
	vkGetDeviceGroupPeerMemoryFeaturesKHR = (PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR)load(context, "vkGetDeviceGroupPeerMemoryFeaturesKHR");
	vkCmdSetDeviceMaskKHR = (PFN_vkCmdSetDeviceMaskKHR)load(context, "vkCmdSetDeviceMaskKHR");
	vkCmdDispatchBaseKHR = (PFN_vkCmdDispatchBaseKHR)load(context, "vkCmdDispatchBaseKHR");
#endif // defined(VK_KHR_device_group)
#if defined(VK_KHR_display_swapchain)
	vkCreateSharedSwapchainsKHR = (PFN_vkCreateSharedSwapchainsKHR)load(context, "vkCreateSharedSwapchainsKHR");
#endif // defined(VK_KHR_display_swapchain)
#if defined(VK_KHR_draw_indirect_count)
	vkCmdDrawIndirectCountKHR = (PFN_vkCmdDrawIndirectCountKHR)load(context, "vkCmdDrawIndirectCountKHR");
	vkCmdDrawIndexedIndirectCountKHR = (PFN_vkCmdDrawIndexedIndirectCountKHR)load(context, "vkCmdDrawIndexedIndirectCountKHR");
#endif // defined(VK_KHR_draw_indirect_count)
#if defined(VK_KHR_dynamic_rendering)
	vkCmdBeginRenderingKHR = (PFN_vkCmdBeginRenderingKHR)load(context, "vkCmdBeginRenderingKHR");
	vkCmdEndRenderingKHR = (PFN_vkCmdEndRenderingKHR)load(context, "vkCmdEndRenderingKHR");
#endif // defined(VK_KHR_dynamic_rendering)
#if defined(VK_KHR_dynamic_rendering_local_read)
	vkCmdSetRenderingAttachmentLocationsKHR = (PFN_vkCmdSetRenderingAttachmentLocationsKHR)load(context, "vkCmdSetRenderingAttachmentLocationsKHR");
	vkCmdSetRenderingInputAttachmentIndicesKHR = (PFN_vkCmdSetRenderingInputAttachmentIndicesKHR)load(context, "vkCmdSetRenderingInputAttachmentIndicesKHR");
#endif // defined(VK_KHR_dynamic_rendering_local_read)
#if defined(VK_KHR_external_fence_fd)
	vkImportFenceFdKHR = (PFN_vkImportFenceFdKHR)load(context, "vkImportFenceFdKHR");
	vkGetFenceFdKHR = (PFN_vkGetFenceFdKHR)load(context, "vkGetFenceFdKHR");
#endif // defined(VK_KHR_external_fence_fd)
#if defined(VK_KHR_external_fence_win32)
	vkImportFenceWin32HandleKHR = (PFN_vkImportFenceWin32HandleKHR)load(context, "vkImportFenceWin32HandleKHR");
	vkGetFenceWin32HandleKHR = (PFN_vkGetFenceWin32HandleKHR)load(context, "vkGetFenceWin32HandleKHR");
#endif // defined(VK_KHR_external_fence_win32)
#if defined(VK_KHR_external_memory_fd)
	vkGetMemoryFdKHR = (PFN_vkGetMemoryFdKHR)load(context, "vkGetMemoryFdKHR");
	vkGetMemoryFdPropertiesKHR = (PFN_vkGetMemoryFdPropertiesKHR)load(context, "vkGetMemoryFdPropertiesKHR");
#endif // defined(VK_KHR_external_memory_fd)
#if defined(VK_KHR_external_memory_win32)
	vkGetMemoryWin32HandleKHR = (PFN_vkGetMemoryWin32HandleKHR)load(context, "vkGetMemoryWin32HandleKHR");
	vkGetMemoryWin32HandlePropertiesKHR = (PFN_vkGetMemoryWin32HandlePropertiesKHR)load(context, "vkGetMemoryWin32HandlePropertiesKHR");
#endif // defined(VK_KHR_external_memory_win32)
#if defined(VK_KHR_external_semaphore_fd)
	vkImportSemaphoreFdKHR = (PFN_vkImportSemaphoreFdKHR)load(context, "vkImportSemaphoreFdKHR");
	vkGetSemaphoreFdKHR = (PFN_vkGetSemaphoreFdKHR)load(context, "vkGetSemaphoreFdKHR");
#endif // defined(VK_KHR_external_semaphore_fd)
#if defined(VK_KHR_external_semaphore_win32)
	vkImportSemaphoreWin32HandleKHR = (PFN_vkImportSemaphoreWin32HandleKHR)load(context, "vkImportSemaphoreWin32HandleKHR");
	vkGetSemaphoreWin32HandleKHR = (PFN_vkGetSemaphoreWin32HandleKHR)load(context, "vkGetSemaphoreWin32HandleKHR");
#endif // defined(VK_KHR_external_semaphore_win32)
#if defined(VK_KHR_fragment_shading_rate)
	vkCmdSetFragmentShadingRateKHR = (PFN_vkCmdSetFragmentShadingRateKHR)load(context, "vkCmdSetFragmentShadingRateKHR");
#endif // defined(VK_KHR_fragment_shading_rate)
#if defined(VK_KHR_get_memory_requirements2)
	vkGetImageMemoryRequirements2KHR = (PFN_vkGetImageMemoryRequirements2KHR)load(context, "vkGetImageMemoryRequirements2KHR");
	vkGetBufferMemoryRequirements2KHR = (PFN_vkGetBufferMemoryRequirements2KHR)load(context, "vkGetBufferMemoryRequirements2KHR");
	vkGetImageSparseMemoryRequirements2KHR = (PFN_vkGetImageSparseMemoryRequirements2KHR)load(context, "vkGetImageSparseMemoryRequirements2KHR");
#endif // defined(VK_KHR_get_memory_requirements2)
#if defined(VK_KHR_line_rasterization)
	vkCmdSetLineStippleKHR = (PFN_vkCmdSetLineStippleKHR)load(context, "vkCmdSetLineStippleKHR");
#endif // defined(VK_KHR_line_rasterization)
#if defined(VK_KHR_maintenance1)
	vkTrimCommandPoolKHR = (PFN_vkTrimCommandPoolKHR)load(context, "vkTrimCommandPoolKHR");
#endif // defined(VK_KHR_maintenance1)
#if defined(VK_KHR_maintenance3)
	vkGetDescriptorSetLayoutSupportKHR = (PFN_vkGetDescriptorSetLayoutSupportKHR)load(context, "vkGetDescriptorSetLayoutSupportKHR");
#endif // defined(VK_KHR_maintenance3)
#if defined(VK_KHR_maintenance4)
	vkGetDeviceBufferMemoryRequirementsKHR = (PFN_vkGetDeviceBufferMemoryRequirementsKHR)load(context, "vkGetDeviceBufferMemoryRequirementsKHR");
	vkGetDeviceImageMemoryRequirementsKHR = (PFN_vkGetDeviceImageMemoryRequirementsKHR)load(context, "vkGetDeviceImageMemoryRequirementsKHR");
	vkGetDeviceImageSparseMemoryRequirementsKHR = (PFN_vkGetDeviceImageSparseMemoryRequirementsKHR)load(context, "vkGetDeviceImageSparseMemoryRequirementsKHR");
#endif // defined(VK_KHR_maintenance4)
#if defined(VK_KHR_maintenance5)
	vkCmdBindIndexBuffer2KHR = (PFN_vkCmdBindIndexBuffer2KHR)load(context, "vkCmdBindIndexBuffer2KHR");
	vkGetRenderingAreaGranularityKHR = (PFN_vkGetRenderingAreaGranularityKHR)load(context, "vkGetRenderingAreaGranularityKHR");
	vkGetDeviceImageSubresourceLayoutKHR = (PFN_vkGetDeviceImageSubresourceLayoutKHR)load(context, "vkGetDeviceImageSubresourceLayoutKHR");
	vkGetImageSubresourceLayout2KHR = (PFN_vkGetImageSubresourceLayout2KHR)load(context, "vkGetImageSubresourceLayout2KHR");
#endif // defined(VK_KHR_maintenance5)
#if defined(VK_KHR_maintenance6)
	vkCmdBindDescriptorSets2KHR = (PFN_vkCmdBindDescriptorSets2KHR)load(context, "vkCmdBindDescriptorSets2KHR");
	vkCmdPushConstants2KHR = (PFN_vkCmdPushConstants2KHR)load(context, "vkCmdPushConstants2KHR");
#endif // defined(VK_KHR_maintenance6)
#if defined(VK_KHR_maintenance6) && defined(VK_KHR_push_descriptor)
	vkCmdPushDescriptorSet2KHR = (PFN_vkCmdPushDescriptorSet2KHR)load(context, "vkCmdPushDescriptorSet2KHR");
	vkCmdPushDescriptorSetWithTemplate2KHR = (PFN_vkCmdPushDescriptorSetWithTemplate2KHR)load(context, "vkCmdPushDescriptorSetWithTemplate2KHR");
#endif // defined(VK_KHR_maintenance6) && defined(VK_KHR_push_descriptor)
#if defined(VK_KHR_maintenance6) && defined(VK_EXT_descriptor_buffer)
	vkCmdSetDescriptorBufferOffsets2EXT = (PFN_vkCmdSetDescriptorBufferOffsets2EXT)load(context, "vkCmdSetDescriptorBufferOffsets2EXT");
	vkCmdBindDescriptorBufferEmbeddedSamplers2EXT = (PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT)load(context, "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT");
#endif // defined(VK_KHR_maintenance6) && defined(VK_EXT_descriptor_buffer)
#if defined(VK_KHR_map_memory2)
	vkMapMemory2KHR = (PFN_vkMapMemory2KHR)load(context, "vkMapMemory2KHR");
	vkUnmapMemory2KHR = (PFN_vkUnmapMemory2KHR)load(context, "vkUnmapMemory2KHR");
#endif // defined(VK_KHR_map_memory2)
#if defined(VK_KHR_performance_query)
	vkAcquireProfilingLockKHR = (PFN_vkAcquireProfilingLockKHR)load(context, "vkAcquireProfilingLockKHR");
	vkReleaseProfilingLockKHR = (PFN_vkReleaseProfilingLockKHR)load(context, "vkReleaseProfilingLockKHR");
#endif // defined(VK_KHR_performance_query)
#if defined(VK_KHR_pipeline_executable_properties)
	vkGetPipelineExecutablePropertiesKHR = (PFN_vkGetPipelineExecutablePropertiesKHR)load(context, "vkGetPipelineExecutablePropertiesKHR");
	vkGetPipelineExecutableStatisticsKHR = (PFN_vkGetPipelineExecutableStatisticsKHR)load(context, "vkGetPipelineExecutableStatisticsKHR");
	vkGetPipelineExecutableInternalRepresentationsKHR = (PFN_vkGetPipelineExecutableInternalRepresentationsKHR)load(context, "vkGetPipelineExecutableInternalRepresentationsKHR");
#endif // defined(VK_KHR_pipeline_executable_properties)
#if defined(VK_KHR_present_wait)
	vkWaitForPresentKHR = (PFN_vkWaitForPresentKHR)load(context, "vkWaitForPresentKHR");
#endif // defined(VK_KHR_present_wait)
#if defined(VK_KHR_push_descriptor)
	vkCmdPushDescriptorSetKHR = (PFN_vkCmdPushDescriptorSetKHR)load(context, "vkCmdPushDescriptorSetKHR");
#endif // defined(VK_KHR_push_descriptor)
#if defined(VK_KHR_ray_tracing_maintenance1) && defined(VK_KHR_ray_tracing_pipeline)
	vkCmdTraceRaysIndirect2KHR = (PFN_vkCmdTraceRaysIndirect2KHR)load(context, "vkCmdTraceRaysIndirect2KHR");
#endif // defined(VK_KHR_ray_tracing_maintenance1) && defined(VK_KHR_ray_tracing_pipeline)
#if defined(VK_KHR_ray_tracing_pipeline)
	vkCmdTraceRaysKHR = (PFN_vkCmdTraceRaysKHR)load(context, "vkCmdTraceRaysKHR");
	vkCreateRayTracingPipelinesKHR = (PFN_vkCreateRayTracingPipelinesKHR)load(context, "vkCreateRayTracingPipelinesKHR");
	vkGetRayTracingShaderGroupHandlesKHR = (PFN_vkGetRayTracingShaderGroupHandlesKHR)load(context, "vkGetRayTracingShaderGroupHandlesKHR");
	vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = (PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR)load(context, "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR");
	vkCmdTraceRaysIndirectKHR = (PFN_vkCmdTraceRaysIndirectKHR)load(context, "vkCmdTraceRaysIndirectKHR");
	vkGetRayTracingShaderGroupStackSizeKHR = (PFN_vkGetRayTracingShaderGroupStackSizeKHR)load(context, "vkGetRayTracingShaderGroupStackSizeKHR");
	vkCmdSetRayTracingPipelineStackSizeKHR = (PFN_vkCmdSetRayTracingPipelineStackSizeKHR)load(context, "vkCmdSetRayTracingPipelineStackSizeKHR");
#endif // defined(VK_KHR_ray_tracing_pipeline)
#if defined(VK_KHR_sampler_ycbcr_conversion)
	vkCreateSamplerYcbcrConversionKHR = (PFN_vkCreateSamplerYcbcrConversionKHR)load(context, "vkCreateSamplerYcbcrConversionKHR");
	vkDestroySamplerYcbcrConversionKHR = (PFN_vkDestroySamplerYcbcrConversionKHR)load(context, "vkDestroySamplerYcbcrConversionKHR");
#endif // defined(VK_KHR_sampler_ycbcr_conversion)
#if defined(VK_KHR_shared_presentable_image)
	vkGetSwapchainStatusKHR = (PFN_vkGetSwapchainStatusKHR)load(context, "vkGetSwapchainStatusKHR");
#endif // defined(VK_KHR_shared_presentable_image)
#if defined(VK_KHR_swapchain)
	vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR)load(context, "vkCreateSwapchainKHR");
	vkDestroySwapchainKHR = (PFN_vkDestroySwapchainKHR)load(context, "vkDestroySwapchainKHR");
	vkGetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR)load(context, "vkGetSwapchainImagesKHR");
	vkAcquireNextImageKHR = (PFN_vkAcquireNextImageKHR)load(context, "vkAcquireNextImageKHR");
	vkQueuePresentKHR = (PFN_vkQueuePresentKHR)load(context, "vkQueuePresentKHR");
#endif // defined(VK_KHR_swapchain)
#if defined(VK_KHR_synchronization2)
	vkCmdSetEvent2KHR = (PFN_vkCmdSetEvent2KHR)load(context, "vkCmdSetEvent2KHR");
	vkCmdResetEvent2KHR = (PFN_vkCmdResetEvent2KHR)load(context, "vkCmdResetEvent2KHR");
	vkCmdWaitEvents2KHR = (PFN_vkCmdWaitEvents2KHR)load(context, "vkCmdWaitEvents2KHR");
	vkCmdPipelineBarrier2KHR = (PFN_vkCmdPipelineBarrier2KHR)load(context, "vkCmdPipelineBarrier2KHR");
	vkCmdWriteTimestamp2KHR = (PFN_vkCmdWriteTimestamp2KHR)load(context, "vkCmdWriteTimestamp2KHR");
	vkQueueSubmit2KHR = (PFN_vkQueueSubmit2KHR)load(context, "vkQueueSubmit2KHR");
#endif // defined(VK_KHR_synchronization2)
#if defined(VK_KHR_synchronization2) && defined(VK_AMD_buffer_marker)
	vkCmdWriteBufferMarker2AMD = (PFN_vkCmdWriteBufferMarker2AMD)load(context, "vkCmdWriteBufferMarker2AMD");
#endif // defined(VK_KHR_synchronization2) && defined(VK_AMD_buffer_marker)
#if defined(VK_KHR_synchronization2) && defined(VK_NV_device_diagnostic_checkpoints)
	vkGetQueueCheckpointData2NV = (PFN_vkGetQueueCheckpointData2NV)load(context, "vkGetQueueCheckpointData2NV");
#endif // defined(VK_KHR_synchronization2) && defined(VK_NV_device_diagnostic_checkpoints)
#if defined(VK_KHR_timeline_semaphore)
	vkGetSemaphoreCounterValueKHR = (PFN_vkGetSemaphoreCounterValueKHR)load(context, "vkGetSemaphoreCounterValueKHR");
	vkWaitSemaphoresKHR = (PFN_vkWaitSemaphoresKHR)load(context, "vkWaitSemaphoresKHR");
	vkSignalSemaphoreKHR = (PFN_vkSignalSemaphoreKHR)load(context, "vkSignalSemaphoreKHR");
#endif // defined(VK_KHR_timeline_semaphore)
#if defined(VK_KHR_video_decode_queue)
	vkCmdDecodeVideoKHR = (PFN_vkCmdDecodeVideoKHR)load(context, "vkCmdDecodeVideoKHR");
#endif // defined(VK_KHR_video_decode_queue)
#if defined(VK_KHR_video_encode_queue)
	vkGetEncodedVideoSessionParametersKHR = (PFN_vkGetEncodedVideoSessionParametersKHR)load(context, "vkGetEncodedVideoSessionParametersKHR");
	vkCmdEncodeVideoKHR = (PFN_vkCmdEncodeVideoKHR)load(context, "vkCmdEncodeVideoKHR");
#endif // defined(VK_KHR_video_encode_queue)
#if defined(VK_KHR_video_queue)
	vkCreateVideoSessionKHR = (PFN_vkCreateVideoSessionKHR)load(context, "vkCreateVideoSessionKHR");
	vkDestroyVideoSessionKHR = (PFN_vkDestroyVideoSessionKHR)load(context, "vkDestroyVideoSessionKHR");
	vkGetVideoSessionMemoryRequirementsKHR = (PFN_vkGetVideoSessionMemoryRequirementsKHR)load(context, "vkGetVideoSessionMemoryRequirementsKHR");
	vkBindVideoSessionMemoryKHR = (PFN_vkBindVideoSessionMemoryKHR)load(context, "vkBindVideoSessionMemoryKHR");
	vkCreateVideoSessionParametersKHR = (PFN_vkCreateVideoSessionParametersKHR)load(context, "vkCreateVideoSessionParametersKHR");
	vkUpdateVideoSessionParametersKHR = (PFN_vkUpdateVideoSessionParametersKHR)load(context, "vkUpdateVideoSessionParametersKHR");
	vkDestroyVideoSessionParametersKHR = (PFN_vkDestroyVideoSessionParametersKHR)load(context, "vkDestroyVideoSessionParametersKHR");
	vkCmdBeginVideoCodingKHR = (PFN_vkCmdBeginVideoCodingKHR)load(context, "vkCmdBeginVideoCodingKHR");
	vkCmdEndVideoCodingKHR = (PFN_vkCmdEndVideoCodingKHR)load(context, "vkCmdEndVideoCodingKHR");
	vkCmdControlVideoCodingKHR = (PFN_vkCmdControlVideoCodingKHR)load(context, "vkCmdControlVideoCodingKHR");
#endif // defined(VK_KHR_video_queue)
#if defined(VK_NV_clip_space_w_scaling)
	vkCmdSetViewportWScalingNV = (PFN_vkCmdSetViewportWScalingNV)load(context, "vkCmdSetViewportWScalingNV");
#endif // defined(VK_NV_clip_space_w_scaling)
#if defined(VK_NV_copy_memory_indirect)
	vkCmdCopyMemoryIndirectNV = (PFN_vkCmdCopyMemoryIndirectNV)load(context, "vkCmdCopyMemoryIndirectNV");
	vkCmdCopyMemoryToImageIndirectNV = (PFN_vkCmdCopyMemoryToImageIndirectNV)load(context, "vkCmdCopyMemoryToImageIndirectNV");
#endif // defined(VK_NV_copy_memory_indirect)
#if defined(VK_NV_cuda_kernel_launch)
	vkCreateCudaModuleNV = (PFN_vkCreateCudaModuleNV)load(context, "vkCreateCudaModuleNV");
	vkGetCudaModuleCacheNV = (PFN_vkGetCudaModuleCacheNV)load(context, "vkGetCudaModuleCacheNV");
	vkCreateCudaFunctionNV = (PFN_vkCreateCudaFunctionNV)load(context, "vkCreateCudaFunctionNV");
	vkDestroyCudaModuleNV = (PFN_vkDestroyCudaModuleNV)load(context, "vkDestroyCudaModuleNV");
	vkDestroyCudaFunctionNV = (PFN_vkDestroyCudaFunctionNV)load(context, "vkDestroyCudaFunctionNV");
	vkCmdCudaLaunchKernelNV = (PFN_vkCmdCudaLaunchKernelNV)load(context, "vkCmdCudaLaunchKernelNV");
#endif // defined(VK_NV_cuda_kernel_launch)
#if defined(VK_NV_device_diagnostic_checkpoints)
	vkCmdSetCheckpointNV = (PFN_vkCmdSetCheckpointNV)load(context, "vkCmdSetCheckpointNV");
	vkGetQueueCheckpointDataNV = (PFN_vkGetQueueCheckpointDataNV)load(context, "vkGetQueueCheckpointDataNV");
#endif // defined(VK_NV_device_diagnostic_checkpoints)
#if defined(VK_NV_device_generated_commands)
	vkGetGeneratedCommandsMemoryRequirementsNV = (PFN_vkGetGeneratedCommandsMemoryRequirementsNV)load(context, "vkGetGeneratedCommandsMemoryRequirementsNV");
	vkCmdPreprocessGeneratedCommandsNV = (PFN_vkCmdPreprocessGeneratedCommandsNV)load(context, "vkCmdPreprocessGeneratedCommandsNV");
	vkCmdExecuteGeneratedCommandsNV = (PFN_vkCmdExecuteGeneratedCommandsNV)load(context, "vkCmdExecuteGeneratedCommandsNV");
	vkCmdBindPipelineShaderGroupNV = (PFN_vkCmdBindPipelineShaderGroupNV)load(context, "vkCmdBindPipelineShaderGroupNV");
	vkCreateIndirectCommandsLayoutNV = (PFN_vkCreateIndirectCommandsLayoutNV)load(context, "vkCreateIndirectCommandsLayoutNV");
	vkDestroyIndirectCommandsLayoutNV = (PFN_vkDestroyIndirectCommandsLayoutNV)load(context, "vkDestroyIndirectCommandsLayoutNV");
#endif // defined(VK_NV_device_generated_commands)
#if defined(VK_NV_device_generated_commands_compute)
	vkGetPipelineIndirectMemoryRequirementsNV = (PFN_vkGetPipelineIndirectMemoryRequirementsNV)load(context, "vkGetPipelineIndirectMemoryRequirementsNV");
	vkCmdUpdatePipelineIndirectBufferNV = (PFN_vkCmdUpdatePipelineIndirectBufferNV)load(context, "vkCmdUpdatePipelineIndirectBufferNV");
	vkGetPipelineIndirectDeviceAddressNV = (PFN_vkGetPipelineIndirectDeviceAddressNV)load(context, "vkGetPipelineIndirectDeviceAddressNV");
#endif // defined(VK_NV_device_generated_commands_compute)
#if defined(VK_NV_external_memory_rdma)
	vkGetMemoryRemoteAddressNV = (PFN_vkGetMemoryRemoteAddressNV)load(context, "vkGetMemoryRemoteAddressNV");
#endif // defined(VK_NV_external_memory_rdma)
#if defined(VK_NV_external_memory_win32)
	vkGetMemoryWin32HandleNV = (PFN_vkGetMemoryWin32HandleNV)load(context, "vkGetMemoryWin32HandleNV");
#endif // defined(VK_NV_external_memory_win32)
#if defined(VK_NV_fragment_shading_rate_enums)
	vkCmdSetFragmentShadingRateEnumNV = (PFN_vkCmdSetFragmentShadingRateEnumNV)load(context, "vkCmdSetFragmentShadingRateEnumNV");
#endif // defined(VK_NV_fragment_shading_rate_enums)
#if defined(VK_NV_low_latency2)
	vkSetLatencySleepModeNV = (PFN_vkSetLatencySleepModeNV)load(context, "vkSetLatencySleepModeNV");
	vkLatencySleepNV = (PFN_vkLatencySleepNV)load(context, "vkLatencySleepNV");
	vkSetLatencyMarkerNV = (PFN_vkSetLatencyMarkerNV)load(context, "vkSetLatencyMarkerNV");
	vkGetLatencyTimingsNV = (PFN_vkGetLatencyTimingsNV)load(context, "vkGetLatencyTimingsNV");
	vkQueueNotifyOutOfBandNV = (PFN_vkQueueNotifyOutOfBandNV)load(context, "vkQueueNotifyOutOfBandNV");
#endif // defined(VK_NV_low_latency2)
#if defined(VK_NV_memory_decompression)
	vkCmdDecompressMemoryNV = (PFN_vkCmdDecompressMemoryNV)load(context, "vkCmdDecompressMemoryNV");
	vkCmdDecompressMemoryIndirectCountNV = (PFN_vkCmdDecompressMemoryIndirectCountNV)load(context, "vkCmdDecompressMemoryIndirectCountNV");
#endif // defined(VK_NV_memory_decompression)
#if defined(VK_NV_mesh_shader)
	vkCmdDrawMeshTasksNV = (PFN_vkCmdDrawMeshTasksNV)load(context, "vkCmdDrawMeshTasksNV");
	vkCmdDrawMeshTasksIndirectNV = (PFN_vkCmdDrawMeshTasksIndirectNV)load(context, "vkCmdDrawMeshTasksIndirectNV");
	vkCmdDrawMeshTasksIndirectCountNV = (PFN_vkCmdDrawMeshTasksIndirectCountNV)load(context, "vkCmdDrawMeshTasksIndirectCountNV");
#endif // defined(VK_NV_mesh_shader)
#if defined(VK_NV_optical_flow)
	vkCreateOpticalFlowSessionNV = (PFN_vkCreateOpticalFlowSessionNV)load(context, "vkCreateOpticalFlowSessionNV");
	vkDestroyOpticalFlowSessionNV = (PFN_vkDestroyOpticalFlowSessionNV)load(context, "vkDestroyOpticalFlowSessionNV");
	vkBindOpticalFlowSessionImageNV = (PFN_vkBindOpticalFlowSessionImageNV)load(context, "vkBindOpticalFlowSessionImageNV");
	vkCmdOpticalFlowExecuteNV = (PFN_vkCmdOpticalFlowExecuteNV)load(context, "vkCmdOpticalFlowExecuteNV");
#endif // defined(VK_NV_optical_flow)
#if defined(VK_NV_ray_tracing)
	vkCreateAccelerationStructureNV = (PFN_vkCreateAccelerationStructureNV)load(context, "vkCreateAccelerationStructureNV");
	vkDestroyAccelerationStructureNV = (PFN_vkDestroyAccelerationStructureNV)load(context, "vkDestroyAccelerationStructureNV");
	vkGetAccelerationStructureMemoryRequirementsNV = (PFN_vkGetAccelerationStructureMemoryRequirementsNV)load(context, "vkGetAccelerationStructureMemoryRequirementsNV");
	vkBindAccelerationStructureMemoryNV = (PFN_vkBindAccelerationStructureMemoryNV)load(context, "vkBindAccelerationStructureMemoryNV");
	vkCmdBuildAccelerationStructureNV = (PFN_vkCmdBuildAccelerationStructureNV)load(context, "vkCmdBuildAccelerationStructureNV");
	vkCmdCopyAccelerationStructureNV = (PFN_vkCmdCopyAccelerationStructureNV)load(context, "vkCmdCopyAccelerationStructureNV");
	vkCmdTraceRaysNV = (PFN_vkCmdTraceRaysNV)load(context, "vkCmdTraceRaysNV");
	vkCreateRayTracingPipelinesNV = (PFN_vkCreateRayTracingPipelinesNV)load(context, "vkCreateRayTracingPipelinesNV");
	vkGetRayTracingShaderGroupHandlesNV = (PFN_vkGetRayTracingShaderGroupHandlesNV)load(context, "vkGetRayTracingShaderGroupHandlesNV");
	vkGetAccelerationStructureHandleNV = (PFN_vkGetAccelerationStructureHandleNV)load(context, "vkGetAccelerationStructureHandleNV");
	vkCmdWriteAccelerationStructuresPropertiesNV = (PFN_vkCmdWriteAccelerationStructuresPropertiesNV)load(context, "vkCmdWriteAccelerationStructuresPropertiesNV");
	vkCompileDeferredNV = (PFN_vkCompileDeferredNV)load(context, "vkCompileDeferredNV");
#endif // defined(VK_NV_ray_tracing)
#if defined(VK_NV_scissor_exclusive)
	vkCmdSetExclusiveScissorEnableNV = (PFN_vkCmdSetExclusiveScissorEnableNV)load(context, "vkCmdSetExclusiveScissorEnableNV");
	vkCmdSetExclusiveScissorNV = (PFN_vkCmdSetExclusiveScissorNV)load(context, "vkCmdSetExclusiveScissorNV");
#endif // defined(VK_NV_scissor_exclusive)
#if defined(VK_NV_shading_rate_image)
	vkCmdBindShadingRateImageNV = (PFN_vkCmdBindShadingRateImageNV)load(context, "vkCmdBindShadingRateImageNV");
	vkCmdSetViewportShadingRatePaletteNV = (PFN_vkCmdSetViewportShadingRatePaletteNV)load(context, "vkCmdSetViewportShadingRatePaletteNV");
	vkCmdSetCoarseSampleOrderNV = (PFN_vkCmdSetCoarseSampleOrderNV)load(context, "vkCmdSetCoarseSampleOrderNV");
#endif // defined(VK_NV_shading_rate_image)
#if defined(VK_NVX_binary_import)
	vkCreateCuModuleNVX = (PFN_vkCreateCuModuleNVX)load(context, "vkCreateCuModuleNVX");
	vkCreateCuFunctionNVX = (PFN_vkCreateCuFunctionNVX)load(context, "vkCreateCuFunctionNVX");
	vkDestroyCuModuleNVX = (PFN_vkDestroyCuModuleNVX)load(context, "vkDestroyCuModuleNVX");
	vkDestroyCuFunctionNVX = (PFN_vkDestroyCuFunctionNVX)load(context, "vkDestroyCuFunctionNVX");
	vkCmdCuLaunchKernelNVX = (PFN_vkCmdCuLaunchKernelNVX)load(context, "vkCmdCuLaunchKernelNVX");
#endif // defined(VK_NVX_binary_import)
#if defined(VK_NVX_image_view_handle)
	vkGetImageViewHandleNVX = (PFN_vkGetImageViewHandleNVX)load(context, "vkGetImageViewHandleNVX");
	vkGetImageViewAddressNVX = (PFN_vkGetImageViewAddressNVX)load(context, "vkGetImageViewAddressNVX");
#endif // defined(VK_NVX_image_view_handle)
#if defined(VK_QCOM_tile_properties)
	vkGetFramebufferTilePropertiesQCOM = (PFN_vkGetFramebufferTilePropertiesQCOM)load(context, "vkGetFramebufferTilePropertiesQCOM");
	vkGetDynamicRenderingTilePropertiesQCOM = (PFN_vkGetDynamicRenderingTilePropertiesQCOM)load(context, "vkGetDynamicRenderingTilePropertiesQCOM");
#endif // defined(VK_QCOM_tile_properties)
#if defined(VK_QNX_external_memory_screen_buffer)
	vkGetScreenBufferPropertiesQNX = (PFN_vkGetScreenBufferPropertiesQNX)load(context, "vkGetScreenBufferPropertiesQNX");
#endif // defined(VK_QNX_external_memory_screen_buffer)
#if defined(VK_VALVE_descriptor_set_host_mapping)
	vkGetDescriptorSetLayoutHostMappingInfoVALVE = (PFN_vkGetDescriptorSetLayoutHostMappingInfoVALVE)load(context, "vkGetDescriptorSetLayoutHostMappingInfoVALVE");
	vkGetDescriptorSetHostMappingVALVE = (PFN_vkGetDescriptorSetHostMappingVALVE)load(context, "vkGetDescriptorSetHostMappingVALVE");
#endif // defined(VK_VALVE_descriptor_set_host_mapping)
#if defined(VK_EXT_extended_dynamic_state) || (defined(VK_EXT_shader_object))
	vkCmdSetCullModeEXT = (PFN_vkCmdSetCullModeEXT)load(context, "vkCmdSetCullModeEXT");
	vkCmdSetFrontFaceEXT = (PFN_vkCmdSetFrontFaceEXT)load(context, "vkCmdSetFrontFaceEXT");
	vkCmdSetPrimitiveTopologyEXT = (PFN_vkCmdSetPrimitiveTopologyEXT)load(context, "vkCmdSetPrimitiveTopologyEXT");
	vkCmdSetViewportWithCountEXT = (PFN_vkCmdSetViewportWithCountEXT)load(context, "vkCmdSetViewportWithCountEXT");
	vkCmdSetScissorWithCountEXT = (PFN_vkCmdSetScissorWithCountEXT)load(context, "vkCmdSetScissorWithCountEXT");
	vkCmdBindVertexBuffers2EXT = (PFN_vkCmdBindVertexBuffers2EXT)load(context, "vkCmdBindVertexBuffers2EXT");
	vkCmdSetDepthTestEnableEXT = (PFN_vkCmdSetDepthTestEnableEXT)load(context, "vkCmdSetDepthTestEnableEXT");
	vkCmdSetDepthWriteEnableEXT = (PFN_vkCmdSetDepthWriteEnableEXT)load(context, "vkCmdSetDepthWriteEnableEXT");
	vkCmdSetDepthCompareOpEXT = (PFN_vkCmdSetDepthCompareOpEXT)load(context, "vkCmdSetDepthCompareOpEXT");
	vkCmdSetDepthBoundsTestEnableEXT = (PFN_vkCmdSetDepthBoundsTestEnableEXT)load(context, "vkCmdSetDepthBoundsTestEnableEXT");
	vkCmdSetStencilTestEnableEXT = (PFN_vkCmdSetStencilTestEnableEXT)load(context, "vkCmdSetStencilTestEnableEXT");
	vkCmdSetStencilOpEXT = (PFN_vkCmdSetStencilOpEXT)load(context, "vkCmdSetStencilOpEXT");
#endif // defined(VK_EXT_extended_dynamic_state) || (defined(VK_EXT_shader_object))
#if defined(VK_EXT_extended_dynamic_state2) || (defined(VK_EXT_shader_object))
	vkCmdSetPatchControlPointsEXT = (PFN_vkCmdSetPatchControlPointsEXT)load(context, "vkCmdSetPatchControlPointsEXT");
	vkCmdSetRasterizerDiscardEnableEXT = (PFN_vkCmdSetRasterizerDiscardEnableEXT)load(context, "vkCmdSetRasterizerDiscardEnableEXT");
	vkCmdSetDepthBiasEnableEXT = (PFN_vkCmdSetDepthBiasEnableEXT)load(context, "vkCmdSetDepthBiasEnableEXT");
	vkCmdSetLogicOpEXT = (PFN_vkCmdSetLogicOpEXT)load(context, "vkCmdSetLogicOpEXT");
	vkCmdSetPrimitiveRestartEnableEXT = (PFN_vkCmdSetPrimitiveRestartEnableEXT)load(context, "vkCmdSetPrimitiveRestartEnableEXT");
#endif // defined(VK_EXT_extended_dynamic_state2) || (defined(VK_EXT_shader_object))
#if defined(VK_EXT_extended_dynamic_state3) || (defined(VK_EXT_shader_object))
	vkCmdSetDepthClampEnableEXT = (PFN_vkCmdSetDepthClampEnableEXT)load(context, "vkCmdSetDepthClampEnableEXT");
	vkCmdSetPolygonModeEXT = (PFN_vkCmdSetPolygonModeEXT)load(context, "vkCmdSetPolygonModeEXT");
	vkCmdSetRasterizationSamplesEXT = (PFN_vkCmdSetRasterizationSamplesEXT)load(context, "vkCmdSetRasterizationSamplesEXT");
	vkCmdSetSampleMaskEXT = (PFN_vkCmdSetSampleMaskEXT)load(context, "vkCmdSetSampleMaskEXT");
	vkCmdSetAlphaToCoverageEnableEXT = (PFN_vkCmdSetAlphaToCoverageEnableEXT)load(context, "vkCmdSetAlphaToCoverageEnableEXT");
	vkCmdSetAlphaToOneEnableEXT = (PFN_vkCmdSetAlphaToOneEnableEXT)load(context, "vkCmdSetAlphaToOneEnableEXT");
	vkCmdSetLogicOpEnableEXT = (PFN_vkCmdSetLogicOpEnableEXT)load(context, "vkCmdSetLogicOpEnableEXT");
	vkCmdSetColorBlendEnableEXT = (PFN_vkCmdSetColorBlendEnableEXT)load(context, "vkCmdSetColorBlendEnableEXT");
	vkCmdSetColorBlendEquationEXT = (PFN_vkCmdSetColorBlendEquationEXT)load(context, "vkCmdSetColorBlendEquationEXT");
	vkCmdSetColorWriteMaskEXT = (PFN_vkCmdSetColorWriteMaskEXT)load(context, "vkCmdSetColorWriteMaskEXT");
#endif // defined(VK_EXT_extended_dynamic_state3) || (defined(VK_EXT_shader_object))
#if defined(VK_EXT_extended_dynamic_state3) && (defined(VK_KHR_maintenance2) || defined(VK_VERSION_1_1)) || (defined(VK_EXT_shader_object))
	vkCmdSetTessellationDomainOriginEXT = (PFN_vkCmdSetTessellationDomainOriginEXT)load(context, "vkCmdSetTessellationDomainOriginEXT");
#endif // defined(VK_EXT_extended_dynamic_state3) && (defined(VK_KHR_maintenance2) || defined(VK_VERSION_1_1)) || (defined(VK_EXT_shader_object))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_transform_feedback) || (defined(VK_EXT_shader_object) && defined(VK_EXT_transform_feedback))
	vkCmdSetRasterizationStreamEXT = (PFN_vkCmdSetRasterizationStreamEXT)load(context, "vkCmdSetRasterizationStreamEXT");
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_transform_feedback) || (defined(VK_EXT_shader_object) && defined(VK_EXT_transform_feedback))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_conservative_rasterization) || (defined(VK_EXT_shader_object) && defined(VK_EXT_conservative_rasterization))
	vkCmdSetConservativeRasterizationModeEXT = (PFN_vkCmdSetConservativeRasterizationModeEXT)load(context, "vkCmdSetConservativeRasterizationModeEXT");
	vkCmdSetExtraPrimitiveOverestimationSizeEXT = (PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT)load(context, "vkCmdSetExtraPrimitiveOverestimationSizeEXT");
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_conservative_rasterization) || (defined(VK_EXT_shader_object) && defined(VK_EXT_conservative_rasterization))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_enable) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_enable))
	vkCmdSetDepthClipEnableEXT = (PFN_vkCmdSetDepthClipEnableEXT)load(context, "vkCmdSetDepthClipEnableEXT");
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_enable) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_enable))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_sample_locations) || (defined(VK_EXT_shader_object) && defined(VK_EXT_sample_locations))
	vkCmdSetSampleLocationsEnableEXT = (PFN_vkCmdSetSampleLocationsEnableEXT)load(context, "vkCmdSetSampleLocationsEnableEXT");
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_sample_locations) || (defined(VK_EXT_shader_object) && defined(VK_EXT_sample_locations))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_blend_operation_advanced) || (defined(VK_EXT_shader_object) && defined(VK_EXT_blend_operation_advanced))
	vkCmdSetColorBlendAdvancedEXT = (PFN_vkCmdSetColorBlendAdvancedEXT)load(context, "vkCmdSetColorBlendAdvancedEXT");
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_blend_operation_advanced) || (defined(VK_EXT_shader_object) && defined(VK_EXT_blend_operation_advanced))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_provoking_vertex) || (defined(VK_EXT_shader_object) && defined(VK_EXT_provoking_vertex))
	vkCmdSetProvokingVertexModeEXT = (PFN_vkCmdSetProvokingVertexModeEXT)load(context, "vkCmdSetProvokingVertexModeEXT");
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_provoking_vertex) || (defined(VK_EXT_shader_object) && defined(VK_EXT_provoking_vertex))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_line_rasterization) || (defined(VK_EXT_shader_object) && defined(VK_EXT_line_rasterization))
	vkCmdSetLineRasterizationModeEXT = (PFN_vkCmdSetLineRasterizationModeEXT)load(context, "vkCmdSetLineRasterizationModeEXT");
	vkCmdSetLineStippleEnableEXT = (PFN_vkCmdSetLineStippleEnableEXT)load(context, "vkCmdSetLineStippleEnableEXT");
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_line_rasterization) || (defined(VK_EXT_shader_object) && defined(VK_EXT_line_rasterization))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_control) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_control))
	vkCmdSetDepthClipNegativeOneToOneEXT = (PFN_vkCmdSetDepthClipNegativeOneToOneEXT)load(context, "vkCmdSetDepthClipNegativeOneToOneEXT");
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_control) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_control))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_clip_space_w_scaling) || (defined(VK_EXT_shader_object) && defined(VK_NV_clip_space_w_scaling))
	vkCmdSetViewportWScalingEnableNV = (PFN_vkCmdSetViewportWScalingEnableNV)load(context, "vkCmdSetViewportWScalingEnableNV");
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_clip_space_w_scaling) || (defined(VK_EXT_shader_object) && defined(VK_NV_clip_space_w_scaling))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_viewport_swizzle) || (defined(VK_EXT_shader_object) && defined(VK_NV_viewport_swizzle))
	vkCmdSetViewportSwizzleNV = (PFN_vkCmdSetViewportSwizzleNV)load(context, "vkCmdSetViewportSwizzleNV");
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_viewport_swizzle) || (defined(VK_EXT_shader_object) && defined(VK_NV_viewport_swizzle))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_fragment_coverage_to_color) || (defined(VK_EXT_shader_object) && defined(VK_NV_fragment_coverage_to_color))
	vkCmdSetCoverageToColorEnableNV = (PFN_vkCmdSetCoverageToColorEnableNV)load(context, "vkCmdSetCoverageToColorEnableNV");
	vkCmdSetCoverageToColorLocationNV = (PFN_vkCmdSetCoverageToColorLocationNV)load(context, "vkCmdSetCoverageToColorLocationNV");
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_fragment_coverage_to_color) || (defined(VK_EXT_shader_object) && defined(VK_NV_fragment_coverage_to_color))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_framebuffer_mixed_samples) || (defined(VK_EXT_shader_object) && defined(VK_NV_framebuffer_mixed_samples))
	vkCmdSetCoverageModulationModeNV = (PFN_vkCmdSetCoverageModulationModeNV)load(context, "vkCmdSetCoverageModulationModeNV");
	vkCmdSetCoverageModulationTableEnableNV = (PFN_vkCmdSetCoverageModulationTableEnableNV)load(context, "vkCmdSetCoverageModulationTableEnableNV");
	vkCmdSetCoverageModulationTableNV = (PFN_vkCmdSetCoverageModulationTableNV)load(context, "vkCmdSetCoverageModulationTableNV");
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_framebuffer_mixed_samples) || (defined(VK_EXT_shader_object) && defined(VK_NV_framebuffer_mixed_samples))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_shading_rate_image) || (defined(VK_EXT_shader_object) && defined(VK_NV_shading_rate_image))
	vkCmdSetShadingRateImageEnableNV = (PFN_vkCmdSetShadingRateImageEnableNV)load(context, "vkCmdSetShadingRateImageEnableNV");
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_shading_rate_image) || (defined(VK_EXT_shader_object) && defined(VK_NV_shading_rate_image))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_representative_fragment_test) || (defined(VK_EXT_shader_object) && defined(VK_NV_representative_fragment_test))
	vkCmdSetRepresentativeFragmentTestEnableNV = (PFN_vkCmdSetRepresentativeFragmentTestEnableNV)load(context, "vkCmdSetRepresentativeFragmentTestEnableNV");
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_representative_fragment_test) || (defined(VK_EXT_shader_object) && defined(VK_NV_representative_fragment_test))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_coverage_reduction_mode) || (defined(VK_EXT_shader_object) && defined(VK_NV_coverage_reduction_mode))
	vkCmdSetCoverageReductionModeNV = (PFN_vkCmdSetCoverageReductionModeNV)load(context, "vkCmdSetCoverageReductionModeNV");
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_coverage_reduction_mode) || (defined(VK_EXT_shader_object) && defined(VK_NV_coverage_reduction_mode))
#if defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))
	vkGetDeviceGroupSurfacePresentModes2EXT = (PFN_vkGetDeviceGroupSurfacePresentModes2EXT)load(context, "vkGetDeviceGroupSurfacePresentModes2EXT");
#endif // defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))
#if defined(VK_EXT_host_image_copy) || (defined(VK_EXT_image_compression_control))
	vkGetImageSubresourceLayout2EXT = (PFN_vkGetImageSubresourceLayout2EXT)load(context, "vkGetImageSubresourceLayout2EXT");
#endif // defined(VK_EXT_host_image_copy) || (defined(VK_EXT_image_compression_control))
#if defined(VK_EXT_shader_object) || (defined(VK_EXT_vertex_input_dynamic_state))
	vkCmdSetVertexInputEXT = (PFN_vkCmdSetVertexInputEXT)load(context, "vkCmdSetVertexInputEXT");
#endif // defined(VK_EXT_shader_object) || (defined(VK_EXT_vertex_input_dynamic_state))
#if defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
	vkCmdPushDescriptorSetWithTemplateKHR = (PFN_vkCmdPushDescriptorSetWithTemplateKHR)load(context, "vkCmdPushDescriptorSetWithTemplateKHR");
#endif // defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
#if defined(VK_KHR_device_group) && defined(VK_KHR_surface) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
	vkGetDeviceGroupPresentCapabilitiesKHR = (PFN_vkGetDeviceGroupPresentCapabilitiesKHR)load(context, "vkGetDeviceGroupPresentCapabilitiesKHR");
	vkGetDeviceGroupSurfacePresentModesKHR = (PFN_vkGetDeviceGroupSurfacePresentModesKHR)load(context, "vkGetDeviceGroupSurfacePresentModesKHR");
#endif // defined(VK_KHR_device_group) && defined(VK_KHR_surface) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
#if defined(VK_KHR_device_group) && defined(VK_KHR_swapchain) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
	vkAcquireNextImage2KHR = (PFN_vkAcquireNextImage2KHR)load(context, "vkAcquireNextImage2KHR");
#endif // defined(VK_KHR_device_group) && defined(VK_KHR_swapchain) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
	// KODIAK_GEN_LOAD_DEVICE
}


// KODIAK_GEN_SOURCE_FUNCTION_PTRS
#if defined(VK_VERSION_1_0)
PFN_vkCreateInstance vkCreateInstance;
PFN_vkDestroyInstance vkDestroyInstance;
PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices;
PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures;
PFN_vkGetPhysicalDeviceFormatProperties vkGetPhysicalDeviceFormatProperties;
PFN_vkGetPhysicalDeviceImageFormatProperties vkGetPhysicalDeviceImageFormatProperties;
PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties;
PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties;
PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr;
PFN_vkCreateDevice vkCreateDevice;
PFN_vkDestroyDevice vkDestroyDevice;
PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties;
PFN_vkEnumerateDeviceExtensionProperties vkEnumerateDeviceExtensionProperties;
PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties;
PFN_vkEnumerateDeviceLayerProperties vkEnumerateDeviceLayerProperties;
PFN_vkGetDeviceQueue vkGetDeviceQueue;
PFN_vkQueueSubmit vkQueueSubmit;
PFN_vkQueueWaitIdle vkQueueWaitIdle;
PFN_vkDeviceWaitIdle vkDeviceWaitIdle;
PFN_vkAllocateMemory vkAllocateMemory;
PFN_vkFreeMemory vkFreeMemory;
PFN_vkMapMemory vkMapMemory;
PFN_vkUnmapMemory vkUnmapMemory;
PFN_vkFlushMappedMemoryRanges vkFlushMappedMemoryRanges;
PFN_vkInvalidateMappedMemoryRanges vkInvalidateMappedMemoryRanges;
PFN_vkGetDeviceMemoryCommitment vkGetDeviceMemoryCommitment;
PFN_vkBindBufferMemory vkBindBufferMemory;
PFN_vkBindImageMemory vkBindImageMemory;
PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements;
PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements;
PFN_vkGetImageSparseMemoryRequirements vkGetImageSparseMemoryRequirements;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties vkGetPhysicalDeviceSparseImageFormatProperties;
PFN_vkQueueBindSparse vkQueueBindSparse;
PFN_vkCreateFence vkCreateFence;
PFN_vkDestroyFence vkDestroyFence;
PFN_vkResetFences vkResetFences;
PFN_vkGetFenceStatus vkGetFenceStatus;
PFN_vkWaitForFences vkWaitForFences;
PFN_vkCreateSemaphore vkCreateSemaphore;
PFN_vkDestroySemaphore vkDestroySemaphore;
PFN_vkCreateEvent vkCreateEvent;
PFN_vkDestroyEvent vkDestroyEvent;
PFN_vkGetEventStatus vkGetEventStatus;
PFN_vkSetEvent vkSetEvent;
PFN_vkResetEvent vkResetEvent;
PFN_vkCreateQueryPool vkCreateQueryPool;
PFN_vkDestroyQueryPool vkDestroyQueryPool;
PFN_vkGetQueryPoolResults vkGetQueryPoolResults;
PFN_vkCreateBuffer vkCreateBuffer;
PFN_vkDestroyBuffer vkDestroyBuffer;
PFN_vkCreateBufferView vkCreateBufferView;
PFN_vkDestroyBufferView vkDestroyBufferView;
PFN_vkCreateImage vkCreateImage;
PFN_vkDestroyImage vkDestroyImage;
PFN_vkGetImageSubresourceLayout vkGetImageSubresourceLayout;
PFN_vkCreateImageView vkCreateImageView;
PFN_vkDestroyImageView vkDestroyImageView;
PFN_vkCreateShaderModule vkCreateShaderModule;
PFN_vkDestroyShaderModule vkDestroyShaderModule;
PFN_vkCreatePipelineCache vkCreatePipelineCache;
PFN_vkDestroyPipelineCache vkDestroyPipelineCache;
PFN_vkGetPipelineCacheData vkGetPipelineCacheData;
PFN_vkMergePipelineCaches vkMergePipelineCaches;
PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines;
PFN_vkCreateComputePipelines vkCreateComputePipelines;
PFN_vkDestroyPipeline vkDestroyPipeline;
PFN_vkCreatePipelineLayout vkCreatePipelineLayout;
PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout;
PFN_vkCreateSampler vkCreateSampler;
PFN_vkDestroySampler vkDestroySampler;
PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout;
PFN_vkDestroyDescriptorSetLayout vkDestroyDescriptorSetLayout;
PFN_vkCreateDescriptorPool vkCreateDescriptorPool;
PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool;
PFN_vkResetDescriptorPool vkResetDescriptorPool;
PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets;
PFN_vkFreeDescriptorSets vkFreeDescriptorSets;
PFN_vkUpdateDescriptorSets vkUpdateDescriptorSets;
PFN_vkCreateFramebuffer vkCreateFramebuffer;
PFN_vkDestroyFramebuffer vkDestroyFramebuffer;
PFN_vkCreateRenderPass vkCreateRenderPass;
PFN_vkDestroyRenderPass vkDestroyRenderPass;
PFN_vkGetRenderAreaGranularity vkGetRenderAreaGranularity;
PFN_vkCreateCommandPool vkCreateCommandPool;
PFN_vkDestroyCommandPool vkDestroyCommandPool;
PFN_vkResetCommandPool vkResetCommandPool;
PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers;
PFN_vkFreeCommandBuffers vkFreeCommandBuffers;
PFN_vkBeginCommandBuffer vkBeginCommandBuffer;
PFN_vkEndCommandBuffer vkEndCommandBuffer;
PFN_vkResetCommandBuffer vkResetCommandBuffer;
PFN_vkCmdBindPipeline vkCmdBindPipeline;
PFN_vkCmdSetViewport vkCmdSetViewport;
PFN_vkCmdSetScissor vkCmdSetScissor;
PFN_vkCmdSetLineWidth vkCmdSetLineWidth;
PFN_vkCmdSetDepthBias vkCmdSetDepthBias;
PFN_vkCmdSetBlendConstants vkCmdSetBlendConstants;
PFN_vkCmdSetDepthBounds vkCmdSetDepthBounds;
PFN_vkCmdSetStencilCompareMask vkCmdSetStencilCompareMask;
PFN_vkCmdSetStencilWriteMask vkCmdSetStencilWriteMask;
PFN_vkCmdSetStencilReference vkCmdSetStencilReference;
PFN_vkCmdBindDescriptorSets vkCmdBindDescriptorSets;
PFN_vkCmdBindIndexBuffer vkCmdBindIndexBuffer;
PFN_vkCmdBindVertexBuffers vkCmdBindVertexBuffers;
PFN_vkCmdDraw vkCmdDraw;
PFN_vkCmdDrawIndexed vkCmdDrawIndexed;
PFN_vkCmdDrawIndirect vkCmdDrawIndirect;
PFN_vkCmdDrawIndexedIndirect vkCmdDrawIndexedIndirect;
PFN_vkCmdDispatch vkCmdDispatch;
PFN_vkCmdDispatchIndirect vkCmdDispatchIndirect;
PFN_vkCmdCopyBuffer vkCmdCopyBuffer;
PFN_vkCmdCopyImage vkCmdCopyImage;
PFN_vkCmdBlitImage vkCmdBlitImage;
PFN_vkCmdCopyBufferToImage vkCmdCopyBufferToImage;
PFN_vkCmdCopyImageToBuffer vkCmdCopyImageToBuffer;
PFN_vkCmdUpdateBuffer vkCmdUpdateBuffer;
PFN_vkCmdFillBuffer vkCmdFillBuffer;
PFN_vkCmdClearColorImage vkCmdClearColorImage;
PFN_vkCmdClearDepthStencilImage vkCmdClearDepthStencilImage;
PFN_vkCmdClearAttachments vkCmdClearAttachments;
PFN_vkCmdResolveImage vkCmdResolveImage;
PFN_vkCmdSetEvent vkCmdSetEvent;
PFN_vkCmdResetEvent vkCmdResetEvent;
PFN_vkCmdWaitEvents vkCmdWaitEvents;
PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier;
PFN_vkCmdBeginQuery vkCmdBeginQuery;
PFN_vkCmdEndQuery vkCmdEndQuery;
PFN_vkCmdResetQueryPool vkCmdResetQueryPool;
PFN_vkCmdWriteTimestamp vkCmdWriteTimestamp;
PFN_vkCmdCopyQueryPoolResults vkCmdCopyQueryPoolResults;
PFN_vkCmdPushConstants vkCmdPushConstants;
PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass;
PFN_vkCmdNextSubpass vkCmdNextSubpass;
PFN_vkCmdEndRenderPass vkCmdEndRenderPass;
PFN_vkCmdExecuteCommands vkCmdExecuteCommands;
#endif // defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
PFN_vkEnumerateInstanceVersion vkEnumerateInstanceVersion;
PFN_vkBindBufferMemory2 vkBindBufferMemory2;
PFN_vkBindImageMemory2 vkBindImageMemory2;
PFN_vkGetDeviceGroupPeerMemoryFeatures vkGetDeviceGroupPeerMemoryFeatures;
PFN_vkCmdSetDeviceMask vkCmdSetDeviceMask;
PFN_vkCmdDispatchBase vkCmdDispatchBase;
PFN_vkEnumeratePhysicalDeviceGroups vkEnumeratePhysicalDeviceGroups;
PFN_vkGetImageMemoryRequirements2 vkGetImageMemoryRequirements2;
PFN_vkGetBufferMemoryRequirements2 vkGetBufferMemoryRequirements2;
PFN_vkGetImageSparseMemoryRequirements2 vkGetImageSparseMemoryRequirements2;
PFN_vkGetPhysicalDeviceFeatures2 vkGetPhysicalDeviceFeatures2;
PFN_vkGetPhysicalDeviceProperties2 vkGetPhysicalDeviceProperties2;
PFN_vkGetPhysicalDeviceFormatProperties2 vkGetPhysicalDeviceFormatProperties2;
PFN_vkGetPhysicalDeviceImageFormatProperties2 vkGetPhysicalDeviceImageFormatProperties2;
PFN_vkGetPhysicalDeviceQueueFamilyProperties2 vkGetPhysicalDeviceQueueFamilyProperties2;
PFN_vkGetPhysicalDeviceMemoryProperties2 vkGetPhysicalDeviceMemoryProperties2;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 vkGetPhysicalDeviceSparseImageFormatProperties2;
PFN_vkTrimCommandPool vkTrimCommandPool;
PFN_vkGetDeviceQueue2 vkGetDeviceQueue2;
PFN_vkCreateSamplerYcbcrConversion vkCreateSamplerYcbcrConversion;
PFN_vkDestroySamplerYcbcrConversion vkDestroySamplerYcbcrConversion;
PFN_vkCreateDescriptorUpdateTemplate vkCreateDescriptorUpdateTemplate;
PFN_vkDestroyDescriptorUpdateTemplate vkDestroyDescriptorUpdateTemplate;
PFN_vkUpdateDescriptorSetWithTemplate vkUpdateDescriptorSetWithTemplate;
PFN_vkGetPhysicalDeviceExternalBufferProperties vkGetPhysicalDeviceExternalBufferProperties;
PFN_vkGetPhysicalDeviceExternalFenceProperties vkGetPhysicalDeviceExternalFenceProperties;
PFN_vkGetPhysicalDeviceExternalSemaphoreProperties vkGetPhysicalDeviceExternalSemaphoreProperties;
PFN_vkGetDescriptorSetLayoutSupport vkGetDescriptorSetLayoutSupport;
#endif // defined(VK_VERSION_1_1)
#if defined(VK_VERSION_1_2)
PFN_vkCmdDrawIndirectCount vkCmdDrawIndirectCount;
PFN_vkCmdDrawIndexedIndirectCount vkCmdDrawIndexedIndirectCount;
PFN_vkCreateRenderPass2 vkCreateRenderPass2;
PFN_vkCmdBeginRenderPass2 vkCmdBeginRenderPass2;
PFN_vkCmdNextSubpass2 vkCmdNextSubpass2;
PFN_vkCmdEndRenderPass2 vkCmdEndRenderPass2;
PFN_vkResetQueryPool vkResetQueryPool;
PFN_vkGetSemaphoreCounterValue vkGetSemaphoreCounterValue;
PFN_vkWaitSemaphores vkWaitSemaphores;
PFN_vkSignalSemaphore vkSignalSemaphore;
PFN_vkGetBufferDeviceAddress vkGetBufferDeviceAddress;
PFN_vkGetBufferOpaqueCaptureAddress vkGetBufferOpaqueCaptureAddress;
PFN_vkGetDeviceMemoryOpaqueCaptureAddress vkGetDeviceMemoryOpaqueCaptureAddress;
#endif // defined(VK_VERSION_1_2)
#if defined(VK_VERSION_1_3)
PFN_vkGetPhysicalDeviceToolProperties vkGetPhysicalDeviceToolProperties;
PFN_vkCreatePrivateDataSlot vkCreatePrivateDataSlot;
PFN_vkDestroyPrivateDataSlot vkDestroyPrivateDataSlot;
PFN_vkSetPrivateData vkSetPrivateData;
PFN_vkGetPrivateData vkGetPrivateData;
PFN_vkCmdSetEvent2 vkCmdSetEvent2;
PFN_vkCmdResetEvent2 vkCmdResetEvent2;
PFN_vkCmdWaitEvents2 vkCmdWaitEvents2;
PFN_vkCmdPipelineBarrier2 vkCmdPipelineBarrier2;
PFN_vkCmdWriteTimestamp2 vkCmdWriteTimestamp2;
PFN_vkQueueSubmit2 vkQueueSubmit2;
PFN_vkCmdCopyBuffer2 vkCmdCopyBuffer2;
PFN_vkCmdCopyImage2 vkCmdCopyImage2;
PFN_vkCmdCopyBufferToImage2 vkCmdCopyBufferToImage2;
PFN_vkCmdCopyImageToBuffer2 vkCmdCopyImageToBuffer2;
PFN_vkCmdBlitImage2 vkCmdBlitImage2;
PFN_vkCmdResolveImage2 vkCmdResolveImage2;
PFN_vkCmdBeginRendering vkCmdBeginRendering;
PFN_vkCmdEndRendering vkCmdEndRendering;
PFN_vkCmdSetCullMode vkCmdSetCullMode;
PFN_vkCmdSetFrontFace vkCmdSetFrontFace;
PFN_vkCmdSetPrimitiveTopology vkCmdSetPrimitiveTopology;
PFN_vkCmdSetViewportWithCount vkCmdSetViewportWithCount;
PFN_vkCmdSetScissorWithCount vkCmdSetScissorWithCount;
PFN_vkCmdBindVertexBuffers2 vkCmdBindVertexBuffers2;
PFN_vkCmdSetDepthTestEnable vkCmdSetDepthTestEnable;
PFN_vkCmdSetDepthWriteEnable vkCmdSetDepthWriteEnable;
PFN_vkCmdSetDepthCompareOp vkCmdSetDepthCompareOp;
PFN_vkCmdSetDepthBoundsTestEnable vkCmdSetDepthBoundsTestEnable;
PFN_vkCmdSetStencilTestEnable vkCmdSetStencilTestEnable;
PFN_vkCmdSetStencilOp vkCmdSetStencilOp;
PFN_vkCmdSetRasterizerDiscardEnable vkCmdSetRasterizerDiscardEnable;
PFN_vkCmdSetDepthBiasEnable vkCmdSetDepthBiasEnable;
PFN_vkCmdSetPrimitiveRestartEnable vkCmdSetPrimitiveRestartEnable;
PFN_vkGetDeviceBufferMemoryRequirements vkGetDeviceBufferMemoryRequirements;
PFN_vkGetDeviceImageMemoryRequirements vkGetDeviceImageMemoryRequirements;
PFN_vkGetDeviceImageSparseMemoryRequirements vkGetDeviceImageSparseMemoryRequirements;
#endif // defined(VK_VERSION_1_3)
#if defined(VK_AMD_buffer_marker)
PFN_vkCmdWriteBufferMarkerAMD vkCmdWriteBufferMarkerAMD;
#endif // defined(VK_AMD_buffer_marker)
#if defined(VK_AMD_display_native_hdr)
PFN_vkSetLocalDimmingAMD vkSetLocalDimmingAMD;
#endif // defined(VK_AMD_display_native_hdr)
#if defined(VK_AMD_draw_indirect_count)
PFN_vkCmdDrawIndirectCountAMD vkCmdDrawIndirectCountAMD;
PFN_vkCmdDrawIndexedIndirectCountAMD vkCmdDrawIndexedIndirectCountAMD;
#endif // defined(VK_AMD_draw_indirect_count)
#if defined(VK_AMD_shader_info)
PFN_vkGetShaderInfoAMD vkGetShaderInfoAMD;
#endif // defined(VK_AMD_shader_info)
#if defined(VK_AMDX_shader_enqueue)
PFN_vkCreateExecutionGraphPipelinesAMDX vkCreateExecutionGraphPipelinesAMDX;
PFN_vkGetExecutionGraphPipelineScratchSizeAMDX vkGetExecutionGraphPipelineScratchSizeAMDX;
PFN_vkGetExecutionGraphPipelineNodeIndexAMDX vkGetExecutionGraphPipelineNodeIndexAMDX;
PFN_vkCmdInitializeGraphScratchMemoryAMDX vkCmdInitializeGraphScratchMemoryAMDX;
PFN_vkCmdDispatchGraphAMDX vkCmdDispatchGraphAMDX;
PFN_vkCmdDispatchGraphIndirectAMDX vkCmdDispatchGraphIndirectAMDX;
PFN_vkCmdDispatchGraphIndirectCountAMDX vkCmdDispatchGraphIndirectCountAMDX;
#endif // defined(VK_AMDX_shader_enqueue)
#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
PFN_vkGetAndroidHardwareBufferPropertiesANDROID vkGetAndroidHardwareBufferPropertiesANDROID;
PFN_vkGetMemoryAndroidHardwareBufferANDROID vkGetMemoryAndroidHardwareBufferANDROID;
#endif // defined(VK_ANDROID_external_memory_android_hardware_buffer)
#if defined(VK_EXT_acquire_drm_display)
PFN_vkAcquireDrmDisplayEXT vkAcquireDrmDisplayEXT;
PFN_vkGetDrmDisplayEXT vkGetDrmDisplayEXT;
#endif // defined(VK_EXT_acquire_drm_display)
#if defined(VK_EXT_acquire_xlib_display)
PFN_vkAcquireXlibDisplayEXT vkAcquireXlibDisplayEXT;
PFN_vkGetRandROutputDisplayEXT vkGetRandROutputDisplayEXT;
#endif // defined(VK_EXT_acquire_xlib_display)
#if defined(VK_EXT_attachment_feedback_loop_dynamic_state)
PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT vkCmdSetAttachmentFeedbackLoopEnableEXT;
#endif // defined(VK_EXT_attachment_feedback_loop_dynamic_state)
#if defined(VK_EXT_buffer_device_address)
PFN_vkGetBufferDeviceAddressEXT vkGetBufferDeviceAddressEXT;
#endif // defined(VK_EXT_buffer_device_address)
#if defined(VK_EXT_calibrated_timestamps)
PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT vkGetPhysicalDeviceCalibrateableTimeDomainsEXT;
PFN_vkGetCalibratedTimestampsEXT vkGetCalibratedTimestampsEXT;
#endif // defined(VK_EXT_calibrated_timestamps)
#if defined(VK_EXT_color_write_enable)
PFN_vkCmdSetColorWriteEnableEXT vkCmdSetColorWriteEnableEXT;
#endif // defined(VK_EXT_color_write_enable)
#if defined(VK_EXT_conditional_rendering)
PFN_vkCmdBeginConditionalRenderingEXT vkCmdBeginConditionalRenderingEXT;
PFN_vkCmdEndConditionalRenderingEXT vkCmdEndConditionalRenderingEXT;
#endif // defined(VK_EXT_conditional_rendering)
#if defined(VK_EXT_debug_marker)
PFN_vkDebugMarkerSetObjectTagEXT vkDebugMarkerSetObjectTagEXT;
PFN_vkDebugMarkerSetObjectNameEXT vkDebugMarkerSetObjectNameEXT;
PFN_vkCmdDebugMarkerBeginEXT vkCmdDebugMarkerBeginEXT;
PFN_vkCmdDebugMarkerEndEXT vkCmdDebugMarkerEndEXT;
PFN_vkCmdDebugMarkerInsertEXT vkCmdDebugMarkerInsertEXT;
#endif // defined(VK_EXT_debug_marker)
#if defined(VK_EXT_debug_report)
PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT;
PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT;
PFN_vkDebugReportMessageEXT vkDebugReportMessageEXT;
#endif // defined(VK_EXT_debug_report)
#if defined(VK_EXT_debug_utils)
PFN_vkSetDebugUtilsObjectNameEXT vkSetDebugUtilsObjectNameEXT;
PFN_vkSetDebugUtilsObjectTagEXT vkSetDebugUtilsObjectTagEXT;
PFN_vkQueueBeginDebugUtilsLabelEXT vkQueueBeginDebugUtilsLabelEXT;
PFN_vkQueueEndDebugUtilsLabelEXT vkQueueEndDebugUtilsLabelEXT;
PFN_vkQueueInsertDebugUtilsLabelEXT vkQueueInsertDebugUtilsLabelEXT;
PFN_vkCmdBeginDebugUtilsLabelEXT vkCmdBeginDebugUtilsLabelEXT;
PFN_vkCmdEndDebugUtilsLabelEXT vkCmdEndDebugUtilsLabelEXT;
PFN_vkCmdInsertDebugUtilsLabelEXT vkCmdInsertDebugUtilsLabelEXT;
PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT;
PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;
PFN_vkSubmitDebugUtilsMessageEXT vkSubmitDebugUtilsMessageEXT;
#endif // defined(VK_EXT_debug_utils)
#if defined(VK_EXT_depth_bias_control)
PFN_vkCmdSetDepthBias2EXT vkCmdSetDepthBias2EXT;
#endif // defined(VK_EXT_depth_bias_control)
#if defined(VK_EXT_descriptor_buffer)
PFN_vkGetDescriptorSetLayoutSizeEXT vkGetDescriptorSetLayoutSizeEXT;
PFN_vkGetDescriptorSetLayoutBindingOffsetEXT vkGetDescriptorSetLayoutBindingOffsetEXT;
PFN_vkGetDescriptorEXT vkGetDescriptorEXT;
PFN_vkCmdBindDescriptorBuffersEXT vkCmdBindDescriptorBuffersEXT;
PFN_vkCmdSetDescriptorBufferOffsetsEXT vkCmdSetDescriptorBufferOffsetsEXT;
PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT vkCmdBindDescriptorBufferEmbeddedSamplersEXT;
PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT vkGetBufferOpaqueCaptureDescriptorDataEXT;
PFN_vkGetImageOpaqueCaptureDescriptorDataEXT vkGetImageOpaqueCaptureDescriptorDataEXT;
PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT vkGetImageViewOpaqueCaptureDescriptorDataEXT;
PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT vkGetSamplerOpaqueCaptureDescriptorDataEXT;
#endif // defined(VK_EXT_descriptor_buffer)
#if defined(VK_EXT_descriptor_buffer) && (defined(VK_KHR_acceleration_structure) || defined(VK_NV_ray_tracing))
PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT;
#endif // defined(VK_EXT_descriptor_buffer) && (defined(VK_KHR_acceleration_structure) || defined(VK_NV_ray_tracing))
#if defined(VK_EXT_device_fault)
PFN_vkGetDeviceFaultInfoEXT vkGetDeviceFaultInfoEXT;
#endif // defined(VK_EXT_device_fault)
#if defined(VK_EXT_direct_mode_display)
PFN_vkReleaseDisplayEXT vkReleaseDisplayEXT;
#endif // defined(VK_EXT_direct_mode_display)
#if defined(VK_EXT_directfb_surface)
PFN_vkCreateDirectFBSurfaceEXT vkCreateDirectFBSurfaceEXT;
PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT vkGetPhysicalDeviceDirectFBPresentationSupportEXT;
#endif // defined(VK_EXT_directfb_surface)
#if defined(VK_EXT_discard_rectangles)
PFN_vkCmdSetDiscardRectangleEXT vkCmdSetDiscardRectangleEXT;
PFN_vkCmdSetDiscardRectangleEnableEXT vkCmdSetDiscardRectangleEnableEXT;
PFN_vkCmdSetDiscardRectangleModeEXT vkCmdSetDiscardRectangleModeEXT;
#endif // defined(VK_EXT_discard_rectangles)
#if defined(VK_EXT_display_control)
PFN_vkDisplayPowerControlEXT vkDisplayPowerControlEXT;
PFN_vkRegisterDeviceEventEXT vkRegisterDeviceEventEXT;
PFN_vkRegisterDisplayEventEXT vkRegisterDisplayEventEXT;
PFN_vkGetSwapchainCounterEXT vkGetSwapchainCounterEXT;
#endif // defined(VK_EXT_display_control)
#if defined(VK_EXT_display_surface_counter)
PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT vkGetPhysicalDeviceSurfaceCapabilities2EXT;
#endif // defined(VK_EXT_display_surface_counter)
#if defined(VK_EXT_external_memory_host)
PFN_vkGetMemoryHostPointerPropertiesEXT vkGetMemoryHostPointerPropertiesEXT;
#endif // defined(VK_EXT_external_memory_host)
#if defined(VK_EXT_full_screen_exclusive)
PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT vkGetPhysicalDeviceSurfacePresentModes2EXT;
PFN_vkAcquireFullScreenExclusiveModeEXT vkAcquireFullScreenExclusiveModeEXT;
PFN_vkReleaseFullScreenExclusiveModeEXT vkReleaseFullScreenExclusiveModeEXT;
#endif // defined(VK_EXT_full_screen_exclusive)
#if defined(VK_EXT_hdr_metadata)
PFN_vkSetHdrMetadataEXT vkSetHdrMetadataEXT;
#endif // defined(VK_EXT_hdr_metadata)
#if defined(VK_EXT_headless_surface)
PFN_vkCreateHeadlessSurfaceEXT vkCreateHeadlessSurfaceEXT;
#endif // defined(VK_EXT_headless_surface)
#if defined(VK_EXT_host_image_copy)
PFN_vkCopyMemoryToImageEXT vkCopyMemoryToImageEXT;
PFN_vkCopyImageToMemoryEXT vkCopyImageToMemoryEXT;
PFN_vkCopyImageToImageEXT vkCopyImageToImageEXT;
PFN_vkTransitionImageLayoutEXT vkTransitionImageLayoutEXT;
#endif // defined(VK_EXT_host_image_copy)
#if defined(VK_EXT_host_query_reset)
PFN_vkResetQueryPoolEXT vkResetQueryPoolEXT;
#endif // defined(VK_EXT_host_query_reset)
#if defined(VK_EXT_image_drm_format_modifier)
PFN_vkGetImageDrmFormatModifierPropertiesEXT vkGetImageDrmFormatModifierPropertiesEXT;
#endif // defined(VK_EXT_image_drm_format_modifier)
#if defined(VK_EXT_line_rasterization)
PFN_vkCmdSetLineStippleEXT vkCmdSetLineStippleEXT;
#endif // defined(VK_EXT_line_rasterization)
#if defined(VK_EXT_mesh_shader)
PFN_vkCmdDrawMeshTasksEXT vkCmdDrawMeshTasksEXT;
PFN_vkCmdDrawMeshTasksIndirectEXT vkCmdDrawMeshTasksIndirectEXT;
PFN_vkCmdDrawMeshTasksIndirectCountEXT vkCmdDrawMeshTasksIndirectCountEXT;
#endif // defined(VK_EXT_mesh_shader)
#if defined(VK_EXT_metal_objects)
PFN_vkExportMetalObjectsEXT vkExportMetalObjectsEXT;
#endif // defined(VK_EXT_metal_objects)
#if defined(VK_EXT_metal_surface)
PFN_vkCreateMetalSurfaceEXT vkCreateMetalSurfaceEXT;
#endif // defined(VK_EXT_metal_surface)
#if defined(VK_EXT_multi_draw)
PFN_vkCmdDrawMultiEXT vkCmdDrawMultiEXT;
PFN_vkCmdDrawMultiIndexedEXT vkCmdDrawMultiIndexedEXT;
#endif // defined(VK_EXT_multi_draw)
#if defined(VK_EXT_opacity_micromap)
PFN_vkCreateMicromapEXT vkCreateMicromapEXT;
PFN_vkDestroyMicromapEXT vkDestroyMicromapEXT;
PFN_vkCmdBuildMicromapsEXT vkCmdBuildMicromapsEXT;
PFN_vkBuildMicromapsEXT vkBuildMicromapsEXT;
PFN_vkCopyMicromapEXT vkCopyMicromapEXT;
PFN_vkCopyMicromapToMemoryEXT vkCopyMicromapToMemoryEXT;
PFN_vkCopyMemoryToMicromapEXT vkCopyMemoryToMicromapEXT;
PFN_vkWriteMicromapsPropertiesEXT vkWriteMicromapsPropertiesEXT;
PFN_vkCmdCopyMicromapEXT vkCmdCopyMicromapEXT;
PFN_vkCmdCopyMicromapToMemoryEXT vkCmdCopyMicromapToMemoryEXT;
PFN_vkCmdCopyMemoryToMicromapEXT vkCmdCopyMemoryToMicromapEXT;
PFN_vkCmdWriteMicromapsPropertiesEXT vkCmdWriteMicromapsPropertiesEXT;
PFN_vkGetDeviceMicromapCompatibilityEXT vkGetDeviceMicromapCompatibilityEXT;
PFN_vkGetMicromapBuildSizesEXT vkGetMicromapBuildSizesEXT;
#endif // defined(VK_EXT_opacity_micromap)
#if defined(VK_EXT_pageable_device_local_memory)
PFN_vkSetDeviceMemoryPriorityEXT vkSetDeviceMemoryPriorityEXT;
#endif // defined(VK_EXT_pageable_device_local_memory)
#if defined(VK_EXT_pipeline_properties)
PFN_vkGetPipelinePropertiesEXT vkGetPipelinePropertiesEXT;
#endif // defined(VK_EXT_pipeline_properties)
#if defined(VK_EXT_private_data)
PFN_vkCreatePrivateDataSlotEXT vkCreatePrivateDataSlotEXT;
PFN_vkDestroyPrivateDataSlotEXT vkDestroyPrivateDataSlotEXT;
PFN_vkSetPrivateDataEXT vkSetPrivateDataEXT;
PFN_vkGetPrivateDataEXT vkGetPrivateDataEXT;
#endif // defined(VK_EXT_private_data)
#if defined(VK_EXT_sample_locations)
PFN_vkCmdSetSampleLocationsEXT vkCmdSetSampleLocationsEXT;
PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT vkGetPhysicalDeviceMultisamplePropertiesEXT;
#endif // defined(VK_EXT_sample_locations)
#if defined(VK_EXT_shader_module_identifier)
PFN_vkGetShaderModuleIdentifierEXT vkGetShaderModuleIdentifierEXT;
PFN_vkGetShaderModuleCreateInfoIdentifierEXT vkGetShaderModuleCreateInfoIdentifierEXT;
#endif // defined(VK_EXT_shader_module_identifier)
#if defined(VK_EXT_shader_object)
PFN_vkCreateShadersEXT vkCreateShadersEXT;
PFN_vkDestroyShaderEXT vkDestroyShaderEXT;
PFN_vkGetShaderBinaryDataEXT vkGetShaderBinaryDataEXT;
PFN_vkCmdBindShadersEXT vkCmdBindShadersEXT;
#endif // defined(VK_EXT_shader_object)
#if defined(VK_EXT_swapchain_maintenance1)
PFN_vkReleaseSwapchainImagesEXT vkReleaseSwapchainImagesEXT;
#endif // defined(VK_EXT_swapchain_maintenance1)
#if defined(VK_EXT_tooling_info)
PFN_vkGetPhysicalDeviceToolPropertiesEXT vkGetPhysicalDeviceToolPropertiesEXT;
#endif // defined(VK_EXT_tooling_info)
#if defined(VK_EXT_transform_feedback)
PFN_vkCmdBindTransformFeedbackBuffersEXT vkCmdBindTransformFeedbackBuffersEXT;
PFN_vkCmdBeginTransformFeedbackEXT vkCmdBeginTransformFeedbackEXT;
PFN_vkCmdEndTransformFeedbackEXT vkCmdEndTransformFeedbackEXT;
PFN_vkCmdBeginQueryIndexedEXT vkCmdBeginQueryIndexedEXT;
PFN_vkCmdEndQueryIndexedEXT vkCmdEndQueryIndexedEXT;
PFN_vkCmdDrawIndirectByteCountEXT vkCmdDrawIndirectByteCountEXT;
#endif // defined(VK_EXT_transform_feedback)
#if defined(VK_EXT_validation_cache)
PFN_vkCreateValidationCacheEXT vkCreateValidationCacheEXT;
PFN_vkDestroyValidationCacheEXT vkDestroyValidationCacheEXT;
PFN_vkMergeValidationCachesEXT vkMergeValidationCachesEXT;
PFN_vkGetValidationCacheDataEXT vkGetValidationCacheDataEXT;
#endif // defined(VK_EXT_validation_cache)
#if defined(VK_FUCHSIA_buffer_collection)
PFN_vkCreateBufferCollectionFUCHSIA vkCreateBufferCollectionFUCHSIA;
PFN_vkSetBufferCollectionImageConstraintsFUCHSIA vkSetBufferCollectionImageConstraintsFUCHSIA;
PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA vkSetBufferCollectionBufferConstraintsFUCHSIA;
PFN_vkDestroyBufferCollectionFUCHSIA vkDestroyBufferCollectionFUCHSIA;
PFN_vkGetBufferCollectionPropertiesFUCHSIA vkGetBufferCollectionPropertiesFUCHSIA;
#endif // defined(VK_FUCHSIA_buffer_collection)
#if defined(VK_FUCHSIA_external_memory)
PFN_vkGetMemoryZirconHandleFUCHSIA vkGetMemoryZirconHandleFUCHSIA;
PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA vkGetMemoryZirconHandlePropertiesFUCHSIA;
#endif // defined(VK_FUCHSIA_external_memory)
#if defined(VK_FUCHSIA_external_semaphore)
PFN_vkImportSemaphoreZirconHandleFUCHSIA vkImportSemaphoreZirconHandleFUCHSIA;
PFN_vkGetSemaphoreZirconHandleFUCHSIA vkGetSemaphoreZirconHandleFUCHSIA;
#endif // defined(VK_FUCHSIA_external_semaphore)
#if defined(VK_FUCHSIA_imagepipe_surface)
PFN_vkCreateImagePipeSurfaceFUCHSIA vkCreateImagePipeSurfaceFUCHSIA;
#endif // defined(VK_FUCHSIA_imagepipe_surface)
#if defined(VK_GGP_stream_descriptor_surface)
PFN_vkCreateStreamDescriptorSurfaceGGP vkCreateStreamDescriptorSurfaceGGP;
#endif // defined(VK_GGP_stream_descriptor_surface)
#if defined(VK_GOOGLE_display_timing)
PFN_vkGetRefreshCycleDurationGOOGLE vkGetRefreshCycleDurationGOOGLE;
PFN_vkGetPastPresentationTimingGOOGLE vkGetPastPresentationTimingGOOGLE;
#endif // defined(VK_GOOGLE_display_timing)
#if defined(VK_HUAWEI_cluster_culling_shader)
PFN_vkCmdDrawClusterHUAWEI vkCmdDrawClusterHUAWEI;
PFN_vkCmdDrawClusterIndirectHUAWEI vkCmdDrawClusterIndirectHUAWEI;
#endif // defined(VK_HUAWEI_cluster_culling_shader)
#if defined(VK_HUAWEI_invocation_mask)
PFN_vkCmdBindInvocationMaskHUAWEI vkCmdBindInvocationMaskHUAWEI;
#endif // defined(VK_HUAWEI_invocation_mask)
#if defined(VK_HUAWEI_subpass_shading)
PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI;
PFN_vkCmdSubpassShadingHUAWEI vkCmdSubpassShadingHUAWEI;
#endif // defined(VK_HUAWEI_subpass_shading)
#if defined(VK_INTEL_performance_query)
PFN_vkInitializePerformanceApiINTEL vkInitializePerformanceApiINTEL;
PFN_vkUninitializePerformanceApiINTEL vkUninitializePerformanceApiINTEL;
PFN_vkCmdSetPerformanceMarkerINTEL vkCmdSetPerformanceMarkerINTEL;
PFN_vkCmdSetPerformanceStreamMarkerINTEL vkCmdSetPerformanceStreamMarkerINTEL;
PFN_vkCmdSetPerformanceOverrideINTEL vkCmdSetPerformanceOverrideINTEL;
PFN_vkAcquirePerformanceConfigurationINTEL vkAcquirePerformanceConfigurationINTEL;
PFN_vkReleasePerformanceConfigurationINTEL vkReleasePerformanceConfigurationINTEL;
PFN_vkQueueSetPerformanceConfigurationINTEL vkQueueSetPerformanceConfigurationINTEL;
PFN_vkGetPerformanceParameterINTEL vkGetPerformanceParameterINTEL;
#endif // defined(VK_INTEL_performance_query)
#if defined(VK_KHR_acceleration_structure)
PFN_vkCreateAccelerationStructureKHR vkCreateAccelerationStructureKHR;
PFN_vkDestroyAccelerationStructureKHR vkDestroyAccelerationStructureKHR;
PFN_vkCmdBuildAccelerationStructuresKHR vkCmdBuildAccelerationStructuresKHR;
PFN_vkCmdBuildAccelerationStructuresIndirectKHR vkCmdBuildAccelerationStructuresIndirectKHR;
PFN_vkBuildAccelerationStructuresKHR vkBuildAccelerationStructuresKHR;
PFN_vkCopyAccelerationStructureKHR vkCopyAccelerationStructureKHR;
PFN_vkCopyAccelerationStructureToMemoryKHR vkCopyAccelerationStructureToMemoryKHR;
PFN_vkCopyMemoryToAccelerationStructureKHR vkCopyMemoryToAccelerationStructureKHR;
PFN_vkWriteAccelerationStructuresPropertiesKHR vkWriteAccelerationStructuresPropertiesKHR;
PFN_vkCmdCopyAccelerationStructureKHR vkCmdCopyAccelerationStructureKHR;
PFN_vkCmdCopyAccelerationStructureToMemoryKHR vkCmdCopyAccelerationStructureToMemoryKHR;
PFN_vkCmdCopyMemoryToAccelerationStructureKHR vkCmdCopyMemoryToAccelerationStructureKHR;
PFN_vkGetAccelerationStructureDeviceAddressKHR vkGetAccelerationStructureDeviceAddressKHR;
PFN_vkCmdWriteAccelerationStructuresPropertiesKHR vkCmdWriteAccelerationStructuresPropertiesKHR;
PFN_vkGetDeviceAccelerationStructureCompatibilityKHR vkGetDeviceAccelerationStructureCompatibilityKHR;
PFN_vkGetAccelerationStructureBuildSizesKHR vkGetAccelerationStructureBuildSizesKHR;
#endif // defined(VK_KHR_acceleration_structure)
#if defined(VK_KHR_android_surface)
PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR;
#endif // defined(VK_KHR_android_surface)
#if defined(VK_KHR_bind_memory2)
PFN_vkBindBufferMemory2KHR vkBindBufferMemory2KHR;
PFN_vkBindImageMemory2KHR vkBindImageMemory2KHR;
#endif // defined(VK_KHR_bind_memory2)
#if defined(VK_KHR_buffer_device_address)
PFN_vkGetBufferDeviceAddressKHR vkGetBufferDeviceAddressKHR;
PFN_vkGetBufferOpaqueCaptureAddressKHR vkGetBufferOpaqueCaptureAddressKHR;
PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR vkGetDeviceMemoryOpaqueCaptureAddressKHR;
#endif // defined(VK_KHR_buffer_device_address)
#if defined(VK_KHR_calibrated_timestamps)
PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR vkGetPhysicalDeviceCalibrateableTimeDomainsKHR;
PFN_vkGetCalibratedTimestampsKHR vkGetCalibratedTimestampsKHR;
#endif // defined(VK_KHR_calibrated_timestamps)
#if defined(VK_KHR_cooperative_matrix)
PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR;
#endif // defined(VK_KHR_cooperative_matrix)
#if defined(VK_KHR_copy_commands2)
PFN_vkCmdCopyBuffer2KHR vkCmdCopyBuffer2KHR;
PFN_vkCmdCopyImage2KHR vkCmdCopyImage2KHR;
PFN_vkCmdCopyBufferToImage2KHR vkCmdCopyBufferToImage2KHR;
PFN_vkCmdCopyImageToBuffer2KHR vkCmdCopyImageToBuffer2KHR;
PFN_vkCmdBlitImage2KHR vkCmdBlitImage2KHR;
PFN_vkCmdResolveImage2KHR vkCmdResolveImage2KHR;
#endif // defined(VK_KHR_copy_commands2)
#if defined(VK_KHR_create_renderpass2)
PFN_vkCreateRenderPass2KHR vkCreateRenderPass2KHR;
PFN_vkCmdBeginRenderPass2KHR vkCmdBeginRenderPass2KHR;
PFN_vkCmdNextSubpass2KHR vkCmdNextSubpass2KHR;
PFN_vkCmdEndRenderPass2KHR vkCmdEndRenderPass2KHR;
#endif // defined(VK_KHR_create_renderpass2)
#if defined(VK_KHR_deferred_host_operations)
PFN_vkCreateDeferredOperationKHR vkCreateDeferredOperationKHR;
PFN_vkDestroyDeferredOperationKHR vkDestroyDeferredOperationKHR;
PFN_vkGetDeferredOperationMaxConcurrencyKHR vkGetDeferredOperationMaxConcurrencyKHR;
PFN_vkGetDeferredOperationResultKHR vkGetDeferredOperationResultKHR;
PFN_vkDeferredOperationJoinKHR vkDeferredOperationJoinKHR;
#endif // defined(VK_KHR_deferred_host_operations)
#if defined(VK_KHR_descriptor_update_template)
PFN_vkCreateDescriptorUpdateTemplateKHR vkCreateDescriptorUpdateTemplateKHR;
PFN_vkDestroyDescriptorUpdateTemplateKHR vkDestroyDescriptorUpdateTemplateKHR;
PFN_vkUpdateDescriptorSetWithTemplateKHR vkUpdateDescriptorSetWithTemplateKHR;
#endif // defined(VK_KHR_descriptor_update_template)
#if defined(VK_KHR_device_group)
PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR vkGetDeviceGroupPeerMemoryFeaturesKHR;
PFN_vkCmdSetDeviceMaskKHR vkCmdSetDeviceMaskKHR;
PFN_vkCmdDispatchBaseKHR vkCmdDispatchBaseKHR;
#endif // defined(VK_KHR_device_group)
#if defined(VK_KHR_device_group_creation)
PFN_vkEnumeratePhysicalDeviceGroupsKHR vkEnumeratePhysicalDeviceGroupsKHR;
#endif // defined(VK_KHR_device_group_creation)
#if defined(VK_KHR_display)
PFN_vkGetPhysicalDeviceDisplayPropertiesKHR vkGetPhysicalDeviceDisplayPropertiesKHR;
PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR vkGetPhysicalDeviceDisplayPlanePropertiesKHR;
PFN_vkGetDisplayPlaneSupportedDisplaysKHR vkGetDisplayPlaneSupportedDisplaysKHR;
PFN_vkGetDisplayModePropertiesKHR vkGetDisplayModePropertiesKHR;
PFN_vkCreateDisplayModeKHR vkCreateDisplayModeKHR;
PFN_vkGetDisplayPlaneCapabilitiesKHR vkGetDisplayPlaneCapabilitiesKHR;
PFN_vkCreateDisplayPlaneSurfaceKHR vkCreateDisplayPlaneSurfaceKHR;
#endif // defined(VK_KHR_display)
#if defined(VK_KHR_display_swapchain)
PFN_vkCreateSharedSwapchainsKHR vkCreateSharedSwapchainsKHR;
#endif // defined(VK_KHR_display_swapchain)
#if defined(VK_KHR_draw_indirect_count)
PFN_vkCmdDrawIndirectCountKHR vkCmdDrawIndirectCountKHR;
PFN_vkCmdDrawIndexedIndirectCountKHR vkCmdDrawIndexedIndirectCountKHR;
#endif // defined(VK_KHR_draw_indirect_count)
#if defined(VK_KHR_dynamic_rendering)
PFN_vkCmdBeginRenderingKHR vkCmdBeginRenderingKHR;
PFN_vkCmdEndRenderingKHR vkCmdEndRenderingKHR;
#endif // defined(VK_KHR_dynamic_rendering)
#if defined(VK_KHR_dynamic_rendering_local_read)
PFN_vkCmdSetRenderingAttachmentLocationsKHR vkCmdSetRenderingAttachmentLocationsKHR;
PFN_vkCmdSetRenderingInputAttachmentIndicesKHR vkCmdSetRenderingInputAttachmentIndicesKHR;
#endif // defined(VK_KHR_dynamic_rendering_local_read)
#if defined(VK_KHR_external_fence_capabilities)
PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR vkGetPhysicalDeviceExternalFencePropertiesKHR;
#endif // defined(VK_KHR_external_fence_capabilities)
#if defined(VK_KHR_external_fence_fd)
PFN_vkImportFenceFdKHR vkImportFenceFdKHR;
PFN_vkGetFenceFdKHR vkGetFenceFdKHR;
#endif // defined(VK_KHR_external_fence_fd)
#if defined(VK_KHR_external_fence_win32)
PFN_vkImportFenceWin32HandleKHR vkImportFenceWin32HandleKHR;
PFN_vkGetFenceWin32HandleKHR vkGetFenceWin32HandleKHR;
#endif // defined(VK_KHR_external_fence_win32)
#if defined(VK_KHR_external_memory_capabilities)
PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR vkGetPhysicalDeviceExternalBufferPropertiesKHR;
#endif // defined(VK_KHR_external_memory_capabilities)
#if defined(VK_KHR_external_memory_fd)
PFN_vkGetMemoryFdKHR vkGetMemoryFdKHR;
PFN_vkGetMemoryFdPropertiesKHR vkGetMemoryFdPropertiesKHR;
#endif // defined(VK_KHR_external_memory_fd)
#if defined(VK_KHR_external_memory_win32)
PFN_vkGetMemoryWin32HandleKHR vkGetMemoryWin32HandleKHR;
PFN_vkGetMemoryWin32HandlePropertiesKHR vkGetMemoryWin32HandlePropertiesKHR;
#endif // defined(VK_KHR_external_memory_win32)
#if defined(VK_KHR_external_semaphore_capabilities)
PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR vkGetPhysicalDeviceExternalSemaphorePropertiesKHR;
#endif // defined(VK_KHR_external_semaphore_capabilities)
#if defined(VK_KHR_external_semaphore_fd)
PFN_vkImportSemaphoreFdKHR vkImportSemaphoreFdKHR;
PFN_vkGetSemaphoreFdKHR vkGetSemaphoreFdKHR;
#endif // defined(VK_KHR_external_semaphore_fd)
#if defined(VK_KHR_external_semaphore_win32)
PFN_vkImportSemaphoreWin32HandleKHR vkImportSemaphoreWin32HandleKHR;
PFN_vkGetSemaphoreWin32HandleKHR vkGetSemaphoreWin32HandleKHR;
#endif // defined(VK_KHR_external_semaphore_win32)
#if defined(VK_KHR_fragment_shading_rate)
PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR vkGetPhysicalDeviceFragmentShadingRatesKHR;
PFN_vkCmdSetFragmentShadingRateKHR vkCmdSetFragmentShadingRateKHR;
#endif // defined(VK_KHR_fragment_shading_rate)
#if defined(VK_KHR_get_display_properties2)
PFN_vkGetPhysicalDeviceDisplayProperties2KHR vkGetPhysicalDeviceDisplayProperties2KHR;
PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR vkGetPhysicalDeviceDisplayPlaneProperties2KHR;
PFN_vkGetDisplayModeProperties2KHR vkGetDisplayModeProperties2KHR;
PFN_vkGetDisplayPlaneCapabilities2KHR vkGetDisplayPlaneCapabilities2KHR;
#endif // defined(VK_KHR_get_display_properties2)
#if defined(VK_KHR_get_memory_requirements2)
PFN_vkGetImageMemoryRequirements2KHR vkGetImageMemoryRequirements2KHR;
PFN_vkGetBufferMemoryRequirements2KHR vkGetBufferMemoryRequirements2KHR;
PFN_vkGetImageSparseMemoryRequirements2KHR vkGetImageSparseMemoryRequirements2KHR;
#endif // defined(VK_KHR_get_memory_requirements2)
#if defined(VK_KHR_get_physical_device_properties2)
PFN_vkGetPhysicalDeviceFeatures2KHR vkGetPhysicalDeviceFeatures2KHR;
PFN_vkGetPhysicalDeviceProperties2KHR vkGetPhysicalDeviceProperties2KHR;
PFN_vkGetPhysicalDeviceFormatProperties2KHR vkGetPhysicalDeviceFormatProperties2KHR;
PFN_vkGetPhysicalDeviceImageFormatProperties2KHR vkGetPhysicalDeviceImageFormatProperties2KHR;
PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR vkGetPhysicalDeviceQueueFamilyProperties2KHR;
PFN_vkGetPhysicalDeviceMemoryProperties2KHR vkGetPhysicalDeviceMemoryProperties2KHR;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR vkGetPhysicalDeviceSparseImageFormatProperties2KHR;
#endif // defined(VK_KHR_get_physical_device_properties2)
#if defined(VK_KHR_get_surface_capabilities2)
PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR vkGetPhysicalDeviceSurfaceCapabilities2KHR;
PFN_vkGetPhysicalDeviceSurfaceFormats2KHR vkGetPhysicalDeviceSurfaceFormats2KHR;
#endif // defined(VK_KHR_get_surface_capabilities2)
#if defined(VK_KHR_line_rasterization)
PFN_vkCmdSetLineStippleKHR vkCmdSetLineStippleKHR;
#endif // defined(VK_KHR_line_rasterization)
#if defined(VK_KHR_maintenance1)
PFN_vkTrimCommandPoolKHR vkTrimCommandPoolKHR;
#endif // defined(VK_KHR_maintenance1)
#if defined(VK_KHR_maintenance3)
PFN_vkGetDescriptorSetLayoutSupportKHR vkGetDescriptorSetLayoutSupportKHR;
#endif // defined(VK_KHR_maintenance3)
#if defined(VK_KHR_maintenance4)
PFN_vkGetDeviceBufferMemoryRequirementsKHR vkGetDeviceBufferMemoryRequirementsKHR;
PFN_vkGetDeviceImageMemoryRequirementsKHR vkGetDeviceImageMemoryRequirementsKHR;
PFN_vkGetDeviceImageSparseMemoryRequirementsKHR vkGetDeviceImageSparseMemoryRequirementsKHR;
#endif // defined(VK_KHR_maintenance4)
#if defined(VK_KHR_maintenance5)
PFN_vkCmdBindIndexBuffer2KHR vkCmdBindIndexBuffer2KHR;
PFN_vkGetRenderingAreaGranularityKHR vkGetRenderingAreaGranularityKHR;
PFN_vkGetDeviceImageSubresourceLayoutKHR vkGetDeviceImageSubresourceLayoutKHR;
PFN_vkGetImageSubresourceLayout2KHR vkGetImageSubresourceLayout2KHR;
#endif // defined(VK_KHR_maintenance5)
#if defined(VK_KHR_maintenance6)
PFN_vkCmdBindDescriptorSets2KHR vkCmdBindDescriptorSets2KHR;
PFN_vkCmdPushConstants2KHR vkCmdPushConstants2KHR;
#endif // defined(VK_KHR_maintenance6)
#if defined(VK_KHR_maintenance6) && defined(VK_KHR_push_descriptor)
PFN_vkCmdPushDescriptorSet2KHR vkCmdPushDescriptorSet2KHR;
PFN_vkCmdPushDescriptorSetWithTemplate2KHR vkCmdPushDescriptorSetWithTemplate2KHR;
#endif // defined(VK_KHR_maintenance6) && defined(VK_KHR_push_descriptor)
#if defined(VK_KHR_maintenance6) && defined(VK_EXT_descriptor_buffer)
PFN_vkCmdSetDescriptorBufferOffsets2EXT vkCmdSetDescriptorBufferOffsets2EXT;
PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT vkCmdBindDescriptorBufferEmbeddedSamplers2EXT;
#endif // defined(VK_KHR_maintenance6) && defined(VK_EXT_descriptor_buffer)
#if defined(VK_KHR_map_memory2)
PFN_vkMapMemory2KHR vkMapMemory2KHR;
PFN_vkUnmapMemory2KHR vkUnmapMemory2KHR;
#endif // defined(VK_KHR_map_memory2)
#if defined(VK_KHR_performance_query)
PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
PFN_vkAcquireProfilingLockKHR vkAcquireProfilingLockKHR;
PFN_vkReleaseProfilingLockKHR vkReleaseProfilingLockKHR;
#endif // defined(VK_KHR_performance_query)
#if defined(VK_KHR_pipeline_executable_properties)
PFN_vkGetPipelineExecutablePropertiesKHR vkGetPipelineExecutablePropertiesKHR;
PFN_vkGetPipelineExecutableStatisticsKHR vkGetPipelineExecutableStatisticsKHR;
PFN_vkGetPipelineExecutableInternalRepresentationsKHR vkGetPipelineExecutableInternalRepresentationsKHR;
#endif // defined(VK_KHR_pipeline_executable_properties)
#if defined(VK_KHR_present_wait)
PFN_vkWaitForPresentKHR vkWaitForPresentKHR;
#endif // defined(VK_KHR_present_wait)
#if defined(VK_KHR_push_descriptor)
PFN_vkCmdPushDescriptorSetKHR vkCmdPushDescriptorSetKHR;
#endif // defined(VK_KHR_push_descriptor)
#if defined(VK_KHR_ray_tracing_maintenance1) && defined(VK_KHR_ray_tracing_pipeline)
PFN_vkCmdTraceRaysIndirect2KHR vkCmdTraceRaysIndirect2KHR;
#endif // defined(VK_KHR_ray_tracing_maintenance1) && defined(VK_KHR_ray_tracing_pipeline)
#if defined(VK_KHR_ray_tracing_pipeline)
PFN_vkCmdTraceRaysKHR vkCmdTraceRaysKHR;
PFN_vkCreateRayTracingPipelinesKHR vkCreateRayTracingPipelinesKHR;
PFN_vkGetRayTracingShaderGroupHandlesKHR vkGetRayTracingShaderGroupHandlesKHR;
PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR vkGetRayTracingCaptureReplayShaderGroupHandlesKHR;
PFN_vkCmdTraceRaysIndirectKHR vkCmdTraceRaysIndirectKHR;
PFN_vkGetRayTracingShaderGroupStackSizeKHR vkGetRayTracingShaderGroupStackSizeKHR;
PFN_vkCmdSetRayTracingPipelineStackSizeKHR vkCmdSetRayTracingPipelineStackSizeKHR;
#endif // defined(VK_KHR_ray_tracing_pipeline)
#if defined(VK_KHR_sampler_ycbcr_conversion)
PFN_vkCreateSamplerYcbcrConversionKHR vkCreateSamplerYcbcrConversionKHR;
PFN_vkDestroySamplerYcbcrConversionKHR vkDestroySamplerYcbcrConversionKHR;
#endif // defined(VK_KHR_sampler_ycbcr_conversion)
#if defined(VK_KHR_shared_presentable_image)
PFN_vkGetSwapchainStatusKHR vkGetSwapchainStatusKHR;
#endif // defined(VK_KHR_shared_presentable_image)
#if defined(VK_KHR_surface)
PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;
PFN_vkGetPhysicalDeviceSurfaceSupportKHR vkGetPhysicalDeviceSurfaceSupportKHR;
PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vkGetPhysicalDeviceSurfaceFormatsKHR;
PFN_vkGetPhysicalDeviceSurfacePresentModesKHR vkGetPhysicalDeviceSurfacePresentModesKHR;
#endif // defined(VK_KHR_surface)
#if defined(VK_KHR_swapchain)
PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR;
PFN_vkDestroySwapchainKHR vkDestroySwapchainKHR;
PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR;
PFN_vkAcquireNextImageKHR vkAcquireNextImageKHR;
PFN_vkQueuePresentKHR vkQueuePresentKHR;
#endif // defined(VK_KHR_swapchain)
#if defined(VK_KHR_synchronization2)
PFN_vkCmdSetEvent2KHR vkCmdSetEvent2KHR;
PFN_vkCmdResetEvent2KHR vkCmdResetEvent2KHR;
PFN_vkCmdWaitEvents2KHR vkCmdWaitEvents2KHR;
PFN_vkCmdPipelineBarrier2KHR vkCmdPipelineBarrier2KHR;
PFN_vkCmdWriteTimestamp2KHR vkCmdWriteTimestamp2KHR;
PFN_vkQueueSubmit2KHR vkQueueSubmit2KHR;
#endif // defined(VK_KHR_synchronization2)
#if defined(VK_KHR_synchronization2) && defined(VK_AMD_buffer_marker)
PFN_vkCmdWriteBufferMarker2AMD vkCmdWriteBufferMarker2AMD;
#endif // defined(VK_KHR_synchronization2) && defined(VK_AMD_buffer_marker)
#if defined(VK_KHR_synchronization2) && defined(VK_NV_device_diagnostic_checkpoints)
PFN_vkGetQueueCheckpointData2NV vkGetQueueCheckpointData2NV;
#endif // defined(VK_KHR_synchronization2) && defined(VK_NV_device_diagnostic_checkpoints)
#if defined(VK_KHR_timeline_semaphore)
PFN_vkGetSemaphoreCounterValueKHR vkGetSemaphoreCounterValueKHR;
PFN_vkWaitSemaphoresKHR vkWaitSemaphoresKHR;
PFN_vkSignalSemaphoreKHR vkSignalSemaphoreKHR;
#endif // defined(VK_KHR_timeline_semaphore)
#if defined(VK_KHR_video_decode_queue)
PFN_vkCmdDecodeVideoKHR vkCmdDecodeVideoKHR;
#endif // defined(VK_KHR_video_decode_queue)
#if defined(VK_KHR_video_encode_queue)
PFN_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR;
PFN_vkGetEncodedVideoSessionParametersKHR vkGetEncodedVideoSessionParametersKHR;
PFN_vkCmdEncodeVideoKHR vkCmdEncodeVideoKHR;
#endif // defined(VK_KHR_video_encode_queue)
#if defined(VK_KHR_video_queue)
PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR vkGetPhysicalDeviceVideoCapabilitiesKHR;
PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR vkGetPhysicalDeviceVideoFormatPropertiesKHR;
PFN_vkCreateVideoSessionKHR vkCreateVideoSessionKHR;
PFN_vkDestroyVideoSessionKHR vkDestroyVideoSessionKHR;
PFN_vkGetVideoSessionMemoryRequirementsKHR vkGetVideoSessionMemoryRequirementsKHR;
PFN_vkBindVideoSessionMemoryKHR vkBindVideoSessionMemoryKHR;
PFN_vkCreateVideoSessionParametersKHR vkCreateVideoSessionParametersKHR;
PFN_vkUpdateVideoSessionParametersKHR vkUpdateVideoSessionParametersKHR;
PFN_vkDestroyVideoSessionParametersKHR vkDestroyVideoSessionParametersKHR;
PFN_vkCmdBeginVideoCodingKHR vkCmdBeginVideoCodingKHR;
PFN_vkCmdEndVideoCodingKHR vkCmdEndVideoCodingKHR;
PFN_vkCmdControlVideoCodingKHR vkCmdControlVideoCodingKHR;
#endif // defined(VK_KHR_video_queue)
#if defined(VK_KHR_wayland_surface)
PFN_vkCreateWaylandSurfaceKHR vkCreateWaylandSurfaceKHR;
PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR vkGetPhysicalDeviceWaylandPresentationSupportKHR;
#endif // defined(VK_KHR_wayland_surface)
#if defined(VK_KHR_win32_surface)
PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR;
PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR;
#endif // defined(VK_KHR_win32_surface)
#if defined(VK_KHR_xcb_surface)
PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR;
PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR;
#endif // defined(VK_KHR_xcb_surface)
#if defined(VK_KHR_xlib_surface)
PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR;
PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR;
#endif // defined(VK_KHR_xlib_surface)
#if defined(VK_MVK_ios_surface)
PFN_vkCreateIOSSurfaceMVK vkCreateIOSSurfaceMVK;
#endif // defined(VK_MVK_ios_surface)
#if defined(VK_MVK_macos_surface)
PFN_vkCreateMacOSSurfaceMVK vkCreateMacOSSurfaceMVK;
#endif // defined(VK_MVK_macos_surface)
#if defined(VK_NN_vi_surface)
PFN_vkCreateViSurfaceNN vkCreateViSurfaceNN;
#endif // defined(VK_NN_vi_surface)
#if defined(VK_NV_acquire_winrt_display)
PFN_vkAcquireWinrtDisplayNV vkAcquireWinrtDisplayNV;
PFN_vkGetWinrtDisplayNV vkGetWinrtDisplayNV;
#endif // defined(VK_NV_acquire_winrt_display)
#if defined(VK_NV_clip_space_w_scaling)
PFN_vkCmdSetViewportWScalingNV vkCmdSetViewportWScalingNV;
#endif // defined(VK_NV_clip_space_w_scaling)
#if defined(VK_NV_cooperative_matrix)
PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV vkGetPhysicalDeviceCooperativeMatrixPropertiesNV;
#endif // defined(VK_NV_cooperative_matrix)
#if defined(VK_NV_copy_memory_indirect)
PFN_vkCmdCopyMemoryIndirectNV vkCmdCopyMemoryIndirectNV;
PFN_vkCmdCopyMemoryToImageIndirectNV vkCmdCopyMemoryToImageIndirectNV;
#endif // defined(VK_NV_copy_memory_indirect)
#if defined(VK_NV_coverage_reduction_mode)
PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV;
#endif // defined(VK_NV_coverage_reduction_mode)
#if defined(VK_NV_cuda_kernel_launch)
PFN_vkCreateCudaModuleNV vkCreateCudaModuleNV;
PFN_vkGetCudaModuleCacheNV vkGetCudaModuleCacheNV;
PFN_vkCreateCudaFunctionNV vkCreateCudaFunctionNV;
PFN_vkDestroyCudaModuleNV vkDestroyCudaModuleNV;
PFN_vkDestroyCudaFunctionNV vkDestroyCudaFunctionNV;
PFN_vkCmdCudaLaunchKernelNV vkCmdCudaLaunchKernelNV;
#endif // defined(VK_NV_cuda_kernel_launch)
#if defined(VK_NV_device_diagnostic_checkpoints)
PFN_vkCmdSetCheckpointNV vkCmdSetCheckpointNV;
PFN_vkGetQueueCheckpointDataNV vkGetQueueCheckpointDataNV;
#endif // defined(VK_NV_device_diagnostic_checkpoints)
#if defined(VK_NV_device_generated_commands)
PFN_vkGetGeneratedCommandsMemoryRequirementsNV vkGetGeneratedCommandsMemoryRequirementsNV;
PFN_vkCmdPreprocessGeneratedCommandsNV vkCmdPreprocessGeneratedCommandsNV;
PFN_vkCmdExecuteGeneratedCommandsNV vkCmdExecuteGeneratedCommandsNV;
PFN_vkCmdBindPipelineShaderGroupNV vkCmdBindPipelineShaderGroupNV;
PFN_vkCreateIndirectCommandsLayoutNV vkCreateIndirectCommandsLayoutNV;
PFN_vkDestroyIndirectCommandsLayoutNV vkDestroyIndirectCommandsLayoutNV;
#endif // defined(VK_NV_device_generated_commands)
#if defined(VK_NV_device_generated_commands_compute)
PFN_vkGetPipelineIndirectMemoryRequirementsNV vkGetPipelineIndirectMemoryRequirementsNV;
PFN_vkCmdUpdatePipelineIndirectBufferNV vkCmdUpdatePipelineIndirectBufferNV;
PFN_vkGetPipelineIndirectDeviceAddressNV vkGetPipelineIndirectDeviceAddressNV;
#endif // defined(VK_NV_device_generated_commands_compute)
#if defined(VK_NV_external_memory_capabilities)
PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV vkGetPhysicalDeviceExternalImageFormatPropertiesNV;
#endif // defined(VK_NV_external_memory_capabilities)
#if defined(VK_NV_external_memory_rdma)
PFN_vkGetMemoryRemoteAddressNV vkGetMemoryRemoteAddressNV;
#endif // defined(VK_NV_external_memory_rdma)
#if defined(VK_NV_external_memory_win32)
PFN_vkGetMemoryWin32HandleNV vkGetMemoryWin32HandleNV;
#endif // defined(VK_NV_external_memory_win32)
#if defined(VK_NV_fragment_shading_rate_enums)
PFN_vkCmdSetFragmentShadingRateEnumNV vkCmdSetFragmentShadingRateEnumNV;
#endif // defined(VK_NV_fragment_shading_rate_enums)
#if defined(VK_NV_low_latency2)
PFN_vkSetLatencySleepModeNV vkSetLatencySleepModeNV;
PFN_vkLatencySleepNV vkLatencySleepNV;
PFN_vkSetLatencyMarkerNV vkSetLatencyMarkerNV;
PFN_vkGetLatencyTimingsNV vkGetLatencyTimingsNV;
PFN_vkQueueNotifyOutOfBandNV vkQueueNotifyOutOfBandNV;
#endif // defined(VK_NV_low_latency2)
#if defined(VK_NV_memory_decompression)
PFN_vkCmdDecompressMemoryNV vkCmdDecompressMemoryNV;
PFN_vkCmdDecompressMemoryIndirectCountNV vkCmdDecompressMemoryIndirectCountNV;
#endif // defined(VK_NV_memory_decompression)
#if defined(VK_NV_mesh_shader)
PFN_vkCmdDrawMeshTasksNV vkCmdDrawMeshTasksNV;
PFN_vkCmdDrawMeshTasksIndirectNV vkCmdDrawMeshTasksIndirectNV;
PFN_vkCmdDrawMeshTasksIndirectCountNV vkCmdDrawMeshTasksIndirectCountNV;
#endif // defined(VK_NV_mesh_shader)
#if defined(VK_NV_optical_flow)
PFN_vkGetPhysicalDeviceOpticalFlowImageFormatsNV vkGetPhysicalDeviceOpticalFlowImageFormatsNV;
PFN_vkCreateOpticalFlowSessionNV vkCreateOpticalFlowSessionNV;
PFN_vkDestroyOpticalFlowSessionNV vkDestroyOpticalFlowSessionNV;
PFN_vkBindOpticalFlowSessionImageNV vkBindOpticalFlowSessionImageNV;
PFN_vkCmdOpticalFlowExecuteNV vkCmdOpticalFlowExecuteNV;
#endif // defined(VK_NV_optical_flow)
#if defined(VK_NV_ray_tracing)
PFN_vkCreateAccelerationStructureNV vkCreateAccelerationStructureNV;
PFN_vkDestroyAccelerationStructureNV vkDestroyAccelerationStructureNV;
PFN_vkGetAccelerationStructureMemoryRequirementsNV vkGetAccelerationStructureMemoryRequirementsNV;
PFN_vkBindAccelerationStructureMemoryNV vkBindAccelerationStructureMemoryNV;
PFN_vkCmdBuildAccelerationStructureNV vkCmdBuildAccelerationStructureNV;
PFN_vkCmdCopyAccelerationStructureNV vkCmdCopyAccelerationStructureNV;
PFN_vkCmdTraceRaysNV vkCmdTraceRaysNV;
PFN_vkCreateRayTracingPipelinesNV vkCreateRayTracingPipelinesNV;
PFN_vkGetRayTracingShaderGroupHandlesNV vkGetRayTracingShaderGroupHandlesNV;
PFN_vkGetAccelerationStructureHandleNV vkGetAccelerationStructureHandleNV;
PFN_vkCmdWriteAccelerationStructuresPropertiesNV vkCmdWriteAccelerationStructuresPropertiesNV;
PFN_vkCompileDeferredNV vkCompileDeferredNV;
#endif // defined(VK_NV_ray_tracing)
#if defined(VK_NV_scissor_exclusive)
PFN_vkCmdSetExclusiveScissorEnableNV vkCmdSetExclusiveScissorEnableNV;
PFN_vkCmdSetExclusiveScissorNV vkCmdSetExclusiveScissorNV;
#endif // defined(VK_NV_scissor_exclusive)
#if defined(VK_NV_shading_rate_image)
PFN_vkCmdBindShadingRateImageNV vkCmdBindShadingRateImageNV;
PFN_vkCmdSetViewportShadingRatePaletteNV vkCmdSetViewportShadingRatePaletteNV;
PFN_vkCmdSetCoarseSampleOrderNV vkCmdSetCoarseSampleOrderNV;
#endif // defined(VK_NV_shading_rate_image)
#if defined(VK_NVX_binary_import)
PFN_vkCreateCuModuleNVX vkCreateCuModuleNVX;
PFN_vkCreateCuFunctionNVX vkCreateCuFunctionNVX;
PFN_vkDestroyCuModuleNVX vkDestroyCuModuleNVX;
PFN_vkDestroyCuFunctionNVX vkDestroyCuFunctionNVX;
PFN_vkCmdCuLaunchKernelNVX vkCmdCuLaunchKernelNVX;
#endif // defined(VK_NVX_binary_import)
#if defined(VK_NVX_image_view_handle)
PFN_vkGetImageViewHandleNVX vkGetImageViewHandleNVX;
PFN_vkGetImageViewAddressNVX vkGetImageViewAddressNVX;
#endif // defined(VK_NVX_image_view_handle)
#if defined(VK_QCOM_tile_properties)
PFN_vkGetFramebufferTilePropertiesQCOM vkGetFramebufferTilePropertiesQCOM;
PFN_vkGetDynamicRenderingTilePropertiesQCOM vkGetDynamicRenderingTilePropertiesQCOM;
#endif // defined(VK_QCOM_tile_properties)
#if defined(VK_QNX_external_memory_screen_buffer)
PFN_vkGetScreenBufferPropertiesQNX vkGetScreenBufferPropertiesQNX;
#endif // defined(VK_QNX_external_memory_screen_buffer)
#if defined(VK_QNX_screen_surface)
PFN_vkCreateScreenSurfaceQNX vkCreateScreenSurfaceQNX;
PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX vkGetPhysicalDeviceScreenPresentationSupportQNX;
#endif // defined(VK_QNX_screen_surface)
#if defined(VK_VALVE_descriptor_set_host_mapping)
PFN_vkGetDescriptorSetLayoutHostMappingInfoVALVE vkGetDescriptorSetLayoutHostMappingInfoVALVE;
PFN_vkGetDescriptorSetHostMappingVALVE vkGetDescriptorSetHostMappingVALVE;
#endif // defined(VK_VALVE_descriptor_set_host_mapping)
#if defined(VK_EXT_extended_dynamic_state) || (defined(VK_EXT_shader_object))
PFN_vkCmdSetCullModeEXT vkCmdSetCullModeEXT;
PFN_vkCmdSetFrontFaceEXT vkCmdSetFrontFaceEXT;
PFN_vkCmdSetPrimitiveTopologyEXT vkCmdSetPrimitiveTopologyEXT;
PFN_vkCmdSetViewportWithCountEXT vkCmdSetViewportWithCountEXT;
PFN_vkCmdSetScissorWithCountEXT vkCmdSetScissorWithCountEXT;
PFN_vkCmdBindVertexBuffers2EXT vkCmdBindVertexBuffers2EXT;
PFN_vkCmdSetDepthTestEnableEXT vkCmdSetDepthTestEnableEXT;
PFN_vkCmdSetDepthWriteEnableEXT vkCmdSetDepthWriteEnableEXT;
PFN_vkCmdSetDepthCompareOpEXT vkCmdSetDepthCompareOpEXT;
PFN_vkCmdSetDepthBoundsTestEnableEXT vkCmdSetDepthBoundsTestEnableEXT;
PFN_vkCmdSetStencilTestEnableEXT vkCmdSetStencilTestEnableEXT;
PFN_vkCmdSetStencilOpEXT vkCmdSetStencilOpEXT;
#endif // defined(VK_EXT_extended_dynamic_state) || (defined(VK_EXT_shader_object))
#if defined(VK_EXT_extended_dynamic_state2) || (defined(VK_EXT_shader_object))
PFN_vkCmdSetPatchControlPointsEXT vkCmdSetPatchControlPointsEXT;
PFN_vkCmdSetRasterizerDiscardEnableEXT vkCmdSetRasterizerDiscardEnableEXT;
PFN_vkCmdSetDepthBiasEnableEXT vkCmdSetDepthBiasEnableEXT;
PFN_vkCmdSetLogicOpEXT vkCmdSetLogicOpEXT;
PFN_vkCmdSetPrimitiveRestartEnableEXT vkCmdSetPrimitiveRestartEnableEXT;
#endif // defined(VK_EXT_extended_dynamic_state2) || (defined(VK_EXT_shader_object))
#if defined(VK_EXT_extended_dynamic_state3) || (defined(VK_EXT_shader_object))
PFN_vkCmdSetDepthClampEnableEXT vkCmdSetDepthClampEnableEXT;
PFN_vkCmdSetPolygonModeEXT vkCmdSetPolygonModeEXT;
PFN_vkCmdSetRasterizationSamplesEXT vkCmdSetRasterizationSamplesEXT;
PFN_vkCmdSetSampleMaskEXT vkCmdSetSampleMaskEXT;
PFN_vkCmdSetAlphaToCoverageEnableEXT vkCmdSetAlphaToCoverageEnableEXT;
PFN_vkCmdSetAlphaToOneEnableEXT vkCmdSetAlphaToOneEnableEXT;
PFN_vkCmdSetLogicOpEnableEXT vkCmdSetLogicOpEnableEXT;
PFN_vkCmdSetColorBlendEnableEXT vkCmdSetColorBlendEnableEXT;
PFN_vkCmdSetColorBlendEquationEXT vkCmdSetColorBlendEquationEXT;
PFN_vkCmdSetColorWriteMaskEXT vkCmdSetColorWriteMaskEXT;
#endif // defined(VK_EXT_extended_dynamic_state3) || (defined(VK_EXT_shader_object))
#if defined(VK_EXT_extended_dynamic_state3) && (defined(VK_KHR_maintenance2) || defined(VK_VERSION_1_1)) || (defined(VK_EXT_shader_object))
PFN_vkCmdSetTessellationDomainOriginEXT vkCmdSetTessellationDomainOriginEXT;
#endif // defined(VK_EXT_extended_dynamic_state3) && (defined(VK_KHR_maintenance2) || defined(VK_VERSION_1_1)) || (defined(VK_EXT_shader_object))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_transform_feedback) || (defined(VK_EXT_shader_object) && defined(VK_EXT_transform_feedback))
PFN_vkCmdSetRasterizationStreamEXT vkCmdSetRasterizationStreamEXT;
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_transform_feedback) || (defined(VK_EXT_shader_object) && defined(VK_EXT_transform_feedback))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_conservative_rasterization) || (defined(VK_EXT_shader_object) && defined(VK_EXT_conservative_rasterization))
PFN_vkCmdSetConservativeRasterizationModeEXT vkCmdSetConservativeRasterizationModeEXT;
PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT vkCmdSetExtraPrimitiveOverestimationSizeEXT;
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_conservative_rasterization) || (defined(VK_EXT_shader_object) && defined(VK_EXT_conservative_rasterization))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_enable) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_enable))
PFN_vkCmdSetDepthClipEnableEXT vkCmdSetDepthClipEnableEXT;
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_enable) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_enable))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_sample_locations) || (defined(VK_EXT_shader_object) && defined(VK_EXT_sample_locations))
PFN_vkCmdSetSampleLocationsEnableEXT vkCmdSetSampleLocationsEnableEXT;
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_sample_locations) || (defined(VK_EXT_shader_object) && defined(VK_EXT_sample_locations))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_blend_operation_advanced) || (defined(VK_EXT_shader_object) && defined(VK_EXT_blend_operation_advanced))
PFN_vkCmdSetColorBlendAdvancedEXT vkCmdSetColorBlendAdvancedEXT;
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_blend_operation_advanced) || (defined(VK_EXT_shader_object) && defined(VK_EXT_blend_operation_advanced))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_provoking_vertex) || (defined(VK_EXT_shader_object) && defined(VK_EXT_provoking_vertex))
PFN_vkCmdSetProvokingVertexModeEXT vkCmdSetProvokingVertexModeEXT;
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_provoking_vertex) || (defined(VK_EXT_shader_object) && defined(VK_EXT_provoking_vertex))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_line_rasterization) || (defined(VK_EXT_shader_object) && defined(VK_EXT_line_rasterization))
PFN_vkCmdSetLineRasterizationModeEXT vkCmdSetLineRasterizationModeEXT;
PFN_vkCmdSetLineStippleEnableEXT vkCmdSetLineStippleEnableEXT;
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_line_rasterization) || (defined(VK_EXT_shader_object) && defined(VK_EXT_line_rasterization))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_control) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_control))
PFN_vkCmdSetDepthClipNegativeOneToOneEXT vkCmdSetDepthClipNegativeOneToOneEXT;
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_control) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_control))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_clip_space_w_scaling) || (defined(VK_EXT_shader_object) && defined(VK_NV_clip_space_w_scaling))
PFN_vkCmdSetViewportWScalingEnableNV vkCmdSetViewportWScalingEnableNV;
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_clip_space_w_scaling) || (defined(VK_EXT_shader_object) && defined(VK_NV_clip_space_w_scaling))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_viewport_swizzle) || (defined(VK_EXT_shader_object) && defined(VK_NV_viewport_swizzle))
PFN_vkCmdSetViewportSwizzleNV vkCmdSetViewportSwizzleNV;
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_viewport_swizzle) || (defined(VK_EXT_shader_object) && defined(VK_NV_viewport_swizzle))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_fragment_coverage_to_color) || (defined(VK_EXT_shader_object) && defined(VK_NV_fragment_coverage_to_color))
PFN_vkCmdSetCoverageToColorEnableNV vkCmdSetCoverageToColorEnableNV;
PFN_vkCmdSetCoverageToColorLocationNV vkCmdSetCoverageToColorLocationNV;
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_fragment_coverage_to_color) || (defined(VK_EXT_shader_object) && defined(VK_NV_fragment_coverage_to_color))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_framebuffer_mixed_samples) || (defined(VK_EXT_shader_object) && defined(VK_NV_framebuffer_mixed_samples))
PFN_vkCmdSetCoverageModulationModeNV vkCmdSetCoverageModulationModeNV;
PFN_vkCmdSetCoverageModulationTableEnableNV vkCmdSetCoverageModulationTableEnableNV;
PFN_vkCmdSetCoverageModulationTableNV vkCmdSetCoverageModulationTableNV;
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_framebuffer_mixed_samples) || (defined(VK_EXT_shader_object) && defined(VK_NV_framebuffer_mixed_samples))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_shading_rate_image) || (defined(VK_EXT_shader_object) && defined(VK_NV_shading_rate_image))
PFN_vkCmdSetShadingRateImageEnableNV vkCmdSetShadingRateImageEnableNV;
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_shading_rate_image) || (defined(VK_EXT_shader_object) && defined(VK_NV_shading_rate_image))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_representative_fragment_test) || (defined(VK_EXT_shader_object) && defined(VK_NV_representative_fragment_test))
PFN_vkCmdSetRepresentativeFragmentTestEnableNV vkCmdSetRepresentativeFragmentTestEnableNV;
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_representative_fragment_test) || (defined(VK_EXT_shader_object) && defined(VK_NV_representative_fragment_test))
#if defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_coverage_reduction_mode) || (defined(VK_EXT_shader_object) && defined(VK_NV_coverage_reduction_mode))
PFN_vkCmdSetCoverageReductionModeNV vkCmdSetCoverageReductionModeNV;
#endif // defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_coverage_reduction_mode) || (defined(VK_EXT_shader_object) && defined(VK_NV_coverage_reduction_mode))
#if defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))
PFN_vkGetDeviceGroupSurfacePresentModes2EXT vkGetDeviceGroupSurfacePresentModes2EXT;
#endif // defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))
#if defined(VK_EXT_host_image_copy) || (defined(VK_EXT_image_compression_control))
PFN_vkGetImageSubresourceLayout2EXT vkGetImageSubresourceLayout2EXT;
#endif // defined(VK_EXT_host_image_copy) || (defined(VK_EXT_image_compression_control))
#if defined(VK_EXT_shader_object) || (defined(VK_EXT_vertex_input_dynamic_state))
PFN_vkCmdSetVertexInputEXT vkCmdSetVertexInputEXT;
#endif // defined(VK_EXT_shader_object) || (defined(VK_EXT_vertex_input_dynamic_state))
#if defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
PFN_vkCmdPushDescriptorSetWithTemplateKHR vkCmdPushDescriptorSetWithTemplateKHR;
#endif // defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
#if defined(VK_KHR_device_group) && defined(VK_KHR_surface) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
PFN_vkGetDeviceGroupPresentCapabilitiesKHR vkGetDeviceGroupPresentCapabilitiesKHR;
PFN_vkGetDeviceGroupSurfacePresentModesKHR vkGetDeviceGroupSurfacePresentModesKHR;
PFN_vkGetPhysicalDevicePresentRectanglesKHR vkGetPhysicalDevicePresentRectanglesKHR;
#endif // defined(VK_KHR_device_group) && defined(VK_KHR_surface) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
#if defined(VK_KHR_device_group) && defined(VK_KHR_swapchain) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
PFN_vkAcquireNextImage2KHR vkAcquireNextImage2KHR;
#endif // defined(VK_KHR_device_group) && defined(VK_KHR_swapchain) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
// KODIAK_GEN_SOURCE_FUNCTION_PTRS
