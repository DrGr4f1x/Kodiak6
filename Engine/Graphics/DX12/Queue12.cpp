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

#include "Queue12.h"


using namespace std;


namespace Kodiak::DX12
{

Queue::Queue(ID3D12Device* device, QueueType queueType)
	: m_type{ queueType }
{
	D3D12_COMMAND_QUEUE_DESC queueDesc{};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = CommandListTypeToDX12(QueueTypeToCommandListType(queueType));
	queueDesc.NodeMask = 1;
	if (FAILED(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_dxQueue))))
	{
		// TODO - get the string name of the queue type for a better log message
		LogError(LogDirectX) << "Failed to create DirectX queue." << endl;

		// TODO - same thing for debug name
		SetDebugName(m_dxQueue.Get(), "Queue");
	}
}

} // namespace Kodiak::DX12