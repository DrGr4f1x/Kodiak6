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

using namespace Kodiak;
using namespace std;


VkResult Kodiak::InitializeLoader()
{
    HMODULE module = LoadLibraryA("vulkan-1.dll");
    if (!module)
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)(void(*)(void))GetProcAddress(module, "vkGetInstanceProcAddr");

#if defined(VK_VERSION_1_0)
	vkCreateInstance = (PFN_vkCreateInstance)vkGetInstanceProcAddr(nullptr, "vkCreateInstance");
	vkEnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties)vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceExtensionProperties");
	vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties)vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceLayerProperties");
#endif // defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
	vkEnumerateInstanceVersion = (PFN_vkEnumerateInstanceVersion)vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceVersion");
#endif // defined(VK_VERSION_1_1)

    return VK_SUCCESS;
}


void Kodiak::LoadInstanceFunctions(VkInstance instance)
{
#if defined(VK_VERSION_1_0)
	// Instance commands
	vkDestroyInstance = (PFN_vkDestroyInstance)vkGetInstanceProcAddr(instance, "vkDestroyInstance");
	vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices)vkGetInstanceProcAddr(instance, "vkEnumeratePhysicalDevices");
	vkGetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFeatures");
	vkGetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFormatProperties");
	vkGetPhysicalDeviceImageFormatProperties = (PFN_vkGetPhysicalDeviceImageFormatProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceImageFormatProperties");
	vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceProperties");
	vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceQueueFamilyProperties");
	vkGetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceMemoryProperties");
	vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr)vkGetInstanceProcAddr(instance, "vkGetDeviceProcAddr");
	vkCreateDevice = (PFN_vkCreateDevice)vkGetInstanceProcAddr(instance, "vkCreateDevice");
	vkEnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties)vkGetInstanceProcAddr(instance, "vkEnumerateDeviceExtensionProperties");
	vkEnumerateDeviceLayerProperties = (PFN_vkEnumerateDeviceLayerProperties)vkGetInstanceProcAddr(instance, "vkEnumerateDeviceLayerProperties");
	vkGetPhysicalDeviceSparseImageFormatProperties = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSparseImageFormatProperties");
	// Device commands
	vkDestroyDevice = (PFN_vkDestroyDevice)vkGetInstanceProcAddr(instance, "vkDestroyDevice");
	vkGetDeviceQueue = (PFN_vkGetDeviceQueue)vkGetInstanceProcAddr(instance, "vkGetDeviceQueue");
	vkQueueSubmit = (PFN_vkQueueSubmit)vkGetInstanceProcAddr(instance, "vkQueueSubmit");
	vkQueueWaitIdle = (PFN_vkQueueWaitIdle)vkGetInstanceProcAddr(instance, "vkQueueWaitIdle");
	vkDeviceWaitIdle = (PFN_vkDeviceWaitIdle)vkGetInstanceProcAddr(instance, "vkDeviceWaitIdle");
	vkAllocateMemory = (PFN_vkAllocateMemory)vkGetInstanceProcAddr(instance, "vkAllocateMemory");
	vkFreeMemory = (PFN_vkFreeMemory)vkGetInstanceProcAddr(instance, "vkFreeMemory");
	vkMapMemory = (PFN_vkMapMemory)vkGetInstanceProcAddr(instance, "vkMapMemory");
	vkUnmapMemory = (PFN_vkUnmapMemory)vkGetInstanceProcAddr(instance, "vkUnmapMemory");
	vkFlushMappedMemoryRanges = (PFN_vkFlushMappedMemoryRanges)vkGetInstanceProcAddr(instance, "vkFlushMappedMemoryRanges");
	vkInvalidateMappedMemoryRanges = (PFN_vkInvalidateMappedMemoryRanges)vkGetInstanceProcAddr(instance, "vkInvalidateMappedMemoryRanges");
	vkGetDeviceMemoryCommitment = (PFN_vkGetDeviceMemoryCommitment)vkGetInstanceProcAddr(instance, "vkGetDeviceMemoryCommitment");
	vkBindBufferMemory = (PFN_vkBindBufferMemory)vkGetInstanceProcAddr(instance, "vkBindBufferMemory");
	vkBindImageMemory = (PFN_vkBindImageMemory)vkGetInstanceProcAddr(instance, "vkBindImageMemory");
	vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements)vkGetInstanceProcAddr(instance, "vkGetBufferMemoryRequirements");
	vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements)vkGetInstanceProcAddr(instance, "vkGetImageMemoryRequirements");
	vkGetImageSparseMemoryRequirements = (PFN_vkGetImageSparseMemoryRequirements)vkGetInstanceProcAddr(instance, "vkGetImageSparseMemoryRequirements");
	vkQueueBindSparse = (PFN_vkQueueBindSparse)vkGetInstanceProcAddr(instance, "vkQueueBindSparse");
	vkCreateFence = (PFN_vkCreateFence)vkGetInstanceProcAddr(instance, "vkCreateFence");
	vkDestroyFence = (PFN_vkDestroyFence)vkGetInstanceProcAddr(instance, "vkDestroyFence");
	vkResetFences = (PFN_vkResetFences)vkGetInstanceProcAddr(instance, "vkResetFences");
	vkGetFenceStatus = (PFN_vkGetFenceStatus)vkGetInstanceProcAddr(instance, "vkGetFenceStatus");
	vkWaitForFences = (PFN_vkWaitForFences)vkGetInstanceProcAddr(instance, "vkWaitForFences");
	vkCreateSemaphore = (PFN_vkCreateSemaphore)vkGetInstanceProcAddr(instance, "vkCreateSemaphore");
	vkDestroySemaphore = (PFN_vkDestroySemaphore)vkGetInstanceProcAddr(instance, "vkDestroySemaphore");
	vkCreateEvent = (PFN_vkCreateEvent)vkGetInstanceProcAddr(instance, "vkCreateEvent");
	vkDestroyEvent = (PFN_vkDestroyEvent)vkGetInstanceProcAddr(instance, "vkDestroyEvent");
	vkGetEventStatus = (PFN_vkGetEventStatus)vkGetInstanceProcAddr(instance, "vkGetEventStatus");
	vkSetEvent = (PFN_vkSetEvent)vkGetInstanceProcAddr(instance, "vkSetEvent");
	vkResetEvent = (PFN_vkResetEvent)vkGetInstanceProcAddr(instance, "vkResetEvent");
	vkCreateQueryPool = (PFN_vkCreateQueryPool)vkGetInstanceProcAddr(instance, "vkCreateQueryPool");
	vkDestroyQueryPool = (PFN_vkDestroyQueryPool)vkGetInstanceProcAddr(instance, "vkDestroyQueryPool");
	vkGetQueryPoolResults = (PFN_vkGetQueryPoolResults)vkGetInstanceProcAddr(instance, "vkGetQueryPoolResults");
	vkCreateBuffer = (PFN_vkCreateBuffer)vkGetInstanceProcAddr(instance, "vkCreateBuffer");
	vkDestroyBuffer = (PFN_vkDestroyBuffer)vkGetInstanceProcAddr(instance, "vkDestroyBuffer");
	vkCreateBufferView = (PFN_vkCreateBufferView)vkGetInstanceProcAddr(instance, "vkCreateBufferView");
	vkDestroyBufferView = (PFN_vkDestroyBufferView)vkGetInstanceProcAddr(instance, "vkDestroyBufferView");
	vkCreateImage = (PFN_vkCreateImage)vkGetInstanceProcAddr(instance, "vkCreateImage");
	vkDestroyImage = (PFN_vkDestroyImage)vkGetInstanceProcAddr(instance, "vkDestroyImage");
	vkGetImageSubresourceLayout = (PFN_vkGetImageSubresourceLayout)vkGetInstanceProcAddr(instance, "vkGetImageSubresourceLayout");
	vkCreateImageView = (PFN_vkCreateImageView)vkGetInstanceProcAddr(instance, "vkCreateImageView");
	vkDestroyImageView = (PFN_vkDestroyImageView)vkGetInstanceProcAddr(instance, "vkDestroyImageView");
	vkCreateShaderModule = (PFN_vkCreateShaderModule)vkGetInstanceProcAddr(instance, "vkCreateShaderModule");
	vkDestroyShaderModule = (PFN_vkDestroyShaderModule)vkGetInstanceProcAddr(instance, "vkDestroyShaderModule");
	vkCreatePipelineCache = (PFN_vkCreatePipelineCache)vkGetInstanceProcAddr(instance, "vkCreatePipelineCache");
	vkDestroyPipelineCache = (PFN_vkDestroyPipelineCache)vkGetInstanceProcAddr(instance, "vkDestroyPipelineCache");
	vkGetPipelineCacheData = (PFN_vkGetPipelineCacheData)vkGetInstanceProcAddr(instance, "vkGetPipelineCacheData");
	vkMergePipelineCaches = (PFN_vkMergePipelineCaches)vkGetInstanceProcAddr(instance, "vkMergePipelineCaches");
	vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines)vkGetInstanceProcAddr(instance, "vkCreateGraphicsPipelines");
	vkCreateComputePipelines = (PFN_vkCreateComputePipelines)vkGetInstanceProcAddr(instance, "vkCreateComputePipelines");
	vkDestroyPipeline = (PFN_vkDestroyPipeline)vkGetInstanceProcAddr(instance, "vkDestroyPipeline");
	vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout)vkGetInstanceProcAddr(instance, "vkCreatePipelineLayout");
	vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout)vkGetInstanceProcAddr(instance, "vkDestroyPipelineLayout");
	vkCreateSampler = (PFN_vkCreateSampler)vkGetInstanceProcAddr(instance, "vkCreateSampler");
	vkDestroySampler = (PFN_vkDestroySampler)vkGetInstanceProcAddr(instance, "vkDestroySampler");
	vkCreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout)vkGetInstanceProcAddr(instance, "vkCreateDescriptorSetLayout");
	vkDestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout)vkGetInstanceProcAddr(instance, "vkDestroyDescriptorSetLayout");
	vkCreateDescriptorPool = (PFN_vkCreateDescriptorPool)vkGetInstanceProcAddr(instance, "vkCreateDescriptorPool");
	vkDestroyDescriptorPool = (PFN_vkDestroyDescriptorPool)vkGetInstanceProcAddr(instance, "vkDestroyDescriptorPool");
	vkResetDescriptorPool = (PFN_vkResetDescriptorPool)vkGetInstanceProcAddr(instance, "vkResetDescriptorPool");
	vkAllocateDescriptorSets = (PFN_vkAllocateDescriptorSets)vkGetInstanceProcAddr(instance, "vkAllocateDescriptorSets");
	vkFreeDescriptorSets = (PFN_vkFreeDescriptorSets)vkGetInstanceProcAddr(instance, "vkFreeDescriptorSets");
	vkUpdateDescriptorSets = (PFN_vkUpdateDescriptorSets)vkGetInstanceProcAddr(instance, "vkUpdateDescriptorSets");
	vkCreateFramebuffer = (PFN_vkCreateFramebuffer)vkGetInstanceProcAddr(instance, "vkCreateFramebuffer");
	vkDestroyFramebuffer = (PFN_vkDestroyFramebuffer)vkGetInstanceProcAddr(instance, "vkDestroyFramebuffer");
	vkCreateRenderPass = (PFN_vkCreateRenderPass)vkGetInstanceProcAddr(instance, "vkCreateRenderPass");
	vkDestroyRenderPass = (PFN_vkDestroyRenderPass)vkGetInstanceProcAddr(instance, "vkDestroyRenderPass");
	vkGetRenderAreaGranularity = (PFN_vkGetRenderAreaGranularity)vkGetInstanceProcAddr(instance, "vkGetRenderAreaGranularity");
	vkCreateCommandPool = (PFN_vkCreateCommandPool)vkGetInstanceProcAddr(instance, "vkCreateCommandPool");
	vkDestroyCommandPool = (PFN_vkDestroyCommandPool)vkGetInstanceProcAddr(instance, "vkDestroyCommandPool");
	vkResetCommandPool = (PFN_vkResetCommandPool)vkGetInstanceProcAddr(instance, "vkResetCommandPool");
	vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)vkGetInstanceProcAddr(instance, "vkAllocateCommandBuffers");
	vkFreeCommandBuffers = (PFN_vkFreeCommandBuffers)vkGetInstanceProcAddr(instance, "vkFreeCommandBuffers");
	vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer)vkGetInstanceProcAddr(instance, "vkBeginCommandBuffer");
	vkEndCommandBuffer = (PFN_vkEndCommandBuffer)vkGetInstanceProcAddr(instance, "vkEndCommandBuffer");
	vkResetCommandBuffer = (PFN_vkResetCommandBuffer)vkGetInstanceProcAddr(instance, "vkResetCommandBuffer");
	vkCmdBindPipeline = (PFN_vkCmdBindPipeline)vkGetInstanceProcAddr(instance, "vkCmdBindPipeline");
	vkCmdSetViewport = (PFN_vkCmdSetViewport)vkGetInstanceProcAddr(instance, "vkCmdSetViewport");
	vkCmdSetScissor = (PFN_vkCmdSetScissor)vkGetInstanceProcAddr(instance, "vkCmdSetScissor");
	vkCmdSetLineWidth = (PFN_vkCmdSetLineWidth)vkGetInstanceProcAddr(instance, "vkCmdSetLineWidth");
	vkCmdSetDepthBias = (PFN_vkCmdSetDepthBias)vkGetInstanceProcAddr(instance, "vkCmdSetDepthBias");
	vkCmdSetBlendConstants = (PFN_vkCmdSetBlendConstants)vkGetInstanceProcAddr(instance, "vkCmdSetBlendConstants");
	vkCmdSetDepthBounds = (PFN_vkCmdSetDepthBounds)vkGetInstanceProcAddr(instance, "vkCmdSetDepthBounds");
	vkCmdSetStencilCompareMask = (PFN_vkCmdSetStencilCompareMask)vkGetInstanceProcAddr(instance, "vkCmdSetStencilCompareMask");
	vkCmdSetStencilWriteMask = (PFN_vkCmdSetStencilWriteMask)vkGetInstanceProcAddr(instance, "vkCmdSetStencilWriteMask");
	vkCmdSetStencilReference = (PFN_vkCmdSetStencilReference)vkGetInstanceProcAddr(instance, "vkCmdSetStencilReference");
	vkCmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets)vkGetInstanceProcAddr(instance, "vkCmdBindDescriptorSets");
	vkCmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer)vkGetInstanceProcAddr(instance, "vkCmdBindIndexBuffer");
	vkCmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers)vkGetInstanceProcAddr(instance, "vkCmdBindVertexBuffers");
	vkCmdDraw = (PFN_vkCmdDraw)vkGetInstanceProcAddr(instance, "vkCmdDraw");
	vkCmdDrawIndexed = (PFN_vkCmdDrawIndexed)vkGetInstanceProcAddr(instance, "vkCmdDrawIndexed");
	vkCmdDrawIndirect = (PFN_vkCmdDrawIndirect)vkGetInstanceProcAddr(instance, "vkCmdDrawIndirect");
	vkCmdDrawIndexedIndirect = (PFN_vkCmdDrawIndexedIndirect)vkGetInstanceProcAddr(instance, "vkCmdDrawIndexedIndirect");
	vkCmdDispatch = (PFN_vkCmdDispatch)vkGetInstanceProcAddr(instance, "vkCmdDispatch");
	vkCmdDispatchIndirect = (PFN_vkCmdDispatchIndirect)vkGetInstanceProcAddr(instance, "vkCmdDispatchIndirect");
	vkCmdCopyBuffer = (PFN_vkCmdCopyBuffer)vkGetInstanceProcAddr(instance, "vkCmdCopyBuffer");
	vkCmdCopyImage = (PFN_vkCmdCopyImage)vkGetInstanceProcAddr(instance, "vkCmdCopyImage");
	vkCmdBlitImage = (PFN_vkCmdBlitImage)vkGetInstanceProcAddr(instance, "vkCmdBlitImage");
	vkCmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage)vkGetInstanceProcAddr(instance, "vkCmdCopyBufferToImage");
	vkCmdCopyImageToBuffer = (PFN_vkCmdCopyImageToBuffer)vkGetInstanceProcAddr(instance, "vkCmdCopyImageToBuffer");
	vkCmdUpdateBuffer = (PFN_vkCmdUpdateBuffer)vkGetInstanceProcAddr(instance, "vkCmdUpdateBuffer");
	vkCmdFillBuffer = (PFN_vkCmdFillBuffer)vkGetInstanceProcAddr(instance, "vkCmdFillBuffer");
	vkCmdClearColorImage = (PFN_vkCmdClearColorImage)vkGetInstanceProcAddr(instance, "vkCmdClearColorImage");
	vkCmdClearDepthStencilImage = (PFN_vkCmdClearDepthStencilImage)vkGetInstanceProcAddr(instance, "vkCmdClearDepthStencilImage");
	vkCmdClearAttachments = (PFN_vkCmdClearAttachments)vkGetInstanceProcAddr(instance, "vkCmdClearAttachments");
	vkCmdResolveImage = (PFN_vkCmdResolveImage)vkGetInstanceProcAddr(instance, "vkCmdResolveImage");
	vkCmdSetEvent = (PFN_vkCmdSetEvent)vkGetInstanceProcAddr(instance, "vkCmdSetEvent");
	vkCmdResetEvent = (PFN_vkCmdResetEvent)vkGetInstanceProcAddr(instance, "vkCmdResetEvent");
	vkCmdWaitEvents = (PFN_vkCmdWaitEvents)vkGetInstanceProcAddr(instance, "vkCmdWaitEvents");
	vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier)vkGetInstanceProcAddr(instance, "vkCmdPipelineBarrier");
	vkCmdBeginQuery = (PFN_vkCmdBeginQuery)vkGetInstanceProcAddr(instance, "vkCmdBeginQuery");
	vkCmdEndQuery = (PFN_vkCmdEndQuery)vkGetInstanceProcAddr(instance, "vkCmdEndQuery");
	vkCmdResetQueryPool = (PFN_vkCmdResetQueryPool)vkGetInstanceProcAddr(instance, "vkCmdResetQueryPool");
	vkCmdWriteTimestamp = (PFN_vkCmdWriteTimestamp)vkGetInstanceProcAddr(instance, "vkCmdWriteTimestamp");
	vkCmdCopyQueryPoolResults = (PFN_vkCmdCopyQueryPoolResults)vkGetInstanceProcAddr(instance, "vkCmdCopyQueryPoolResults");
	vkCmdPushConstants = (PFN_vkCmdPushConstants)vkGetInstanceProcAddr(instance, "vkCmdPushConstants");
	vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass)vkGetInstanceProcAddr(instance, "vkCmdBeginRenderPass");
	vkCmdNextSubpass = (PFN_vkCmdNextSubpass)vkGetInstanceProcAddr(instance, "vkCmdNextSubpass");
	vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass)vkGetInstanceProcAddr(instance, "vkCmdEndRenderPass");
	vkCmdExecuteCommands = (PFN_vkCmdExecuteCommands)vkGetInstanceProcAddr(instance, "vkCmdExecuteCommands");
