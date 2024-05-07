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

#include "CommandContext12.h"

#include "ColorBuffer12.h"
#include "Device12.h"
#include "Queue12.h"

#if ENABLE_D3D12_DEBUG_MARKERS
#include <pix.h>
#endif


using namespace std;


namespace
{

bool IsValidComputeResourceState(Kodiak::ResourceState state)
{
	using enum Kodiak::ResourceState;

	// TODO: Also ResourceState::ShaderResource?
	switch (state)
	{
	case ShaderResource:
	case UnorderedAccess:
	case CopyDest:
	case CopySource:
		return true;

	default:
		return false;
	}
}


uint32_t CalcSubresource(uint32_t mipSlice, uint32_t arraySlice, uint32_t planeSlice, uint32_t numMips, uint32_t arraySize)
{
	return mipSlice + (arraySlice * numMips) + (planeSlice * numMips * arraySize);
}

} // anonymous namespace


namespace Kodiak::DX12
{

CommandContext::CommandContext(GraphicsDevice* device, CommandListType commandListType)
	: m_device{ device }
	, m_type{ commandListType }
{}


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

	assert(m_currentAllocator != nullptr);

	if (m_hasPendingDebugEvent)
	{
		EndEvent();
		m_hasPendingDebugEvent = false;
	}

	Queue& cmdQueue = m_device->GetQueue(m_type);

	uint64_t fenceValue = cmdQueue.ExecuteCommandList(m_commandList);
	cmdQueue.DiscardAllocator(fenceValue, m_currentAllocator);
	m_currentAllocator = nullptr;

	// m_cpuLinearAllocator.CleanupUsedPages(fenceValue);
	// m_gpuLinearAllocator.CleanupUsedPages(fenceValue);
	// m_dynamicViewDescriptorHeap.CleanupUsedHeaps(fenceValue);
	// m_dynamicSamplerDescriptorHeap.CleanupUsedHeaps(fenceValue);

	if (bWaitForCompletion)
	{
		cmdQueue.WaitForFence(fenceValue);
	}

	m_device->FreeContext(this);

	return fenceValue;
}


void CommandContext::BeginEvent(const string& label)
{
#if ENABLE_D3D12_DEBUG_MARKERS
	::PIXBeginEvent(m_commandList, 0, label.c_str());
#endif
}


void CommandContext::EndEvent() 
{
#if ENABLE_D3D12_DEBUG_MARKERS
	::PIXEndEvent(m_commandList);
#endif
}


void CommandContext::SetMarker(const string& label)
{
#if ENABLE_D3D12_DEBUG_MARKERS
	::PIXSetMarker(m_commandList, 0, label.c_str());
#endif
}


void CommandContext::TransitionResource(IPixelBuffer* pixelBuffer, ResourceState newState, bool bFlushImmediate)
{
	auto oldState = pixelBuffer->GetUsageState();

	if (m_type == CommandListType::Compute)
	{
		assert(IsValidComputeResourceState(oldState));
		assert(IsValidComputeResourceState(newState));
	}

	TextureBarrier barrier{};
	barrier.resource = pixelBuffer->GetNativeObject(NativeObjectType::DX12_Resource);
	barrier.beforeState = oldState;
	barrier.afterState = newState;
	barrier.numMips = pixelBuffer->GetNumMips();
	barrier.mipLevel = 0;
	barrier.arraySizeOrDepth = pixelBuffer->GetArraySize();
	barrier.arraySlice = 0;
	barrier.planeCount = pixelBuffer->GetPlaneCount();
	barrier.bWholeTexture = true;

	m_textureBarriers.push_back(barrier);

	pixelBuffer->SetUsageState(newState);


	if (bFlushImmediate || GetPendingBarrierCount() >= 16)
	{
		FlushResourceBarriers();
	}
}


void CommandContext::InsertUAVBarrier(IPixelBuffer* pixelBuffer, bool bFlushImmediate)
{
	assert_msg(HasFlag(pixelBuffer->GetUsageState(), ResourceState::UnorderedAccess), "Resource must be in UnorderedAccess state to insert a UAV barrier");

	BufferBarrier barrier{};
	barrier.resource = pixelBuffer->GetNativeObject(NativeObjectType::DX12_Resource);
	barrier.beforeState = pixelBuffer->GetUsageState();
	barrier.afterState = barrier.beforeState;

	m_bufferBarriers.push_back(barrier);

	if (bFlushImmediate || GetPendingBarrierCount() >= 16)
	{
		FlushResourceBarriers();
	}
}


