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

#include "DepthBufferVK.h"


using namespace std;


namespace Kodiak::VK
{

DepthBuffer::DepthBuffer(const DepthBufferCreationParams& creationParams) noexcept
	: m_name{ creationParams.name }
	, m_resourceType{ creationParams.resourceType }
	, m_width{ creationParams.width }
	, m_height{ creationParams.height }
	, m_arraySizeOrDepth{ creationParams.arraySizeOrDepth }
	, m_numMips{ creationParams.numMips }
	, m_numSamples{ creationParams.numSamples }
	, m_format{ creationParams.format }
	, m_clearDepth{ creationParams.clearDepth }
	, m_clearStencil{ creationParams.clearStencil }
{}

} // namespace Kodiak::VK