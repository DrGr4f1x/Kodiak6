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
	case NonPixelShaderResource:
	case UnorderedAccess:
	case CopyDest:
	case CopySource:
		return true;

	default:
		return false;
	}
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
#else
	(label)
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
#else
	(label)
#endif
}


//void CommandContext::TransitionResource(IColorBuffer* colorBuffer, ResourceState newState, bool bFlushImmediate)
//{
//	auto* dxColorBuffer = (ColorBuffer*)colorBuffer;
//
//	auto oldState = dxColorBuffer->m_usageState;
//
//	if (m_type == CommandListType::Compute)
//	{
//		assert(IsValidComputeResourceState(oldState));
//		assert(IsValidComputeResourceState(newState));
//	}
//
//	if (oldState != newState)
//	{
//		assert_msg(m_numPendingBarriers < 16, "Exceeded arbitrary limit on buffered barriers");
//		D3D12_RESOURCE_BARRIER& barrierDesc = m_resourceBarriers[m_numPendingBarriers++];
//
//		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
//		barrierDesc.Transition.pResource = resource.m_resource.Get();
//		barrierDesc.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
//		barrierDesc.Transition.StateBefore = GetResourceState(oldState);
//		barrierDesc.Transition.StateAfter = GetResourceState(newState);
//
//		// Check to see if we already started the transition
//		if (newState == resource.m_transitioningState)
//		{
//			barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_END_ONLY;
//			resource.m_transitioningState = ResourceState::Undefined;
//		}
//		else
//		{
//			barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
//		}
//
//		resource.m_usageState = newState;
//	}
//	else if (newState == ResourceState::UnorderedAccess)
//	{
//		InsertUAVBarrier(resource, flushImmediate);
//	}
//
//	if (flushImmediate || m_numBarriersToFlush == 16)
//	{
//		FlushResourceBarriers();
//	}
//}


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