void CommandContext::FlushResourceBarriers()
{
	using enum ResourceState;

	const size_t numBarriers = m_textureBarriers.size() + m_bufferBarriers.size();
	if (numBarriers == 0)
	{
		return;
	}

	m_dxBarriers.clear();
	m_dxBarriers.reserve(numBarriers);

	for (const auto& barrier : m_textureBarriers)
	{
		D3D12_RESOURCE_BARRIER dxBarrier{};
		const D3D12_RESOURCE_STATES beforeState = ResourceStateToDX12(barrier.beforeState);
		const D3D12_RESOURCE_STATES afterState = ResourceStateToDX12(barrier.afterState);

		if (beforeState != afterState)
		{
			dxBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			dxBarrier.Transition.StateBefore = beforeState;
			dxBarrier.Transition.StateAfter = afterState;
			dxBarrier.Transition.pResource = barrier.resource;
			if (barrier.bWholeTexture)
			{
				dxBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
				m_dxBarriers.push_back(dxBarrier);
			}
			else
			{
				for (uint8_t plane = 0; plane < barrier.planeCount; ++plane)
				{
					dxBarrier.Transition.Subresource = CalcSubresource(barrier.mipLevel, barrier.arraySlice, plane, barrier.numMips, barrier.arraySizeOrDepth);
					m_dxBarriers.push_back(dxBarrier);
				}
			}
		}
		else if (afterState & D3D12_RESOURCE_STATE_UNORDERED_ACCESS)
		{
			dxBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
			dxBarrier.UAV.pResource = barrier.resource;
			m_dxBarriers.push_back(dxBarrier);
		}
	}

	for (const auto& barrier : m_bufferBarriers)
	{
		D3D12_RESOURCE_BARRIER dxBarrier{};
		const D3D12_RESOURCE_STATES beforeState = ResourceStateToDX12(barrier.beforeState);
		const D3D12_RESOURCE_STATES afterState = ResourceStateToDX12(barrier.afterState);

		if (beforeState != afterState &&
			(beforeState & D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE) == 0 &&
			(afterState & D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE) == 0)
		{
			dxBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			dxBarrier.Transition.StateBefore = beforeState;
			dxBarrier.Transition.StateAfter = afterState;
			dxBarrier.Transition.pResource = barrier.resource;
			dxBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
			m_dxBarriers.push_back(dxBarrier);
		}
		else if ((HasFlag(barrier.beforeState, AccelStructWrite) && HasAnyFlag(barrier.afterState, (AccelStructRead | AccelStructBuildBlas))) ||
			(HasFlag(barrier.afterState, AccelStructWrite) && HasAnyFlag(barrier.beforeState, (AccelStructRead | AccelStructBuildBlas))) ||
			(HasFlag(barrier.beforeState, OpacityMicromapWrite) && HasFlag(barrier.afterState, AccelStructBuildInput)) ||
			(afterState & D3D12_RESOURCE_STATE_UNORDERED_ACCESS) != 0)
		{
			dxBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
			dxBarrier.UAV.pResource = barrier.resource;
			m_dxBarriers.push_back(dxBarrier);
		}
	}

	if (!m_dxBarriers.empty())
	{
		m_commandList->ResourceBarrier((uint32_t)m_dxBarriers.size(), m_dxBarriers.data());
		m_dxBarriers.clear();
	}

	m_textureBarriers.clear();
	m_bufferBarriers.clear();
}


void CommandContext::Reset()
{
	// We only call Reset() on previously freed contexts.  The command list persists, but we must
	// request a new allocator.
	assert(m_commandList != nullptr && m_currentAllocator == nullptr);
	m_currentAllocator = m_device->GetQueue(m_type).RequestAllocator();
	m_commandList->Reset(m_currentAllocator, nullptr);

	/*m_curGraphicsRootSignature = nullptr;
	m_curGraphicsPipelineState = nullptr;
	m_curComputeRootSignature = nullptr;
	m_curComputePipelineState = nullptr;
	m_numBarriersToFlush = 0;

	m_curPrimitiveTopology = (D3D12_PRIMITIVE_TOPOLOGY)-1;

	BindDescriptorHeaps();*/
}


GraphicsContext::~GraphicsContext() = default;


ComputeContext::~ComputeContext() = default;

} // namespace Kodiak::VK