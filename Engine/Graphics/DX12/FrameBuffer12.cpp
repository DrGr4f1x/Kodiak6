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

#include "FrameBuffer12.h"

namespace Kodiak::DX12
{

FrameBuffer::FrameBuffer(const FrameBufferCreationParams& creationParams)
{
	for (size_t i = 0; i < m_colorBuffers.size(); ++i)
	{
		m_colorBuffers[i] = creationParams.colorBuffers[i];
	}
	m_depthBuffer = creationParams.depthBuffer;
}

} // namespace Kodiak::DX12