#endif // defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
	// Instance commands
	vkEnumeratePhysicalDeviceGroups = (PFN_vkEnumeratePhysicalDeviceGroups)vkGetInstanceProcAddr(instance, "vkEnumeratePhysicalDeviceGroups");
	vkGetPhysicalDeviceFeatures2 = (PFN_vkGetPhysicalDeviceFeatures2)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFeatures2");
	vkGetPhysicalDeviceProperties2 = (PFN_vkGetPhysicalDeviceProperties2)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceProperties2");
	vkGetPhysicalDeviceFormatProperties2 = (PFN_vkGetPhysicalDeviceFormatProperties2)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFormatProperties2");
	vkGetPhysicalDeviceImageFormatProperties2 = (PFN_vkGetPhysicalDeviceImageFormatProperties2)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceImageFormatProperties2");
	vkGetPhysicalDeviceQueueFamilyProperties2 = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceQueueFamilyProperties2");
	vkGetPhysicalDeviceMemoryProperties2 = (PFN_vkGetPhysicalDeviceMemoryProperties2)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceMemoryProperties2");
	vkGetPhysicalDeviceSparseImageFormatProperties2 = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSparseImageFormatProperties2");
	vkGetPhysicalDeviceExternalBufferProperties = (PFN_vkGetPhysicalDeviceExternalBufferProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceExternalBufferProperties");
	vkGetPhysicalDeviceExternalFenceProperties = (PFN_vkGetPhysicalDeviceExternalFenceProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceExternalFenceProperties");
	vkGetPhysicalDeviceExternalSemaphoreProperties = (PFN_vkGetPhysicalDeviceExternalSemaphoreProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceExternalSemaphoreProperties");
	// Device commands
	vkBindBufferMemory2 = (PFN_vkBindBufferMemory2)vkGetInstanceProcAddr(instance, "vkBindBufferMemory2");
	vkBindImageMemory2 = (PFN_vkBindImageMemory2)vkGetInstanceProcAddr(instance, "vkBindImageMemory2");
	vkGetDeviceGroupPeerMemoryFeatures = (PFN_vkGetDeviceGroupPeerMemoryFeatures)vkGetInstanceProcAddr(instance, "vkGetDeviceGroupPeerMemoryFeatures");
	vkCmdSetDeviceMask = (PFN_vkCmdSetDeviceMask)vkGetInstanceProcAddr(instance, "vkCmdSetDeviceMask");
	vkCmdDispatchBase = (PFN_vkCmdDispatchBase)vkGetInstanceProcAddr(instance, "vkCmdDispatchBase");
	vkGetImageMemoryRequirements2 = (PFN_vkGetImageMemoryRequirements2)vkGetInstanceProcAddr(instance, "vkGetImageMemoryRequirements2");
	vkGetBufferMemoryRequirements2 = (PFN_vkGetBufferMemoryRequirements2)vkGetInstanceProcAddr(instance, "vkGetBufferMemoryRequirements2");
	vkGetImageSparseMemoryRequirements2 = (PFN_vkGetImageSparseMemoryRequirements2)vkGetInstanceProcAddr(instance, "vkGetImageSparseMemoryRequirements2");
	vkTrimCommandPool = (PFN_vkTrimCommandPool)vkGetInstanceProcAddr(instance, "vkTrimCommandPool");
	vkGetDeviceQueue2 = (PFN_vkGetDeviceQueue2)vkGetInstanceProcAddr(instance, "vkGetDeviceQueue2");
	vkCreateSamplerYcbcrConversion = (PFN_vkCreateSamplerYcbcrConversion)vkGetInstanceProcAddr(instance, "vkCreateSamplerYcbcrConversion");
	vkDestroySamplerYcbcrConversion = (PFN_vkDestroySamplerYcbcrConversion)vkGetInstanceProcAddr(instance, "vkDestroySamplerYcbcrConversion");
	vkCreateDescriptorUpdateTemplate = (PFN_vkCreateDescriptorUpdateTemplate)vkGetInstanceProcAddr(instance, "vkCreateDescriptorUpdateTemplate");
	vkDestroyDescriptorUpdateTemplate = (PFN_vkDestroyDescriptorUpdateTemplate)vkGetInstanceProcAddr(instance, "vkDestroyDescriptorUpdateTemplate");
	vkUpdateDescriptorSetWithTemplate = (PFN_vkUpdateDescriptorSetWithTemplate)vkGetInstanceProcAddr(instance, "vkUpdateDescriptorSetWithTemplate");
	vkGetDescriptorSetLayoutSupport = (PFN_vkGetDescriptorSetLayoutSupport)vkGetInstanceProcAddr(instance, "vkGetDescriptorSetLayoutSupport");
#endif // defined(VK_VERSION_1_1)
#if defined(VK_VERSION_1_2)
	// Device commands
	vkCmdDrawIndirectCount = (PFN_vkCmdDrawIndirectCount)vkGetInstanceProcAddr(instance, "vkCmdDrawIndirectCount");
	vkCmdDrawIndexedIndirectCount = (PFN_vkCmdDrawIndexedIndirectCount)vkGetInstanceProcAddr(instance, "vkCmdDrawIndexedIndirectCount");
	vkCreateRenderPass2 = (PFN_vkCreateRenderPass2)vkGetInstanceProcAddr(instance, "vkCreateRenderPass2");
	vkCmdBeginRenderPass2 = (PFN_vkCmdBeginRenderPass2)vkGetInstanceProcAddr(instance, "vkCmdBeginRenderPass2");
	vkCmdNextSubpass2 = (PFN_vkCmdNextSubpass2)vkGetInstanceProcAddr(instance, "vkCmdNextSubpass2");
	vkCmdEndRenderPass2 = (PFN_vkCmdEndRenderPass2)vkGetInstanceProcAddr(instance, "vkCmdEndRenderPass2");
	vkResetQueryPool = (PFN_vkResetQueryPool)vkGetInstanceProcAddr(instance, "vkResetQueryPool");
	vkGetSemaphoreCounterValue = (PFN_vkGetSemaphoreCounterValue)vkGetInstanceProcAddr(instance, "vkGetSemaphoreCounterValue");
	vkWaitSemaphores = (PFN_vkWaitSemaphores)vkGetInstanceProcAddr(instance, "vkWaitSemaphores");
	vkSignalSemaphore = (PFN_vkSignalSemaphore)vkGetInstanceProcAddr(instance, "vkSignalSemaphore");
	vkGetBufferDeviceAddress = (PFN_vkGetBufferDeviceAddress)vkGetInstanceProcAddr(instance, "vkGetBufferDeviceAddress");
	vkGetBufferOpaqueCaptureAddress = (PFN_vkGetBufferOpaqueCaptureAddress)vkGetInstanceProcAddr(instance, "vkGetBufferOpaqueCaptureAddress");
	vkGetDeviceMemoryOpaqueCaptureAddress = (PFN_vkGetDeviceMemoryOpaqueCaptureAddress)vkGetInstanceProcAddr(instance, "vkGetDeviceMemoryOpaqueCaptureAddress");
#endif // defined(VK_VERSION_1_2)
#if defined(VK_VERSION_1_3)
	// Instance commands
	vkGetPhysicalDeviceToolProperties = (PFN_vkGetPhysicalDeviceToolProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceToolProperties");
	// Device commands
	vkCreatePrivateDataSlot = (PFN_vkCreatePrivateDataSlot)vkGetInstanceProcAddr(instance, "vkCreatePrivateDataSlot");
	vkDestroyPrivateDataSlot = (PFN_vkDestroyPrivateDataSlot)vkGetInstanceProcAddr(instance, "vkDestroyPrivateDataSlot");
	vkSetPrivateData = (PFN_vkSetPrivateData)vkGetInstanceProcAddr(instance, "vkSetPrivateData");
	vkGetPrivateData = (PFN_vkGetPrivateData)vkGetInstanceProcAddr(instance, "vkGetPrivateData");
	vkCmdSetEvent2 = (PFN_vkCmdSetEvent2)vkGetInstanceProcAddr(instance, "vkCmdSetEvent2");
	vkCmdResetEvent2 = (PFN_vkCmdResetEvent2)vkGetInstanceProcAddr(instance, "vkCmdResetEvent2");
	vkCmdWaitEvents2 = (PFN_vkCmdWaitEvents2)vkGetInstanceProcAddr(instance, "vkCmdWaitEvents2");
	vkCmdPipelineBarrier2 = (PFN_vkCmdPipelineBarrier2)vkGetInstanceProcAddr(instance, "vkCmdPipelineBarrier2");
	vkCmdWriteTimestamp2 = (PFN_vkCmdWriteTimestamp2)vkGetInstanceProcAddr(instance, "vkCmdWriteTimestamp2");
	vkQueueSubmit2 = (PFN_vkQueueSubmit2)vkGetInstanceProcAddr(instance, "vkQueueSubmit2");
	vkCmdCopyBuffer2 = (PFN_vkCmdCopyBuffer2)vkGetInstanceProcAddr(instance, "vkCmdCopyBuffer2");
	vkCmdCopyImage2 = (PFN_vkCmdCopyImage2)vkGetInstanceProcAddr(instance, "vkCmdCopyImage2");
	vkCmdCopyBufferToImage2 = (PFN_vkCmdCopyBufferToImage2)vkGetInstanceProcAddr(instance, "vkCmdCopyBufferToImage2");
	vkCmdCopyImageToBuffer2 = (PFN_vkCmdCopyImageToBuffer2)vkGetInstanceProcAddr(instance, "vkCmdCopyImageToBuffer2");
	vkCmdBlitImage2 = (PFN_vkCmdBlitImage2)vkGetInstanceProcAddr(instance, "vkCmdBlitImage2");
	vkCmdResolveImage2 = (PFN_vkCmdResolveImage2)vkGetInstanceProcAddr(instance, "vkCmdResolveImage2");
	vkCmdBeginRendering = (PFN_vkCmdBeginRendering)vkGetInstanceProcAddr(instance, "vkCmdBeginRendering");
	vkCmdEndRendering = (PFN_vkCmdEndRendering)vkGetInstanceProcAddr(instance, "vkCmdEndRendering");
	vkCmdSetCullMode = (PFN_vkCmdSetCullMode)vkGetInstanceProcAddr(instance, "vkCmdSetCullMode");
	vkCmdSetFrontFace = (PFN_vkCmdSetFrontFace)vkGetInstanceProcAddr(instance, "vkCmdSetFrontFace");
	vkCmdSetPrimitiveTopology = (PFN_vkCmdSetPrimitiveTopology)vkGetInstanceProcAddr(instance, "vkCmdSetPrimitiveTopology");
	vkCmdSetViewportWithCount = (PFN_vkCmdSetViewportWithCount)vkGetInstanceProcAddr(instance, "vkCmdSetViewportWithCount");
	vkCmdSetScissorWithCount = (PFN_vkCmdSetScissorWithCount)vkGetInstanceProcAddr(instance, "vkCmdSetScissorWithCount");
	vkCmdBindVertexBuffers2 = (PFN_vkCmdBindVertexBuffers2)vkGetInstanceProcAddr(instance, "vkCmdBindVertexBuffers2");
	vkCmdSetDepthTestEnable = (PFN_vkCmdSetDepthTestEnable)vkGetInstanceProcAddr(instance, "vkCmdSetDepthTestEnable");
	vkCmdSetDepthWriteEnable = (PFN_vkCmdSetDepthWriteEnable)vkGetInstanceProcAddr(instance, "vkCmdSetDepthWriteEnable");
	vkCmdSetDepthCompareOp = (PFN_vkCmdSetDepthCompareOp)vkGetInstanceProcAddr(instance, "vkCmdSetDepthCompareOp");
	vkCmdSetDepthBoundsTestEnable = (PFN_vkCmdSetDepthBoundsTestEnable)vkGetInstanceProcAddr(instance, "vkCmdSetDepthBoundsTestEnable");
	vkCmdSetStencilTestEnable = (PFN_vkCmdSetStencilTestEnable)vkGetInstanceProcAddr(instance, "vkCmdSetStencilTestEnable");
	vkCmdSetStencilOp = (PFN_vkCmdSetStencilOp)vkGetInstanceProcAddr(instance, "vkCmdSetStencilOp");
	vkCmdSetRasterizerDiscardEnable = (PFN_vkCmdSetRasterizerDiscardEnable)vkGetInstanceProcAddr(instance, "vkCmdSetRasterizerDiscardEnable");
	vkCmdSetDepthBiasEnable = (PFN_vkCmdSetDepthBiasEnable)vkGetInstanceProcAddr(instance, "vkCmdSetDepthBiasEnable");
	vkCmdSetPrimitiveRestartEnable = (PFN_vkCmdSetPrimitiveRestartEnable)vkGetInstanceProcAddr(instance, "vkCmdSetPrimitiveRestartEnable");
	vkGetDeviceBufferMemoryRequirements = (PFN_vkGetDeviceBufferMemoryRequirements)vkGetInstanceProcAddr(instance, "vkGetDeviceBufferMemoryRequirements");
	vkGetDeviceImageMemoryRequirements = (PFN_vkGetDeviceImageMemoryRequirements)vkGetInstanceProcAddr(instance, "vkGetDeviceImageMemoryRequirements");
	vkGetDeviceImageSparseMemoryRequirements = (PFN_vkGetDeviceImageSparseMemoryRequirements)vkGetInstanceProcAddr(instance, "vkGetDeviceImageSparseMemoryRequirements");
#endif // defined(VK_VERSION_1_3)
}


void Kodiak::LoadInstanceFunctionsOnly(VkInstance instance)
{
#if defined(VK_VERSION_1_0)
	// Instance commands
	vkDestroyInstance = (PFN_vkDestroyInstance)vkGetInstanceProcAddr(instance, "vkDestroyInstance");
	vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices)vkGetInstanceProcAddr(instance, "vkEnumeratePhysicalDevices");
	vkGetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFeatures");
	vkGetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFormatProperties");
	vkGetPhysicalDeviceImageFormatProperties = (PFN_vkGetPhysicalDeviceImageFormatProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceImageFormatProperties");
	vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceProperties");
	vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceQueueFamilyProperties");
	vkGetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceMemoryProperties");
	vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr)vkGetInstanceProcAddr(instance, "vkGetDeviceProcAddr");
	vkCreateDevice = (PFN_vkCreateDevice)vkGetInstanceProcAddr(instance, "vkCreateDevice");
	vkEnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties)vkGetInstanceProcAddr(instance, "vkEnumerateDeviceExtensionProperties");
	vkEnumerateDeviceLayerProperties = (PFN_vkEnumerateDeviceLayerProperties)vkGetInstanceProcAddr(instance, "vkEnumerateDeviceLayerProperties");
	vkGetPhysicalDeviceSparseImageFormatProperties = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSparseImageFormatProperties");
#endif // defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
	// Instance commands
	vkEnumeratePhysicalDeviceGroups = (PFN_vkEnumeratePhysicalDeviceGroups)vkGetInstanceProcAddr(instance, "vkEnumeratePhysicalDeviceGroups");
	vkGetPhysicalDeviceFeatures2 = (PFN_vkGetPhysicalDeviceFeatures2)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFeatures2");
	vkGetPhysicalDeviceProperties2 = (PFN_vkGetPhysicalDeviceProperties2)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceProperties2");
	vkGetPhysicalDeviceFormatProperties2 = (PFN_vkGetPhysicalDeviceFormatProperties2)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFormatProperties2");
	vkGetPhysicalDeviceImageFormatProperties2 = (PFN_vkGetPhysicalDeviceImageFormatProperties2)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceImageFormatProperties2");
	vkGetPhysicalDeviceQueueFamilyProperties2 = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceQueueFamilyProperties2");
	vkGetPhysicalDeviceMemoryProperties2 = (PFN_vkGetPhysicalDeviceMemoryProperties2)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceMemoryProperties2");
	vkGetPhysicalDeviceSparseImageFormatProperties2 = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSparseImageFormatProperties2");
	vkGetPhysicalDeviceExternalBufferProperties = (PFN_vkGetPhysicalDeviceExternalBufferProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceExternalBufferProperties");
	vkGetPhysicalDeviceExternalFenceProperties = (PFN_vkGetPhysicalDeviceExternalFenceProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceExternalFenceProperties");
	vkGetPhysicalDeviceExternalSemaphoreProperties = (PFN_vkGetPhysicalDeviceExternalSemaphoreProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceExternalSemaphoreProperties");
#endif // defined(VK_VERSION_1_1)
#if defined(VK_VERSION_1_3)
	// Instance commands
	vkGetPhysicalDeviceToolProperties = (PFN_vkGetPhysicalDeviceToolProperties)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceToolProperties");
#endif // defined(VK_VERSION_1_3)
}


void Kodiak::LoadDeviceFunctions(VkDevice device)
{
#if defined(VK_VERSION_1_0)
	// Device commands
	vkDestroyDevice = (PFN_vkDestroyDevice)vkGetDeviceProcAddr(device, "vkDestroyDevice");
	vkGetDeviceQueue = (PFN_vkGetDeviceQueue)vkGetDeviceProcAddr(device, "vkGetDeviceQueue");
	vkQueueSubmit = (PFN_vkQueueSubmit)vkGetDeviceProcAddr(device, "vkQueueSubmit");
	vkQueueWaitIdle = (PFN_vkQueueWaitIdle)vkGetDeviceProcAddr(device, "vkQueueWaitIdle");
	vkDeviceWaitIdle = (PFN_vkDeviceWaitIdle)vkGetDeviceProcAddr(device, "vkDeviceWaitIdle");
	vkAllocateMemory = (PFN_vkAllocateMemory)vkGetDeviceProcAddr(device, "vkAllocateMemory");
	vkFreeMemory = (PFN_vkFreeMemory)vkGetDeviceProcAddr(device, "vkFreeMemory");
	vkMapMemory = (PFN_vkMapMemory)vkGetDeviceProcAddr(device, "vkMapMemory");
	vkUnmapMemory = (PFN_vkUnmapMemory)vkGetDeviceProcAddr(device, "vkUnmapMemory");
	vkFlushMappedMemoryRanges = (PFN_vkFlushMappedMemoryRanges)vkGetDeviceProcAddr(device, "vkFlushMappedMemoryRanges");
	vkInvalidateMappedMemoryRanges = (PFN_vkInvalidateMappedMemoryRanges)vkGetDeviceProcAddr(device, "vkInvalidateMappedMemoryRanges");
	vkGetDeviceMemoryCommitment = (PFN_vkGetDeviceMemoryCommitment)vkGetDeviceProcAddr(device, "vkGetDeviceMemoryCommitment");
	vkBindBufferMemory = (PFN_vkBindBufferMemory)vkGetDeviceProcAddr(device, "vkBindBufferMemory");
	vkBindImageMemory = (PFN_vkBindImageMemory)vkGetDeviceProcAddr(device, "vkBindImageMemory");
	vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements)vkGetDeviceProcAddr(device, "vkGetBufferMemoryRequirements");
	vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements)vkGetDeviceProcAddr(device, "vkGetImageMemoryRequirements");
	vkGetImageSparseMemoryRequirements = (PFN_vkGetImageSparseMemoryRequirements)vkGetDeviceProcAddr(device, "vkGetImageSparseMemoryRequirements");
	vkQueueBindSparse = (PFN_vkQueueBindSparse)vkGetDeviceProcAddr(device, "vkQueueBindSparse");
	vkCreateFence = (PFN_vkCreateFence)vkGetDeviceProcAddr(device, "vkCreateFence");
	vkDestroyFence = (PFN_vkDestroyFence)vkGetDeviceProcAddr(device, "vkDestroyFence");
	vkResetFences = (PFN_vkResetFences)vkGetDeviceProcAddr(device, "vkResetFences");
	vkGetFenceStatus = (PFN_vkGetFenceStatus)vkGetDeviceProcAddr(device, "vkGetFenceStatus");
	vkWaitForFences = (PFN_vkWaitForFences)vkGetDeviceProcAddr(device, "vkWaitForFences");
	vkCreateSemaphore = (PFN_vkCreateSemaphore)vkGetDeviceProcAddr(device, "vkCreateSemaphore");
	vkDestroySemaphore = (PFN_vkDestroySemaphore)vkGetDeviceProcAddr(device, "vkDestroySemaphore");
	vkCreateEvent = (PFN_vkCreateEvent)vkGetDeviceProcAddr(device, "vkCreateEvent");
	vkDestroyEvent = (PFN_vkDestroyEvent)vkGetDeviceProcAddr(device, "vkDestroyEvent");
	vkGetEventStatus = (PFN_vkGetEventStatus)vkGetDeviceProcAddr(device, "vkGetEventStatus");
	vkSetEvent = (PFN_vkSetEvent)vkGetDeviceProcAddr(device, "vkSetEvent");
	vkResetEvent = (PFN_vkResetEvent)vkGetDeviceProcAddr(device, "vkResetEvent");
	vkCreateQueryPool = (PFN_vkCreateQueryPool)vkGetDeviceProcAddr(device, "vkCreateQueryPool");
	vkDestroyQueryPool = (PFN_vkDestroyQueryPool)vkGetDeviceProcAddr(device, "vkDestroyQueryPool");
	vkGetQueryPoolResults = (PFN_vkGetQueryPoolResults)vkGetDeviceProcAddr(device, "vkGetQueryPoolResults");
	vkCreateBuffer = (PFN_vkCreateBuffer)vkGetDeviceProcAddr(device, "vkCreateBuffer");
	vkDestroyBuffer = (PFN_vkDestroyBuffer)vkGetDeviceProcAddr(device, "vkDestroyBuffer");
	vkCreateBufferView = (PFN_vkCreateBufferView)vkGetDeviceProcAddr(device, "vkCreateBufferView");
	vkDestroyBufferView = (PFN_vkDestroyBufferView)vkGetDeviceProcAddr(device, "vkDestroyBufferView");
	vkCreateImage = (PFN_vkCreateImage)vkGetDeviceProcAddr(device, "vkCreateImage");
	vkDestroyImage = (PFN_vkDestroyImage)vkGetDeviceProcAddr(device, "vkDestroyImage");
	vkGetImageSubresourceLayout = (PFN_vkGetImageSubresourceLayout)vkGetDeviceProcAddr(device, "vkGetImageSubresourceLayout");
	vkCreateImageView = (PFN_vkCreateImageView)vkGetDeviceProcAddr(device, "vkCreateImageView");
	vkDestroyImageView = (PFN_vkDestroyImageView)vkGetDeviceProcAddr(device, "vkDestroyImageView");
	vkCreateShaderModule = (PFN_vkCreateShaderModule)vkGetDeviceProcAddr(device, "vkCreateShaderModule");
	vkDestroyShaderModule = (PFN_vkDestroyShaderModule)vkGetDeviceProcAddr(device, "vkDestroyShaderModule");
	vkCreatePipelineCache = (PFN_vkCreatePipelineCache)vkGetDeviceProcAddr(device, "vkCreatePipelineCache");
	vkDestroyPipelineCache = (PFN_vkDestroyPipelineCache)vkGetDeviceProcAddr(device, "vkDestroyPipelineCache");
	vkGetPipelineCacheData = (PFN_vkGetPipelineCacheData)vkGetDeviceProcAddr(device, "vkGetPipelineCacheData");
	vkMergePipelineCaches = (PFN_vkMergePipelineCaches)vkGetDeviceProcAddr(device, "vkMergePipelineCaches");
	vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines)vkGetDeviceProcAddr(device, "vkCreateGraphicsPipelines");
	vkCreateComputePipelines = (PFN_vkCreateComputePipelines)vkGetDeviceProcAddr(device, "vkCreateComputePipelines");
	vkDestroyPipeline = (PFN_vkDestroyPipeline)vkGetDeviceProcAddr(device, "vkDestroyPipeline");
	vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout)vkGetDeviceProcAddr(device, "vkCreatePipelineLayout");
	vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout)vkGetDeviceProcAddr(device, "vkDestroyPipelineLayout");
	vkCreateSampler = (PFN_vkCreateSampler)vkGetDeviceProcAddr(device, "vkCreateSampler");
	vkDestroySampler = (PFN_vkDestroySampler)vkGetDeviceProcAddr(device, "vkDestroySampler");
	vkCreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout)vkGetDeviceProcAddr(device, "vkCreateDescriptorSetLayout");
	vkDestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout)vkGetDeviceProcAddr(device, "vkDestroyDescriptorSetLayout");
	vkCreateDescriptorPool = (PFN_vkCreateDescriptorPool)vkGetDeviceProcAddr(device, "vkCreateDescriptorPool");
	vkDestroyDescriptorPool = (PFN_vkDestroyDescriptorPool)vkGetDeviceProcAddr(device, "vkDestroyDescriptorPool");
	vkResetDescriptorPool = (PFN_vkResetDescriptorPool)vkGetDeviceProcAddr(device, "vkResetDescriptorPool");
	vkAllocateDescriptorSets = (PFN_vkAllocateDescriptorSets)vkGetDeviceProcAddr(device, "vkAllocateDescriptorSets");
	vkFreeDescriptorSets = (PFN_vkFreeDescriptorSets)vkGetDeviceProcAddr(device, "vkFreeDescriptorSets");
	vkUpdateDescriptorSets = (PFN_vkUpdateDescriptorSets)vkGetDeviceProcAddr(device, "vkUpdateDescriptorSets");
	vkCreateFramebuffer = (PFN_vkCreateFramebuffer)vkGetDeviceProcAddr(device, "vkCreateFramebuffer");
	vkDestroyFramebuffer = (PFN_vkDestroyFramebuffer)vkGetDeviceProcAddr(device, "vkDestroyFramebuffer");
	vkCreateRenderPass = (PFN_vkCreateRenderPass)vkGetDeviceProcAddr(device, "vkCreateRenderPass");
	vkDestroyRenderPass = (PFN_vkDestroyRenderPass)vkGetDeviceProcAddr(device, "vkDestroyRenderPass");
	vkGetRenderAreaGranularity = (PFN_vkGetRenderAreaGranularity)vkGetDeviceProcAddr(device, "vkGetRenderAreaGranularity");
	vkCreateCommandPool = (PFN_vkCreateCommandPool)vkGetDeviceProcAddr(device, "vkCreateCommandPool");
	vkDestroyCommandPool = (PFN_vkDestroyCommandPool)vkGetDeviceProcAddr(device, "vkDestroyCommandPool");
	vkResetCommandPool = (PFN_vkResetCommandPool)vkGetDeviceProcAddr(device, "vkResetCommandPool");
	vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)vkGetDeviceProcAddr(device, "vkAllocateCommandBuffers");
	vkFreeCommandBuffers = (PFN_vkFreeCommandBuffers)vkGetDeviceProcAddr(device, "vkFreeCommandBuffers");
	vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer)vkGetDeviceProcAddr(device, "vkBeginCommandBuffer");
	vkEndCommandBuffer = (PFN_vkEndCommandBuffer)vkGetDeviceProcAddr(device, "vkEndCommandBuffer");
	vkResetCommandBuffer = (PFN_vkResetCommandBuffer)vkGetDeviceProcAddr(device, "vkResetCommandBuffer");
	vkCmdBindPipeline = (PFN_vkCmdBindPipeline)vkGetDeviceProcAddr(device, "vkCmdBindPipeline");
	vkCmdSetViewport = (PFN_vkCmdSetViewport)vkGetDeviceProcAddr(device, "vkCmdSetViewport");
	vkCmdSetScissor = (PFN_vkCmdSetScissor)vkGetDeviceProcAddr(device, "vkCmdSetScissor");
	vkCmdSetLineWidth = (PFN_vkCmdSetLineWidth)vkGetDeviceProcAddr(device, "vkCmdSetLineWidth");
	vkCmdSetDepthBias = (PFN_vkCmdSetDepthBias)vkGetDeviceProcAddr(device, "vkCmdSetDepthBias");
	vkCmdSetBlendConstants = (PFN_vkCmdSetBlendConstants)vkGetDeviceProcAddr(device, "vkCmdSetBlendConstants");
	vkCmdSetDepthBounds = (PFN_vkCmdSetDepthBounds)vkGetDeviceProcAddr(device, "vkCmdSetDepthBounds");
	vkCmdSetStencilCompareMask = (PFN_vkCmdSetStencilCompareMask)vkGetDeviceProcAddr(device, "vkCmdSetStencilCompareMask");
	vkCmdSetStencilWriteMask = (PFN_vkCmdSetStencilWriteMask)vkGetDeviceProcAddr(device, "vkCmdSetStencilWriteMask");
	vkCmdSetStencilReference = (PFN_vkCmdSetStencilReference)vkGetDeviceProcAddr(device, "vkCmdSetStencilReference");
	vkCmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets)vkGetDeviceProcAddr(device, "vkCmdBindDescriptorSets");
	vkCmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer)vkGetDeviceProcAddr(device, "vkCmdBindIndexBuffer");
	vkCmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers)vkGetDeviceProcAddr(device, "vkCmdBindVertexBuffers");
	vkCmdDraw = (PFN_vkCmdDraw)vkGetDeviceProcAddr(device, "vkCmdDraw");
	vkCmdDrawIndexed = (PFN_vkCmdDrawIndexed)vkGetDeviceProcAddr(device, "vkCmdDrawIndexed");
	vkCmdDrawIndirect = (PFN_vkCmdDrawIndirect)vkGetDeviceProcAddr(device, "vkCmdDrawIndirect");
	vkCmdDrawIndexedIndirect = (PFN_vkCmdDrawIndexedIndirect)vkGetDeviceProcAddr(device, "vkCmdDrawIndexedIndirect");
	vkCmdDispatch = (PFN_vkCmdDispatch)vkGetDeviceProcAddr(device, "vkCmdDispatch");
	vkCmdDispatchIndirect = (PFN_vkCmdDispatchIndirect)vkGetDeviceProcAddr(device, "vkCmdDispatchIndirect");
	vkCmdCopyBuffer = (PFN_vkCmdCopyBuffer)vkGetDeviceProcAddr(device, "vkCmdCopyBuffer");
	vkCmdCopyImage = (PFN_vkCmdCopyImage)vkGetDeviceProcAddr(device, "vkCmdCopyImage");
	vkCmdBlitImage = (PFN_vkCmdBlitImage)vkGetDeviceProcAddr(device, "vkCmdBlitImage");
	vkCmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage)vkGetDeviceProcAddr(device, "vkCmdCopyBufferToImage");
	vkCmdCopyImageToBuffer = (PFN_vkCmdCopyImageToBuffer)vkGetDeviceProcAddr(device, "vkCmdCopyImageToBuffer");
	vkCmdUpdateBuffer = (PFN_vkCmdUpdateBuffer)vkGetDeviceProcAddr(device, "vkCmdUpdateBuffer");
	vkCmdFillBuffer = (PFN_vkCmdFillBuffer)vkGetDeviceProcAddr(device, "vkCmdFillBuffer");
	vkCmdClearColorImage = (PFN_vkCmdClearColorImage)vkGetDeviceProcAddr(device, "vkCmdClearColorImage");
	vkCmdClearDepthStencilImage = (PFN_vkCmdClearDepthStencilImage)vkGetDeviceProcAddr(device, "vkCmdClearDepthStencilImage");
	vkCmdClearAttachments = (PFN_vkCmdClearAttachments)vkGetDeviceProcAddr(device, "vkCmdClearAttachments");
	vkCmdResolveImage = (PFN_vkCmdResolveImage)vkGetDeviceProcAddr(device, "vkCmdResolveImage");
	vkCmdSetEvent = (PFN_vkCmdSetEvent)vkGetDeviceProcAddr(device, "vkCmdSetEvent");
	vkCmdResetEvent = (PFN_vkCmdResetEvent)vkGetDeviceProcAddr(device, "vkCmdResetEvent");
	vkCmdWaitEvents = (PFN_vkCmdWaitEvents)vkGetDeviceProcAddr(device, "vkCmdWaitEvents");
	vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier)vkGetDeviceProcAddr(device, "vkCmdPipelineBarrier");
	vkCmdBeginQuery = (PFN_vkCmdBeginQuery)vkGetDeviceProcAddr(device, "vkCmdBeginQuery");
	vkCmdEndQuery = (PFN_vkCmdEndQuery)vkGetDeviceProcAddr(device, "vkCmdEndQuery");
	vkCmdResetQueryPool = (PFN_vkCmdResetQueryPool)vkGetDeviceProcAddr(device, "vkCmdResetQueryPool");
	vkCmdWriteTimestamp = (PFN_vkCmdWriteTimestamp)vkGetDeviceProcAddr(device, "vkCmdWriteTimestamp");
	vkCmdCopyQueryPoolResults = (PFN_vkCmdCopyQueryPoolResults)vkGetDeviceProcAddr(device, "vkCmdCopyQueryPoolResults");
	vkCmdPushConstants = (PFN_vkCmdPushConstants)vkGetDeviceProcAddr(device, "vkCmdPushConstants");
	vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass)vkGetDeviceProcAddr(device, "vkCmdBeginRenderPass");
	vkCmdNextSubpass = (PFN_vkCmdNextSubpass)vkGetDeviceProcAddr(device, "vkCmdNextSubpass");
	vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass)vkGetDeviceProcAddr(device, "vkCmdEndRenderPass");
	vkCmdExecuteCommands = (PFN_vkCmdExecuteCommands)vkGetDeviceProcAddr(device, "vkCmdExecuteCommands");
