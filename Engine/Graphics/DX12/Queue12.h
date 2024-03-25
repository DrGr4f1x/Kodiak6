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


namespace Kodiak::DX12
{

// Forward declarations
class GraphicsDevice;


class Queue
{
public:
	Queue(ID3D12Device* device, QueueType queueType);

	ID3D12CommandQueue* GetCommandQueue() noexcept { return m_dxQueue.Get(); }

private:
	IntrusivePtr<ID3D12CommandQueue> m_dxQueue;
	QueueType m_type{ QueueType::Graphics };
};

} // namespace Kodiak::DX12