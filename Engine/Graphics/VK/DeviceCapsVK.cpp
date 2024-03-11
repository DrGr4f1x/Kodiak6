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

#include "DeviceCapsVK.h"

#include "Graphics\GraphicsEnums.h"

#include "GraphicsDeviceVK.h"
#include "LoaderVk.h"
#include "StringsVK.h"


using namespace Kodiak;
using namespace Kodiak::VK;
using namespace std;


DeviceCaps::DeviceCaps()
{
	// Attach pNext pointers
	properties2.pNext = &properties11;
	properties11.pNext = &properties12;
	properties12.pNext = &properties13;
	properties13.pNext = nullptr;

	memoryProperties2.pNext = &memoryBudgetProperties;
	memoryBudgetProperties.pNext = nullptr;

	features2.pNext = &features11;
	features11.pNext = &features12;
	features12.pNext = &features13;
	features13.pNext = nullptr;
}


void DeviceCaps::ReadCaps(VkPhysicalDevice physicalDevice)
{
	if (!m_capsRead)
	{
		vkGetPhysicalDeviceProperties2(physicalDevice, &properties2);
		vkGetPhysicalDeviceMemoryProperties2(physicalDevice, &memoryProperties2);
		vkGetPhysicalDeviceFeatures2(physicalDevice, &features2);

		version = DecodeVulkanVersion(properties.apiVersion);

		m_capsRead = true;
	}
}