#endif // defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
	// Device commands
	vkBindBufferMemory2 = (PFN_vkBindBufferMemory2)vkGetDeviceProcAddr(device, "vkBindBufferMemory2");
	vkBindImageMemory2 = (PFN_vkBindImageMemory2)vkGetDeviceProcAddr(device, "vkBindImageMemory2");
	vkGetDeviceGroupPeerMemoryFeatures = (PFN_vkGetDeviceGroupPeerMemoryFeatures)vkGetDeviceProcAddr(device, "vkGetDeviceGroupPeerMemoryFeatures");
	vkCmdSetDeviceMask = (PFN_vkCmdSetDeviceMask)vkGetDeviceProcAddr(device, "vkCmdSetDeviceMask");
	vkCmdDispatchBase = (PFN_vkCmdDispatchBase)vkGetDeviceProcAddr(device, "vkCmdDispatchBase");
	vkGetImageMemoryRequirements2 = (PFN_vkGetImageMemoryRequirements2)vkGetDeviceProcAddr(device, "vkGetImageMemoryRequirements2");
	vkGetBufferMemoryRequirements2 = (PFN_vkGetBufferMemoryRequirements2)vkGetDeviceProcAddr(device, "vkGetBufferMemoryRequirements2");
	vkGetImageSparseMemoryRequirements2 = (PFN_vkGetImageSparseMemoryRequirements2)vkGetDeviceProcAddr(device, "vkGetImageSparseMemoryRequirements2");
	vkTrimCommandPool = (PFN_vkTrimCommandPool)vkGetDeviceProcAddr(device, "vkTrimCommandPool");
	vkGetDeviceQueue2 = (PFN_vkGetDeviceQueue2)vkGetDeviceProcAddr(device, "vkGetDeviceQueue2");
	vkCreateSamplerYcbcrConversion = (PFN_vkCreateSamplerYcbcrConversion)vkGetDeviceProcAddr(device, "vkCreateSamplerYcbcrConversion");
	vkDestroySamplerYcbcrConversion = (PFN_vkDestroySamplerYcbcrConversion)vkGetDeviceProcAddr(device, "vkDestroySamplerYcbcrConversion");
	vkCreateDescriptorUpdateTemplate = (PFN_vkCreateDescriptorUpdateTemplate)vkGetDeviceProcAddr(device, "vkCreateDescriptorUpdateTemplate");
	vkDestroyDescriptorUpdateTemplate = (PFN_vkDestroyDescriptorUpdateTemplate)vkGetDeviceProcAddr(device, "vkDestroyDescriptorUpdateTemplate");
	vkUpdateDescriptorSetWithTemplate = (PFN_vkUpdateDescriptorSetWithTemplate)vkGetDeviceProcAddr(device, "vkUpdateDescriptorSetWithTemplate");
	vkGetDescriptorSetLayoutSupport = (PFN_vkGetDescriptorSetLayoutSupport)vkGetDeviceProcAddr(device, "vkGetDescriptorSetLayoutSupport");
