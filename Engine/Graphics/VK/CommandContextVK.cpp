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


void CommandContext::HACK_TransitionImageToPresent(VkImage image)
{
	VkImageMemoryBarrier barrierDesc{ VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER };
	barrierDesc.image = image;
	barrierDesc.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	barrierDesc.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	barrierDesc.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrierDesc.subresourceRange.baseArrayLayer = 0;
	barrierDesc.subresourceRange.baseMipLevel = 0;
	barrierDesc.subresourceRange.layerCount = 1;
	barrierDesc.subresourceRange.levelCount = 1;
	barrierDesc.srcAccessMask = 0;
	barrierDesc.dstAccessMask = 0;

	auto srcStageMask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
	auto dstStageMask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;

	vkCmdPipelineBarrier(
		m_commandBuffer,
		srcStageMask,
		dstStageMask,
		0,
		0,
		nullptr,
		0,
		nullptr,
		1,
		&barrierDesc);
}


void CommandContext::Reset()
{
	assert(m_commandBuffer == VK_NULL_HANDLE);
	m_commandBuffer = m_device->GetQueue(m_type).RequestCommandBuffer();
}


GraphicsContext::~GraphicsContext() = default;


ComputeContext::~ComputeContext() = default;

} // namespace Kodiak::VK