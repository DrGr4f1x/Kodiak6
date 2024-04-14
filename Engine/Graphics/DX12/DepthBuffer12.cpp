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

#include "DepthBuffer12.h"

#include "Graphics\CreationParams.h"
#include "Device12.h"
#include "Formats12.h"


namespace Kodiak::DX12
{

DepthBuffer::DepthBuffer(const DepthBufferCreationParams& creationParams, const DepthBufferCreationParamsExt& creationParamsExt) noexcept
	: PixelBuffer{
		creationParams.resourceType,
		creationParamsExt.resource,
		creationParamsExt.usageState,
		creationParams.width,
		creationParams.height,
		creationParams.arraySizeOrDepth,
		creationParams.numMips,
		creationParams.numSamples,
		creationParams.format,
		creationParamsExt.planeCount }
	, m_name{ creationParams.name }
	, m_clearDepth{ creationParams.clearDepth }
	, m_clearStencil{ creationParams.clearStencil }
	, m_dsvHandles{ creationParamsExt.dsvHandles }
	, m_depthSrvHandle{ creationParamsExt.depthSrvHandle }
	, m_stencilSrvHandle{ creationParamsExt.stencilSrvHandle }
{}

} // namespace Kodiak::DX12