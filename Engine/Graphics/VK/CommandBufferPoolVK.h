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

class CommandBufferPool : public IObject, public NonCopyable
{
	IMPLEMENT_IOBJECT

public:
	CommandBufferPool(CVkCommandPool* commandPool, CommandListType commandListType) noexcept
		: m_vkCommandPool{ commandPool }
		, m_commandListType{ commandListType }
	{}

	~CommandBufferPool()
	{
		Destroy();
	}

	VkCommandBuffer RequestCommandBuffer(uint64_t completedFenceValue);
	void DiscardCommandBuffer(uint64_t fenceValue, VkCommandBuffer commandBuffer);

	size_t Size() const noexcept { return m_commandBuffers.size(); }

private:
	void Destroy();

private:
	VkCommandPoolHandle m_vkCommandPool;
	const CommandListType m_commandListType{ CommandListType::Direct };

	std::vector<VkCommandBuffer> m_commandBuffers;
	std::queue<std::pair<uint64_t, VkCommandBuffer>> m_readyCommandBuffers;
	std::mutex m_commandBufferMutex;
};
using CommandBufferPoolHandle = IntrusivePtr<CommandBufferPool>;

} // namespace Kodiak::VK
