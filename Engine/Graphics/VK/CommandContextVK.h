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

#include "Graphics\Enums.h"
#include "Graphics\Interfaces.h"
#include "Graphics\VK\VulkanCommon.h"
#include "Graphics\VK\Generated\LoaderVK.h"


namespace Kodiak::VK
{

// Forward declarations
class GraphicsDevice;


struct TextureBarrier
{
	VkImage image{ VK_NULL_HANDLE };
	VkFormat format{ VK_FORMAT_UNDEFINED };
	ResourceState beforeState{ ResourceState::Undefined };
	ResourceState afterState{ ResourceState::Undefined };
	uint32_t numMips{ 1 };
	uint32_t mipLevel{ 0 };
	uint32_t arraySizeOrDepth{ 1 };
	uint32_t arraySlice{ 0 };
	bool bWholeTexture{ false };
};


struct BufferBarrier
{
	// TODO - Vulkan GPU buffer support
};


class CommandContext : public IntrusiveCounter<ICommandContext>, public NonCopyable
{
	friend class GraphicsDevice;

public:
	~CommandContext() override;

	// Flush existing commands and release the current context
	uint64_t Finish(bool bWaitForCompletion = false) final;

	// Debug events and markers
	void BeginEvent(const std::string& label) final;
	void EndEvent() final;
	void SetMarker(const std::string& label) final;

	void HACK_TransitionImageToPresent(VkImage image);

	void TransitionResource(IGpuResource* gpuResource, ResourceState newState, bool bFlushImmediate) final;
	void InsertUAVBarrier(IGpuResource* gpuResource, bool bFlushImmediate) final;
	void FlushResourceBarriers();

protected:
	GraphicsDevice* m_device{ nullptr };
	CommandListType m_type{ CommandListType::Direct };
	VkCommandBuffer m_commandBuffer{ VK_NULL_HANDLE };

	bool m_bInvertedViewport{ true };
	bool m_hasPendingDebugEvent{ false };

	// Resource barriers
	std::vector<TextureBarrier> m_textureBarriers;
	std::vector<BufferBarrier> m_bufferBarriers;
	std::vector<VkMemoryBarrier2> m_memoryBarriers;
	std::vector<VkBufferMemoryBarrier2> m_bufferMemoryBarriers;
	std::vector<VkImageMemoryBarrier2> m_imageMemoryBarriers;

private:
	explicit CommandContext(CommandListType type);

	void Reset();

	size_t GetPendingBarrierCount() const noexcept { return m_textureBarriers.size() + m_bufferBarriers.size(); }
};


class GraphicsContext : public CommandContext
{
	friend class ContextManager;
	friend class GraphicsDevice;

public:
	~GraphicsContext() override;
};


class ComputeContext : public CommandContext
{
	friend class ContextManager;
	friend class GraphicsDevice;

public:
	~ComputeContext() override;
};

} // namespace Kodiak::VK