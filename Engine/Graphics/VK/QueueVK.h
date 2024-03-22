
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

// Forward declarations
class GraphicsDevice;


class Queue
{
public:
	Queue(GraphicsDevice* device, VkQueue queue, QueueType queueType);

	void AddWaitSemaphore(VkSemaphore semaphore, uint64_t value);
	void AddSignalSemaphore(VkSemaphore semaphore, uint64_t value);

	void UnblockPresent(VkSemaphore signalSemaphore, uint64_t waitValue, VkFence signalFence);

	VkQueue GetVkQueue() const noexcept { return m_vkQueue; }
	VkSemaphore GetTimelineSemaphore() const noexcept { return *m_vkTimelineSemaphore; }

	uint64_t GetNextFenceValue() const noexcept { return m_nextFenceValue; }

private:
	void ClearSemaphores();

private:
	VkQueue m_vkQueue{};
	QueueType m_queueType{};

	VkSemaphoreHandle m_vkTimelineSemaphore;
	uint64_t m_nextFenceValue{ 0 };
	uint64_t m_lastCompletedFenceValue{ 0 };

	std::vector<VkSemaphore> m_waitSemaphores;
	std::vector<uint64_t> m_waitSemaphoreValues;
	std::vector<VkSemaphore> m_signalSemaphores;
	std::vector<uint64_t> m_signalSemaphoreValues;
};

} // namespace Kodiak::VK