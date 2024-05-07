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
#include "Graphics\DX12\DirectXCommon.h"


namespace Kodiak::DX12
{

// Forward declarations
class GraphicsDevice;


struct TextureBarrier
{
	ID3D12Resource* resource{ nullptr };
	ResourceState beforeState{ ResourceState::Undefined };
	ResourceState afterState{ ResourceState::Undefined };
	uint32_t numMips{ 1 };
	uint32_t mipLevel{ 0 };
	uint32_t arraySizeOrDepth{ 1 };
	uint32_t arraySlice{ 0 };
	uint32_t planeCount{ 1 };
	bool bWholeTexture{ false };
};


struct BufferBarrier
{
	ID3D12Resource* resource{ nullptr };
	ResourceState beforeState{ ResourceState::Undefined };
	ResourceState afterState{ ResourceState::Undefined };
};


class CommandContext : public virtual ICommandContext, public NonCopyable
{
	IMPLEMENT_IOBJECT

	friend class GraphicsDevice;

public:
	~CommandContext() override;

	uint64_t Finish(bool bWaitForCompletion = false) final;

	void BeginEvent(const std::string& label) final;
	void EndEvent() final;
	void SetMarker(const std::string& label) final;

	void TransitionResource(IGpuImage* gpuImage, ResourceState newState, bool bFlushImmediate) final;
	void InsertUAVBarrier(IGpuImage* gpuImage, bool bFlushImmediate) final;
	void FlushResourceBarriers();

	IGraphicsContext* GetGraphicsContext() noexcept final
	{
		return reinterpret_cast<IGraphicsContext*>(this);
	}

	IComputeContext* GetComputeContext() noexcept final
	{
		return reinterpret_cast<IComputeContext*>(this);
	}

protected:
	void SetID(const std::string& id) { m_id = id; }

protected:
	GraphicsDevice* m_device{ nullptr };
	CommandListType m_type{ CommandListType::Direct };

	ID3D12GraphicsCommandList* m_commandList{ nullptr };
	ID3D12CommandAllocator* m_currentAllocator{ nullptr };

	std::vector<TextureBarrier> m_textureBarriers;
	std::vector<BufferBarrier> m_bufferBarriers;
	std::vector<D3D12_RESOURCE_BARRIER> m_dxBarriers;

	std::string m_id;

	bool m_hasPendingDebugEvent{ false };

private:
	CommandContext(GraphicsDevice* device, CommandListType type);

	void Reset();

	size_t GetPendingBarrierCount() const noexcept { return m_textureBarriers.size() + m_bufferBarriers.size(); }
};


class GraphicsContext : public IGraphicsContext, public CommandContext
{
public:
	~GraphicsContext() override;
};


class ComputeContext : public IComputeContext, public CommandContext
{
public:
	~ComputeContext() override;
};

} // namespace Kodiak::DX12