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
	inline void FlushResourceBarriers() { /* TODO - see if we can cache and flush multiple barriers at once */ }

protected:
	GraphicsDevice* m_device{ nullptr };
	CommandListType m_type{ CommandListType::Direct };
	VkCommandBuffer m_commandBuffer{ VK_NULL_HANDLE };

	bool m_bInvertedViewport{ true };
	bool m_hasPendingDebugEvent{ false };

private:
	explicit CommandContext(CommandListType type);

	void Reset();
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