#endif // defined(VK_VERSION_1_1)
#if defined(VK_VERSION_1_2)
	// Device commands
	vkCmdDrawIndirectCount = (PFN_vkCmdDrawIndirectCount)vkGetDeviceProcAddr(device, "vkCmdDrawIndirectCount");
	vkCmdDrawIndexedIndirectCount = (PFN_vkCmdDrawIndexedIndirectCount)vkGetDeviceProcAddr(device, "vkCmdDrawIndexedIndirectCount");
	vkCreateRenderPass2 = (PFN_vkCreateRenderPass2)vkGetDeviceProcAddr(device, "vkCreateRenderPass2");
	vkCmdBeginRenderPass2 = (PFN_vkCmdBeginRenderPass2)vkGetDeviceProcAddr(device, "vkCmdBeginRenderPass2");
	vkCmdNextSubpass2 = (PFN_vkCmdNextSubpass2)vkGetDeviceProcAddr(device, "vkCmdNextSubpass2");
	vkCmdEndRenderPass2 = (PFN_vkCmdEndRenderPass2)vkGetDeviceProcAddr(device, "vkCmdEndRenderPass2");
	vkResetQueryPool = (PFN_vkResetQueryPool)vkGetDeviceProcAddr(device, "vkResetQueryPool");
	vkGetSemaphoreCounterValue = (PFN_vkGetSemaphoreCounterValue)vkGetDeviceProcAddr(device, "vkGetSemaphoreCounterValue");
	vkWaitSemaphores = (PFN_vkWaitSemaphores)vkGetDeviceProcAddr(device, "vkWaitSemaphores");
	vkSignalSemaphore = (PFN_vkSignalSemaphore)vkGetDeviceProcAddr(device, "vkSignalSemaphore");
	vkGetBufferDeviceAddress = (PFN_vkGetBufferDeviceAddress)vkGetDeviceProcAddr(device, "vkGetBufferDeviceAddress");
	vkGetBufferOpaqueCaptureAddress = (PFN_vkGetBufferOpaqueCaptureAddress)vkGetDeviceProcAddr(device, "vkGetBufferOpaqueCaptureAddress");
	vkGetDeviceMemoryOpaqueCaptureAddress = (PFN_vkGetDeviceMemoryOpaqueCaptureAddress)vkGetDeviceProcAddr(device, "vkGetDeviceMemoryOpaqueCaptureAddress");