void DeviceCaps::LogCaps()
{
	LogInfo(LogVulkan) << "  Device Caps" << endl;

	constexpr const char* formatStr = "      {:48} {}";
	constexpr const char* formatStr2 = "        {:46} {}";
	constexpr const char* formatStr3 = "        {:46} {:#x}";

	// Vulkan 1.0 properties
	LogInfo(LogVulkan) << "    Vulkan 1.0 properties" << endl;
	LogInfo(LogVulkan) << format(formatStr, "apiVersion:", version) << endl;
	LogInfo(LogVulkan) << format("      {:48} {:#x}", "driverVersion:", properties.driverVersion) << endl;
	LogInfo(LogVulkan) << format("      {:48} {} ({:#x})", "vendorID:", VendorIdToString(properties.vendorID), properties.vendorID) << endl;
	LogInfo(LogVulkan) << format("      {:48} {:#x}", "deviceID:", properties.deviceID) << endl;
	LogInfo(LogVulkan) << format(formatStr, "deviceType:", properties.deviceType) << endl;
	// Vulkan 1.0 properties - limits
	VkPhysicalDeviceLimits& limits = properties.limits;
	LogInfo(LogVulkan) << "    Vulkan 1.0 properties.limits" << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxImageDimension1D:", limits.maxImageDimension1D) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxImageDimension2D:", limits.maxImageDimension2D) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxImageDimension3D:", limits.maxImageDimension3D) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxImageDimensionCube:", limits.maxImageDimensionCube) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxImageArrayLayers:", limits.maxImageArrayLayers) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxTexelBufferElements:", limits.maxTexelBufferElements) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxUniformBufferRange:", limits.maxUniformBufferRange) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxStorageBufferRange:", limits.maxStorageBufferRange) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxPushConstantsSize:", limits.maxPushConstantsSize) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxMemoryAllocationCount:", limits.maxMemoryAllocationCount) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxSamplerAllocationCount:", limits.maxSamplerAllocationCount) << endl;
	LogInfo(LogVulkan) << format(formatStr3, "bufferImageGranularity:", limits.bufferImageGranularity) << endl;
	LogInfo(LogVulkan) << format(formatStr3, "sparseAddressSpaceSize:", limits.sparseAddressSpaceSize) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxBoundDescriptorSets:", limits.maxBoundDescriptorSets) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxPerStageDescriptorSamplers:", limits.maxPerStageDescriptorSamplers) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxPerStageDescriptorUniformBuffers:", limits.maxPerStageDescriptorUniformBuffers) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxPerStageDescriptorStorageBuffers:", limits.maxPerStageDescriptorStorageBuffers) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxPerStageDescriptorSampledImages:", limits.maxPerStageDescriptorSampledImages) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxPerStageDescriptorStorageImages:", limits.maxPerStageDescriptorStorageImages) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxPerStageDescriptorInputAttachments:", limits.maxPerStageDescriptorInputAttachments) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxPerStageResources:", limits.maxPerStageResources) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxDescriptorSetSamplers:", limits.maxDescriptorSetSamplers) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxDescriptorSetUniformBuffers:", limits.maxDescriptorSetUniformBuffers) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxDescriptorSetUniformBuffersDynamic:", limits.maxDescriptorSetUniformBuffersDynamic) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxDescriptorSetStorageBuffers:", limits.maxDescriptorSetStorageBuffers) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxDescriptorSetStorageBuffersDynamic:", limits.maxDescriptorSetStorageBuffersDynamic) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxDescriptorSetSampledImages:", limits.maxDescriptorSetSampledImages) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxDescriptorSetStorageImages:", limits.maxDescriptorSetStorageImages) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxDescriptorSetInputAttachments:", limits.maxDescriptorSetInputAttachments) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxVertexInputAttributes:", limits.maxVertexInputAttributes) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxVertexInputBindings:", limits.maxVertexInputBindings) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxVertexInputAttributeOffset:", limits.maxVertexInputAttributeOffset) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxVertexInputBindingStride:", limits.maxVertexInputBindingStride) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxVertexOutputComponents:", limits.maxVertexOutputComponents) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxTessellationGenerationLevel:", limits.maxTessellationGenerationLevel) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxTessellationPatchSize:", limits.maxTessellationPatchSize) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxTessellationControlPerVertexInputComponents:", limits.maxTessellationControlPerVertexInputComponents) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxTessellationControlPerVertexOutputComponents:", limits.maxTessellationControlPerVertexOutputComponents) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxTessellationControlPerPatchOutputComponents:", limits.maxTessellationControlPerPatchOutputComponents) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxTessellationControlTotalOutputComponents:", limits.maxTessellationControlTotalOutputComponents) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxTessellationEvaluationInputComponents:", limits.maxTessellationEvaluationInputComponents) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxTessellationEvaluationOutputComponents:", limits.maxTessellationEvaluationOutputComponents) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxGeometryShaderInvocations:", limits.maxGeometryShaderInvocations) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxGeometryInputComponents:", limits.maxGeometryInputComponents) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxGeometryOutputComponents:", limits.maxGeometryOutputComponents) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxGeometryOutputVertices:", limits.maxGeometryOutputVertices) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxGeometryTotalOutputComponents:", limits.maxGeometryTotalOutputComponents) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxFragmentInputComponents:", limits.maxFragmentInputComponents) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxFragmentOutputAttachments:", limits.maxFragmentOutputAttachments) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxFragmentDualSrcAttachments:", limits.maxFragmentDualSrcAttachments) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxFragmentCombinedOutputResources:", limits.maxFragmentCombinedOutputResources) << endl;
	LogInfo(LogVulkan) << format("        {:46} [{}, {}, {}]", "maxComputeWorkGroupCount:", 
		limits.maxComputeWorkGroupCount[0],
		limits.maxComputeWorkGroupCount[1],
		limits.maxComputeWorkGroupCount[2]) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxComputeWorkGroupInvocations:", limits.maxComputeWorkGroupInvocations) << endl;
	LogInfo(LogVulkan) << format("        {:46} [{}, {}, {}]", "maxComputeWorkGroupSize:",
		limits.maxComputeWorkGroupSize[0],
		limits.maxComputeWorkGroupSize[1],
		limits.maxComputeWorkGroupSize[2]) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "subPixelPrecisionBits:", limits.subPixelPrecisionBits) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "subTexelPrecisionBits:", limits.subTexelPrecisionBits) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "mipmapPrecisionBits:", limits.mipmapPrecisionBits) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxDrawIndexedIndexValue:", limits.maxDrawIndexedIndexValue) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxDrawIndirectCount:", limits.maxDrawIndirectCount) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxSamplerLodBias:", limits.maxSamplerLodBias) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxSamplerAnisotropy:", limits.maxSamplerAnisotropy) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxViewports:", limits.maxViewports) << endl;
	LogInfo(LogVulkan) << format("        {:46} [{}, {}]", "maxViewportDimensions:",
		limits.maxViewportDimensions[0],
		limits.maxViewportDimensions[1]) << endl;
	LogInfo(LogVulkan) << format("        {:46} [{}, {}]", "viewportBoundsRange:",
		limits.viewportBoundsRange[0],
		limits.viewportBoundsRange[1]) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "viewportSubPixelBits:", limits.viewportSubPixelBits) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "minMemoryMapAlignment:", limits.minMemoryMapAlignment) << endl;
	LogInfo(LogVulkan) << format(formatStr3, "minTexelBufferOffsetAlignment:", limits.minTexelBufferOffsetAlignment) << endl;
	LogInfo(LogVulkan) << format(formatStr3, "minUniformBufferOffsetAlignment:", limits.minUniformBufferOffsetAlignment) << endl;
	LogInfo(LogVulkan) << format(formatStr3, "minStorageBufferOffsetAlignment:", limits.minStorageBufferOffsetAlignment) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "subPixelInterpolationOffsetBits:", limits.subPixelInterpolationOffsetBits) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxFramebufferWidth:", limits.maxFramebufferWidth) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxFramebufferHeight:", limits.maxFramebufferHeight) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxFramebufferLayers:", limits.maxFramebufferLayers) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "framebufferColorSampleCounts:", VkSampleCountFlagsToString(limits.framebufferColorSampleCounts)) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "framebufferDepthSampleCounts:", VkSampleCountFlagsToString(limits.framebufferDepthSampleCounts)) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "framebufferStencilSampleCounts:", VkSampleCountFlagsToString(limits.framebufferStencilSampleCounts)) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "framebufferNoAttachmentsSampleCounts:", VkSampleCountFlagsToString(limits.framebufferNoAttachmentsSampleCounts)) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxColorAttachments:", limits.maxColorAttachments) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "sampledImageColorSampleCounts:", VkSampleCountFlagsToString(limits.sampledImageColorSampleCounts)) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "sampledImageIntegerSampleCounts:", VkSampleCountFlagsToString(limits.sampledImageIntegerSampleCounts)) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "sampledImageDepthSampleCounts:", VkSampleCountFlagsToString(limits.sampledImageDepthSampleCounts)) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "sampledImageStencilSampleCounts:", VkSampleCountFlagsToString(limits.sampledImageStencilSampleCounts)) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "storageImageSampleCounts:", VkSampleCountFlagsToString(limits.storageImageSampleCounts)) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxSampleMaskWords:", limits.maxSampleMaskWords) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "timestampComputeAndGraphics:", (bool)limits.timestampComputeAndGraphics) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "timestampPeriod:", limits.timestampPeriod) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxClipDistances:", limits.maxClipDistances) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxCullDistances:", limits.maxCullDistances) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxCombinedClipAndCullDistances:", limits.maxCombinedClipAndCullDistances) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "discreteQueuePriorities:", limits.discreteQueuePriorities) << endl;
	LogInfo(LogVulkan) << format("        {:46} [{}, {}]", "pointSizeRange:",
		limits.pointSizeRange[0],
		limits.pointSizeRange[1]) << endl;
	LogInfo(LogVulkan) << format("        {:46} [{}, {}]", "lineWidthRange:",
		limits.lineWidthRange[0],
		limits.lineWidthRange[1]) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "pointSizeGranularity:", limits.pointSizeGranularity) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "lineWidthGranularity:", limits.lineWidthGranularity) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "strictLines:", (bool)limits.strictLines) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "standardSampleLocations:", (bool)limits.standardSampleLocations) << endl;
	LogInfo(LogVulkan) << format(formatStr3, "optimalBufferCopyOffsetAlignment:", limits.optimalBufferCopyOffsetAlignment) << endl;
	LogInfo(LogVulkan) << format(formatStr3, "optimalBufferCopyRowPitchAlignment:", limits.optimalBufferCopyRowPitchAlignment) << endl;
	LogInfo(LogVulkan) << format(formatStr3, "nonCoherentAtomSize:", limits.nonCoherentAtomSize) << endl;

	// Vulkan 1.1 properties
	LogInfo(LogVulkan) << format(formatStr2, "deviceUUID:", AsUUID(properties11.deviceUUID)) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "driverUUID:", AsUUID(properties11.driverUUID)) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "deviceLUID:", AsLUID(properties11.deviceLUID)) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "deviceNodeMask:", properties11.deviceNodeMask) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "deviceLUIDValid:", (bool)properties11.deviceLUIDValid) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "subgroupSize: ", properties11.subgroupSize) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "subgroupSupportedStages:", VkShaderStageFlagsToString(properties11.subgroupSupportedStages)) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "subgroupSupportedOperations:", VkSubgroupFeatureFlagsToString(properties11.subgroupSupportedOperations)) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "subgroupQuadOperationsInAllStages:", (bool)properties11.subgroupQuadOperationsInAllStages) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "pointClippingBehavior", properties11.pointClippingBehavior) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxMultiviewViewCount:", properties11.maxMultiviewViewCount) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxMultiviewInstanceIndex:", properties11.maxMultiviewInstanceIndex) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "proptectedNoFault:", (bool)properties11.protectedNoFault) << endl;
	LogInfo(LogVulkan) << format(formatStr2, "maxPerSetDescriptors:", properties11.maxPerSetDescriptors) << endl;
	LogInfo(LogVulkan) << format(formatStr3, "maxMemoryAllocationSize:", properties11.maxMemoryAllocationSize) << endl;
}