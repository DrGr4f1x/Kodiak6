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


namespace Kodiak::DX12
{

DepthBuffer::DepthBuffer(const DepthBufferCreationParams& creationParams, const DepthBufferCreationParamsExt& creationParamsExt) noexcept
	: GpuImage{
		creationParamsExt.resource,
		creationParams.width,
		creationParams.height,
		creationParams.arraySizeOrDepth,
		creationParams.numMips,
		creationParams.numSamples,
		creationParamsExt.planeCount,
		creationParams.resourceType,
		creationParamsExt.usageState,
		creationParams.format }
	, m_name{ creationParams.name }
	, m_clearDepth{ creationParams.clearDepth }
	, m_clearStencil{ creationParams.clearStencil }
	, m_dsvHandles{ creationParamsExt.dsvHandles }
	, m_depthSrvHandle{ creationParamsExt.depthSrvHandle }
	, m_stencilSrvHandle{ creationParamsExt.stencilSrvHandle }
{
	m_numMips = m_numMips == 0 ? ComputeNumMips(m_width, m_height) : m_numMips;
}


NativeObjectPtr DepthBuffer::GetNativeObject(NativeObjectType nativeObjectType) const noexcept
{
	using enum NativeObjectType;

	switch (nativeObjectType)
	{
	case DX12_Resource:
		return NativeObjectPtr(m_resource);
		break;
	default:
		return nullptr;
		break;
	}
}

} // namespace Kodiak::DX12