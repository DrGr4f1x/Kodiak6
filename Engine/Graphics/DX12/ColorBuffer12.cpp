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


namespace Kodiak::DX12
{

ColorBuffer::ColorBuffer(const ColorBufferCreationParams& creationParams, const ColorBufferCreationParamsExt& creationParamsExt)
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
	, m_clearColor{ creationParams.clearColor }
	, m_numFragments{ 1 }
	, m_rtvHandle{ creationParamsExt.rtvHandle }
	, m_srvHandle{ creationParamsExt.srvHandle }
	, m_uavHandles{ creationParamsExt.uavHandles }
{
	m_numMips = m_numMips == 0 ? ComputeNumMips(m_width, m_height) : m_numMips;
}


NativeObjectPtr ColorBuffer::GetNativeObject(NativeObjectType nativeObjectType) const noexcept
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