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

#include "Device12.h"
#include "Formats12.h"


namespace Kodiak::DX12
{

DepthBuffer::DepthBuffer(const DepthBufferCreationParams& creationParams) noexcept
	: m_name{ creationParams.name }
	, m_resourceType{ creationParams.resourceType }
	, m_width{ creationParams.width }
	, m_height{ creationParams.height }
	, m_arraySizeOrDepth{ 1 }
	, m_numMips{ 1 }
	, m_numSamples{ 1 }
	, m_format{ creationParams.format }
	, m_clearDepth{ creationParams.clearDepth }
	, m_clearStencil{ creationParams.clearStencil }
{
	m_dsvHandle[0].ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
	m_dsvHandle[1].ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
	m_dsvHandle[2].ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
	m_dsvHandle[3].ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
	m_depthSrvHandle.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
	m_stencilSrvHandle.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
}


void DepthBuffer::Initialize(GraphicsDevice* device)
{
	D3D12_RESOURCE_DESC desc{};
	desc.Alignment = 0;
	desc.DepthOrArraySize = (UINT16)m_arraySizeOrDepth;
	desc.Dimension = GetResourceDimension(m_resourceType);
	desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	desc.Format = FormatToDxgi(m_format).resourceFormat;
	desc.Height = (UINT)m_height;
	desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	desc.MipLevels = (UINT16)m_numMips;
	desc.SampleDesc.Count = m_numSamples;
	desc.SampleDesc.Quality = 0;
	desc.Width = (UINT64)m_width;

	D3D12_CLEAR_VALUE clearValue = {};
	clearValue.Format = FormatToDxgi(m_format).rtvFormat;
	clearValue.DepthStencil.Depth = m_clearDepth;
	clearValue.DepthStencil.Stencil = m_clearStencil;

	auto d3d12Device = device->GetD3D12Device();

	CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_DEFAULT);
	assert_succeeded(d3d12Device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE,
		&desc, D3D12_RESOURCE_STATE_COMMON, &clearValue, IID_PPV_ARGS(&m_resource)));

	SetDebugName(m_resource, m_name);

	CreateDerivedViews(device);
}


void DepthBuffer::CreateDerivedViews(GraphicsDevice* device)
{

}

} // namespace Kodiak::DX12