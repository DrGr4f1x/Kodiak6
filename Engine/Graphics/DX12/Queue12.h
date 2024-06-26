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

#include "Graphics\DX12\DirectXCommon.h"
#include "Graphics\DX12\CommandAllocatorPool12.h"


namespace Kodiak::DX12
{

// Forward declarations
class GraphicsDevice;


class Queue
{
public:
	Queue(ID3D12Device* device, QueueType queueType);
	~Queue();

	ID3D12CommandQueue* GetCommandQueue() noexcept { return m_dxQueue.Get(); }

	uint64_t ExecuteCommandList(ID3D12CommandList* commandList);
	ID3D12CommandAllocator* RequestAllocator();
	void DiscardAllocator(uint64_t fenceValueForReset, ID3D12CommandAllocator* allocator);

	bool IsFenceComplete(uint64_t fenceValue);
	void WaitForFence(uint64_t fenceValue);

private:
	IntrusivePtr<ID3D12CommandQueue> m_dxQueue;
	QueueType m_type{ QueueType::Graphics };

	CommandAllocatorPool m_allocatorPool;
	std::mutex m_fenceMutex;
	std::mutex m_eventMutex;

	IntrusivePtr<ID3D12Fence> m_dxFence;
	uint64_t m_nextFenceValue;
	uint64_t m_lastCompletedFenceValue;
	HANDLE m_fenceEventHandle{ nullptr };
};

} // namespace Kodiak::DX12