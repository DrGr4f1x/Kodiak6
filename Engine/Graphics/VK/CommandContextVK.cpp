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

#include "CommandContextVK.h"

#include "DeviceVK.h"
#include "FormatsVK.h"
#include "GpuResourceVK.h"
#include "PixelBufferVK.h"
#include "QueueVK.h"


using namespace std;


namespace Kodiak::VK
{

CommandContext::CommandContext(CommandListType type)
{
	m_type = type;
}


CommandContext::~CommandContext() = default;


uint64_t CommandContext::Finish(bool bWaitForCompletion)
{
	assert(m_type == CommandListType::Direct || m_type == CommandListType::Compute);

	FlushResourceBarriers();

	// TODO
#if 0
	if (m_ID.length() > 0)
	{
		EngineProfiling::EndBlock(this);
	}
#endif

#if ENABLE_VULKAN_DEBUG_MARKERS
	if (m_hasPendingDebugEvent)
	{
		EndEvent();
		m_hasPendingDebugEvent = false;
	}
#endif

	vkEndCommandBuffer(m_commandBuffer);

	auto& queue = m_device->GetQueue(m_type);
	
	uint64_t fenceValue = queue.ExecuteCommandList(m_commandBuffer);
	queue.DiscardCommandBuffer(fenceValue, m_commandBuffer);
	m_commandBuffer = VK_NULL_HANDLE;

	// Recycle dynamic allocations
	//m_cpuLinearAllocator.CleanupUsedPages(fenceValue);
	//m_dynamicDescriptorPool.CleanupUsedPools(fenceValue);

	if (bWaitForCompletion)
	{
		queue.WaitForFence(fenceValue);
	}

	m_device->FreeContext(this);

	return fenceValue;
}


void CommandContext::BeginEvent(const string& label)
{
#if ENABLE_VULKAN_DEBUG_MARKERS
	VkDebugUtilsLabelEXT labelInfo{ VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT };
	labelInfo.color[0] = 0.0f;
	labelInfo.color[1] = 0.0f;
	labelInfo.color[2] = 0.0f;
	labelInfo.color[3] = 0.0f;
	labelInfo.pLabelName = label.c_str();
	vkCmdBeginDebugUtilsLabelEXT(m_commandBuffer, &labelInfo);
#endif
}


void CommandContext::EndEvent()
{
#if ENABLE_VULKAN_DEBUG_MARKERS
	vkCmdEndDebugUtilsLabelEXT(m_commandBuffer);
#endif
}


void CommandContext::SetMarker(const string& label)
{
#if ENABLE_VULKAN_DEBUG_MARKERS
	VkDebugUtilsLabelEXT labelInfo{ VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT };
	labelInfo.color[0] = 0.0f;
	labelInfo.color[1] = 0.0f;
	labelInfo.color[2] = 0.0f;
	labelInfo.color[3] = 0.0f;
	labelInfo.pLabelName = label.c_str();
	vkCmdInsertDebugUtilsLabelEXT(m_commandBuffer, &labelInfo);
#endif
}


void CommandContext::TransitionResource(IGpuResource* gpuResource, ResourceState newState, bool bFlushImmediate)
{
	auto* vkGpuResource = dynamic_cast<GpuResource*>(gpuResource);

	if (vkGpuResource->IsImageResource())
	{
		auto* vkPixelBuffer = dynamic_cast<PixelBuffer*>(gpuResource);

		TextureBarrier barrier{};
		barrier.image = vkPixelBuffer->GetImage();
		barrier.format = FormatToVulkan(vkPixelBuffer->GetFormat());
		barrier.imageAspect = GetImageAspect(vkPixelBuffer->GetImageAspect());
		barrier.beforeState = vkPixelBuffer->GetUsageState();
		barrier.afterState = newState;
		barrier.numMips = vkPixelBuffer->GetNumMips();
		barrier.mipLevel = 0;
		barrier.arraySizeOrDepth = vkPixelBuffer->GetArraySize();
		barrier.arraySlice = 0;
		barrier.bWholeTexture = true;

		m_textureBarriers.push_back(barrier);

		vkPixelBuffer->m_usageState = newState;
	}
	else if (vkGpuResource->IsBufferResource())
	{
		// TODO - Vulkan GPU buffer support
		BufferBarrier barrier{};
	}

	if (bFlushImmediate || GetPendingBarrierCount() >= 16)
	{
		FlushResourceBarriers();
	}
}


void CommandContext::InsertUAVBarrier(IGpuResource* gpuResource, bool bFlushImmediate)
{
	auto* vkGpuResource = dynamic_cast<GpuResource*>(gpuResource);

	assert_msg(HasFlag(vkGpuResource->GetUsageState(), ResourceState::UnorderedAccess), "Resource must be in UnorderedAccess state to insert a UAV barrier");

	TransitionResource(gpuResource, vkGpuResource->GetUsageState(), bFlushImmediate);
}


void CommandContext::FlushResourceBarriers()
{
	for (const auto& barrier : m_textureBarriers)
	{
		ResourceStateMapping before = GetResourceStateMapping(barrier.beforeState);
		ResourceStateMapping after = GetResourceStateMapping(barrier.afterState);

		assert(after.imageLayout != VK_IMAGE_LAYOUT_UNDEFINED);

		VkImageSubresourceRange subresourceRange{};
		subresourceRange.aspectMask = barrier.imageAspect;
		subresourceRange.baseArrayLayer = barrier.arraySlice;
		subresourceRange.baseMipLevel = barrier.mipLevel;
		subresourceRange.layerCount = barrier.arraySizeOrDepth;
		subresourceRange.levelCount = barrier.numMips;

		VkImageMemoryBarrier2 vkBarrier{ VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2 };
		vkBarrier.srcAccessMask = before.accessFlags;
		vkBarrier.dstAccessMask = after.accessFlags;
		vkBarrier.srcStageMask = before.stageFlags;
		vkBarrier.dstStageMask = after.stageFlags;
		vkBarrier.oldLayout = before.imageLayout;
		vkBarrier.newLayout = after.imageLayout;
		vkBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		vkBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		vkBarrier.image = barrier.image;
		vkBarrier.subresourceRange = subresourceRange;

		m_imageMemoryBarriers.push_back(vkBarrier);
	}

	if (!m_imageMemoryBarriers.empty())
	{
		VkDependencyInfo dependencyInfo{ VK_STRUCTURE_TYPE_DEPENDENCY_INFO };
		dependencyInfo.imageMemoryBarrierCount = (uint32_t)m_imageMemoryBarriers.size();
		dependencyInfo.pImageMemoryBarriers = m_imageMemoryBarriers.data();

		vkCmdPipelineBarrier2(m_commandBuffer, &dependencyInfo);

		m_imageMemoryBarriers.clear();
	}

	m_textureBarriers.clear();

	// TODO - Vulkan GPU buffer support
}


void CommandContext::Reset()
{
	assert(m_commandBuffer == VK_NULL_HANDLE);
	m_commandBuffer = m_device->GetQueue(m_type).RequestCommandBuffer();
}


GraphicsContext::~GraphicsContext() = default;


ComputeContext::~ComputeContext() = default;

} // namespace Kodiak::VK