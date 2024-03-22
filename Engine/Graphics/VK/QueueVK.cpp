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

#include "QueueVK.h"

#include "DeviceVK.h"
#include "Generated\LoaderVK.h"


namespace Kodiak::VK
{

Queue::Queue(GraphicsDevice* device, VkQueue queue, QueueType queueType)
	: m_vkQueue{ queue }
	, m_queueType{ queueType }
	, m_nextFenceValue{ (uint64_t)queueType << 56 | 1 }
	, m_lastCompletedFenceValue{ (uint64_t)queueType << 56 }
{
	device->CreateSemaphore(VK_SEMAPHORE_TYPE_TIMELINE, m_lastCompletedFenceValue, &m_vkTimelineSemaphore);
}

void Queue::AddWaitSemaphore(VkSemaphore semaphore, uint64_t value)
{
	if (!semaphore)
	{
		return;
	}

	m_waitSemaphores.push_back(semaphore);
	m_waitSemaphoreValues.push_back(value);
}


void Queue::AddSignalSemaphore(VkSemaphore semaphore, uint64_t value)
{
	if (!semaphore)
	{
		return;
	}

	m_signalSemaphores.push_back(semaphore);
	m_signalSemaphoreValues.push_back(value);
}


void Queue::UnblockPresent(VkSemaphore signalSemaphore, uint64_t waitValue, VkFence signalFence)
{
	uint64_t dummy = 0;

	VkTimelineSemaphoreSubmitInfo timelineSubmitInfo{ VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO };
	timelineSubmitInfo.waitSemaphoreValueCount = (uint32_t)m_waitSemaphoreValues.size();
	timelineSubmitInfo.pWaitSemaphoreValues = m_waitSemaphoreValues.data();
	timelineSubmitInfo.signalSemaphoreValueCount = (uint32_t)m_signalSemaphoreValues.size();
	timelineSubmitInfo.pSignalSemaphoreValues = m_signalSemaphoreValues.data();

	VkPipelineStageFlags waitFlag = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;

	VkSemaphore waitSemaphore = *m_vkTimelineSemaphore;

	VkSubmitInfo submitInfo{ VK_STRUCTURE_TYPE_SUBMIT_INFO };
	submitInfo.pNext = &timelineSubmitInfo;
	submitInfo.waitSemaphoreCount = (uint32_t)m_waitSemaphores.size();
	submitInfo.pWaitSemaphores = m_waitSemaphores.data();
	submitInfo.pWaitDstStageMask = &waitFlag;
	submitInfo.signalSemaphoreCount = (uint32_t)m_signalSemaphores.size();
	submitInfo.pSignalSemaphores = m_signalSemaphores.data();
	submitInfo.commandBufferCount = 0;
	submitInfo.pCommandBuffers = nullptr;

	vkQueueSubmit(m_vkQueue, 1, &submitInfo, signalFence);

	ClearSemaphores();
}


void Queue::ClearSemaphores()
{
	m_waitSemaphores.clear();
	m_waitSemaphoreValues.clear();
	m_signalSemaphores.clear();
	m_signalSemaphoreValues.clear();
}

} // namespace Kodiak::VK