#endif // defined(VK_VERSION_1_2)
#if defined(VK_VERSION_1_3)
	// Device commands
	vkCreatePrivateDataSlot = (PFN_vkCreatePrivateDataSlot)vkGetDeviceProcAddr(device, "vkCreatePrivateDataSlot");
	vkDestroyPrivateDataSlot = (PFN_vkDestroyPrivateDataSlot)vkGetDeviceProcAddr(device, "vkDestroyPrivateDataSlot");
	vkSetPrivateData = (PFN_vkSetPrivateData)vkGetDeviceProcAddr(device, "vkSetPrivateData");
	vkGetPrivateData = (PFN_vkGetPrivateData)vkGetDeviceProcAddr(device, "vkGetPrivateData");
	vkCmdSetEvent2 = (PFN_vkCmdSetEvent2)vkGetDeviceProcAddr(device, "vkCmdSetEvent2");
	vkCmdResetEvent2 = (PFN_vkCmdResetEvent2)vkGetDeviceProcAddr(device, "vkCmdResetEvent2");
	vkCmdWaitEvents2 = (PFN_vkCmdWaitEvents2)vkGetDeviceProcAddr(device, "vkCmdWaitEvents2");
	vkCmdPipelineBarrier2 = (PFN_vkCmdPipelineBarrier2)vkGetDeviceProcAddr(device, "vkCmdPipelineBarrier2");
	vkCmdWriteTimestamp2 = (PFN_vkCmdWriteTimestamp2)vkGetDeviceProcAddr(device, "vkCmdWriteTimestamp2");
	vkQueueSubmit2 = (PFN_vkQueueSubmit2)vkGetDeviceProcAddr(device, "vkQueueSubmit2");
	vkCmdCopyBuffer2 = (PFN_vkCmdCopyBuffer2)vkGetDeviceProcAddr(device, "vkCmdCopyBuffer2");
	vkCmdCopyImage2 = (PFN_vkCmdCopyImage2)vkGetDeviceProcAddr(device, "vkCmdCopyImage2");
	vkCmdCopyBufferToImage2 = (PFN_vkCmdCopyBufferToImage2)vkGetDeviceProcAddr(device, "vkCmdCopyBufferToImage2");
	vkCmdCopyImageToBuffer2 = (PFN_vkCmdCopyImageToBuffer2)vkGetDeviceProcAddr(device, "vkCmdCopyImageToBuffer2");
	vkCmdBlitImage2 = (PFN_vkCmdBlitImage2)vkGetDeviceProcAddr(device, "vkCmdBlitImage2");
	vkCmdResolveImage2 = (PFN_vkCmdResolveImage2)vkGetDeviceProcAddr(device, "vkCmdResolveImage2");
	vkCmdBeginRendering = (PFN_vkCmdBeginRendering)vkGetDeviceProcAddr(device, "vkCmdBeginRendering");
	vkCmdEndRendering = (PFN_vkCmdEndRendering)vkGetDeviceProcAddr(device, "vkCmdEndRendering");
	vkCmdSetCullMode = (PFN_vkCmdSetCullMode)vkGetDeviceProcAddr(device, "vkCmdSetCullMode");
	vkCmdSetFrontFace = (PFN_vkCmdSetFrontFace)vkGetDeviceProcAddr(device, "vkCmdSetFrontFace");
	vkCmdSetPrimitiveTopology = (PFN_vkCmdSetPrimitiveTopology)vkGetDeviceProcAddr(device, "vkCmdSetPrimitiveTopology");
	vkCmdSetViewportWithCount = (PFN_vkCmdSetViewportWithCount)vkGetDeviceProcAddr(device, "vkCmdSetViewportWithCount");
	vkCmdSetScissorWithCount = (PFN_vkCmdSetScissorWithCount)vkGetDeviceProcAddr(device, "vkCmdSetScissorWithCount");
	vkCmdBindVertexBuffers2 = (PFN_vkCmdBindVertexBuffers2)vkGetDeviceProcAddr(device, "vkCmdBindVertexBuffers2");
	vkCmdSetDepthTestEnable = (PFN_vkCmdSetDepthTestEnable)vkGetDeviceProcAddr(device, "vkCmdSetDepthTestEnable");
	vkCmdSetDepthWriteEnable = (PFN_vkCmdSetDepthWriteEnable)vkGetDeviceProcAddr(device, "vkCmdSetDepthWriteEnable");
	vkCmdSetDepthCompareOp = (PFN_vkCmdSetDepthCompareOp)vkGetDeviceProcAddr(device, "vkCmdSetDepthCompareOp");
	vkCmdSetDepthBoundsTestEnable = (PFN_vkCmdSetDepthBoundsTestEnable)vkGetDeviceProcAddr(device, "vkCmdSetDepthBoundsTestEnable");
	vkCmdSetStencilTestEnable = (PFN_vkCmdSetStencilTestEnable)vkGetDeviceProcAddr(device, "vkCmdSetStencilTestEnable");
	vkCmdSetStencilOp = (PFN_vkCmdSetStencilOp)vkGetDeviceProcAddr(device, "vkCmdSetStencilOp");
	vkCmdSetRasterizerDiscardEnable = (PFN_vkCmdSetRasterizerDiscardEnable)vkGetDeviceProcAddr(device, "vkCmdSetRasterizerDiscardEnable");
	vkCmdSetDepthBiasEnable = (PFN_vkCmdSetDepthBiasEnable)vkGetDeviceProcAddr(device, "vkCmdSetDepthBiasEnable");
	vkCmdSetPrimitiveRestartEnable = (PFN_vkCmdSetPrimitiveRestartEnable)vkGetDeviceProcAddr(device, "vkCmdSetPrimitiveRestartEnable");
	vkGetDeviceBufferMemoryRequirements = (PFN_vkGetDeviceBufferMemoryRequirements)vkGetDeviceProcAddr(device, "vkGetDeviceBufferMemoryRequirements");
	vkGetDeviceImageMemoryRequirements = (PFN_vkGetDeviceImageMemoryRequirements)vkGetDeviceProcAddr(device, "vkGetDeviceImageMemoryRequirements");
	vkGetDeviceImageSparseMemoryRequirements = (PFN_vkGetDeviceImageSparseMemoryRequirements)vkGetDeviceProcAddr(device, "vkGetDeviceImageSparseMemoryRequirements");
