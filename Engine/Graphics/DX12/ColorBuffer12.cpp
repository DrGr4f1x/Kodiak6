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

#include "Device12.h"


using namespace std;


namespace Kodiak::DX12
{

ColorBuffer::ColorBuffer(const ColorBufferCreationParams& creationParams, const ColorBufferCreationParamsExt& creationParamsExt)
	: m_resourceType{creationParams.resourceType}
	, m_width{creationParams.width}
	, m_height{creationParams.height}
	, m_arraySizeOrDepth{creationParams.arraySizeOrDepth}
	, m_numMips{creationParams.numMips}
	, m_numSamples{creationParams.numSamples}
	, m_format{creationParams.format}
	, m_clearColor{creationParams.clearColor}
	, m_resource{creationParamsExt.resource}
	, m_usageState{creationParamsExt.usageState}
	, m_transitioningState{creationParamsExt.transitioningState}
{
	m_srvHandle.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
	m_rtvHandle.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
	memset(m_uavHandle, 0xFF, sizeof(m_uavHandle));
}


void ColorBuffer::InitializeFromSwapChain(GraphicsDevice* device)
{
	m_rtvHandle = device->AllocateDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	device->GetD3D12Device()->CreateRenderTargetView(m_resource, nullptr, m_rtvHandle);
}

} // namespace Kodiak::DX12