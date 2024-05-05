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

#include "Graphics\CreationParams.h"
#include "Graphics\DX12\DirectXCommon.h"

namespace Kodiak::DX12
{

class FrameBuffer : public IFrameBuffer
{
	IMPLEMENT_IOBJECT

	friend class GraphicsDevice;

public:

private:
	explicit FrameBuffer(const FrameBufferCreationParams& creationParams);

private:
	std::array<ColorBufferHandle, 8> m_colorBuffers;
	DepthBufferHandle m_depthBuffer;
};

} // namespace Kodiak::DX12