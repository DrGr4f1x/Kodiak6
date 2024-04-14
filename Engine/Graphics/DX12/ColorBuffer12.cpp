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

#include "ColorBuffer12.h"

#include "Graphics\CreationParams.h"


using namespace std;


namespace
{

D3D12_RESOURCE_FLAGS CombineResourceFlags(uint32_t fragmentCount)
{
	D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAG_NONE;

	if (flags == D3D12_RESOURCE_FLAG_NONE && fragmentCount == 1)
	{
		flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
	}

	return D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET | flags;
}

} // anonymous namespace


namespace Kodiak::DX12
{

ColorBuffer::ColorBuffer(const ColorBufferCreationParams& creationParams, const ColorBufferCreationParamsExt& creationParamsExt)
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
	, m_clearColor{ creationParams.clearColor }
	, m_rtvHandle{ creationParamsExt.rtvHandle }
	, m_srvHandle{ creationParamsExt.srvHandle }
	, m_uavHandles{ creationParamsExt.uavHandles }
{
	m_numMips = m_numMips == 0 ? ComputeNumMips(m_width, m_height) : m_numMips;
}

} // namespace Kodiak::DX12