#endif // defined(VK_VERSION_1_3)
}


#if defined(VK_VERSION_1_0)
// Root commands
PFN_vkCreateInstance vkCreateInstance;
PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties;
PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties;
// Instance commands
PFN_vkDestroyInstance vkDestroyInstance;
PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices;
PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures;
PFN_vkGetPhysicalDeviceFormatProperties vkGetPhysicalDeviceFormatProperties;
PFN_vkGetPhysicalDeviceImageFormatProperties vkGetPhysicalDeviceImageFormatProperties;
PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties;
PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties;
PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr;
PFN_vkCreateDevice vkCreateDevice;
PFN_vkEnumerateDeviceExtensionProperties vkEnumerateDeviceExtensionProperties;
PFN_vkEnumerateDeviceLayerProperties vkEnumerateDeviceLayerProperties;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties vkGetPhysicalDeviceSparseImageFormatProperties;
// Device commands
PFN_vkDestroyDevice vkDestroyDevice;
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
// Root commands
PFN_vkEnumerateInstanceVersion vkEnumerateInstanceVersion;
// Instance commands
PFN_vkEnumeratePhysicalDeviceGroups vkEnumeratePhysicalDeviceGroups;
PFN_vkGetPhysicalDeviceFeatures2 vkGetPhysicalDeviceFeatures2;
PFN_vkGetPhysicalDeviceProperties2 vkGetPhysicalDeviceProperties2;
PFN_vkGetPhysicalDeviceFormatProperties2 vkGetPhysicalDeviceFormatProperties2;
PFN_vkGetPhysicalDeviceImageFormatProperties2 vkGetPhysicalDeviceImageFormatProperties2;
PFN_vkGetPhysicalDeviceQueueFamilyProperties2 vkGetPhysicalDeviceQueueFamilyProperties2;
PFN_vkGetPhysicalDeviceMemoryProperties2 vkGetPhysicalDeviceMemoryProperties2;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 vkGetPhysicalDeviceSparseImageFormatProperties2;
PFN_vkGetPhysicalDeviceExternalBufferProperties vkGetPhysicalDeviceExternalBufferProperties;
PFN_vkGetPhysicalDeviceExternalFenceProperties vkGetPhysicalDeviceExternalFenceProperties;
PFN_vkGetPhysicalDeviceExternalSemaphoreProperties vkGetPhysicalDeviceExternalSemaphoreProperties;
// Device commands
PFN_vkBindBufferMemory2 vkBindBufferMemory2;
PFN_vkBindImageMemory2 vkBindImageMemory2;
PFN_vkGetDeviceGroupPeerMemoryFeatures vkGetDeviceGroupPeerMemoryFeatures;
PFN_vkCmdSetDeviceMask vkCmdSetDeviceMask;
PFN_vkCmdDispatchBase vkCmdDispatchBase;
PFN_vkGetImageMemoryRequirements2 vkGetImageMemoryRequirements2;
PFN_vkGetBufferMemoryRequirements2 vkGetBufferMemoryRequirements2;
PFN_vkGetImageSparseMemoryRequirements2 vkGetImageSparseMemoryRequirements2;
PFN_vkTrimCommandPool vkTrimCommandPool;
PFN_vkGetDeviceQueue2 vkGetDeviceQueue2;
PFN_vkCreateSamplerYcbcrConversion vkCreateSamplerYcbcrConversion;
PFN_vkDestroySamplerYcbcrConversion vkDestroySamplerYcbcrConversion;
PFN_vkCreateDescriptorUpdateTemplate vkCreateDescriptorUpdateTemplate;
PFN_vkDestroyDescriptorUpdateTemplate vkDestroyDescriptorUpdateTemplate;
PFN_vkUpdateDescriptorSetWithTemplate vkUpdateDescriptorSetWithTemplate;
PFN_vkGetDescriptorSetLayoutSupport vkGetDescriptorSetLayoutSupport;
#endif // defined(VK_VERSION_1_1)
#if defined(VK_VERSION_1_2)
// Device commands
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
// Instance commands
PFN_vkGetPhysicalDeviceToolProperties vkGetPhysicalDeviceToolProperties;
// Device commands
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
