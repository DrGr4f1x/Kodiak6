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

#include "Graphics\Interfaces.h"
#include "Graphics\Enums.h"
#include "Graphics\DX12\DirectXCommon.h"


namespace Kodiak::DX12
{

// Forward declarations
class GraphicsDevice;


class CommandContext : public IntrusiveCounter<ICommandContext>, public NonCopyable
{
	friend class GraphicsDevice;

public:
	~CommandContext() override;

	uint64_t Finish(bool bWaitForCompletion = false) final;

	void BeginEvent(const std::string& label);
	void EndEvent();
	void SetMarker(const std::string& label);

	void FlushResourceBarriers();

protected:
	void SetID(const std::string& id) { m_id = id; }

protected:
	GraphicsDevice* m_device{ nullptr };
	CommandListType m_type{ CommandListType::Direct };

	ID3D12GraphicsCommandList* m_commandList{ nullptr };
	ID3D12CommandAllocator* m_currentAllocator{ nullptr };

	std::string m_id;

	bool m_hasPendingDebugEvent{ false };

private:
	CommandContext(GraphicsDevice* device, CommandListType type);

	void Reset();
};


class GraphicsContext : public IntrusiveCounter<IGraphicsContext>, public CommandContext
{
public:
	~GraphicsContext() override;
};


class ComputeContext : public IntrusiveCounter<IComputeContext>, public CommandContext
{
public:
	~ComputeContext() override;
};

} // namespace Kodiak::DX12