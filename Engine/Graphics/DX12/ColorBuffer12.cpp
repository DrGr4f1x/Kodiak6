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
#include "Formats12.h"


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
	: m_name{ creationParams.name }
	, m_resourceType{ creationParams.resourceType }
	, m_width{ creationParams.width }
	, m_height{ creationParams.height }
	, m_arraySizeOrDepth{ creationParams.arraySizeOrDepth }
	, m_numMips{ creationParams.numMips }
	, m_numSamples{ creationParams.numSamples }
	, m_format{ creationParams.format }
	, m_clearColor{ creationParams.clearColor }
	, m_resource{ creationParamsExt.resource }
	, m_usageState{ creationParamsExt.usageState }
	, m_transitioningState{ creationParamsExt.transitioningState }
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


void ColorBuffer::Initialize(GraphicsDevice* device)
{
	auto numMips = m_numMips == 0 ? ComputeNumMips(m_width, m_height) : m_numMips;
	auto flags = CombineResourceFlags(m_numSamples);

	D3D12_RESOURCE_DESC desc{};
	desc.Alignment = 0;
	desc.DepthOrArraySize = (UINT16)m_arraySizeOrDepth;
	desc.Dimension = GetResourceDimension(m_resourceType);
	desc.Flags = (D3D12_RESOURCE_FLAGS)flags;
	desc.Format = FormatToDxgi(m_format).resourceFormat;
	desc.Height = (UINT)m_height;
	desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	desc.MipLevels = (UINT16)numMips;
	desc.SampleDesc.Count = m_numSamples;
	desc.SampleDesc.Quality = 0;
	desc.Width = (UINT64)m_width;

	D3D12_CLEAR_VALUE clearValue = {};
	clearValue.Format = FormatToDxgi(m_format).rtvFormat;
	clearValue.Color[0] = m_clearColor.R();
	clearValue.Color[1] = m_clearColor.G();
	clearValue.Color[2] = m_clearColor.B();
	clearValue.Color[3] = m_clearColor.A();

	auto d3d12Device = device->GetD3D12Device();
	
	CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_DEFAULT);
	assert_succeeded(d3d12Device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE,
		&desc, D3D12_RESOURCE_STATE_COMMON, &clearValue, IID_PPV_ARGS(&m_resource)));

	SetDebugName(m_resource, m_name);

	CreateDerivedViews(device, numMips);
}


void ColorBuffer::CreateDerivedViews(GraphicsDevice* device, uint32_t numMips)
{
	assert_msg(m_arraySizeOrDepth == 1 || numMips == 1, "We don't support auto-mips on texture arrays");

	m_numMips = numMips - 1;

	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc{};
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};

	DXGI_FORMAT dxgiFormat = FormatToDxgi(m_format).resourceFormat;
	rtvDesc.Format = dxgiFormat;
	uavDesc.Format = GetUAVFormat(dxgiFormat);
	srvDesc.Format = dxgiFormat;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

	if (m_arraySizeOrDepth > 1)
	{
		if (m_resourceType == ResourceType::Texture3D)
		{
			rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE3D;
			rtvDesc.Texture3D.MipSlice = 0;
			rtvDesc.Texture3D.FirstWSlice = 0;
			rtvDesc.Texture3D.WSize = (UINT)m_arraySizeOrDepth;

			uavDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE3D;
			uavDesc.Texture3D.MipSlice = 0;
			uavDesc.Texture3D.FirstWSlice = 0;
			uavDesc.Texture3D.WSize = (UINT)m_arraySizeOrDepth;

			srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
			srvDesc.Texture3D.MipLevels = numMips;
			srvDesc.Texture3D.MostDetailedMip = 0;
		}
		else
		{
			rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
			rtvDesc.Texture2DArray.MipSlice = 0;
			rtvDesc.Texture2DArray.FirstArraySlice = 0;
			rtvDesc.Texture2DArray.ArraySize = (UINT)m_arraySizeOrDepth;

			uavDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2DARRAY;
			uavDesc.Texture2DArray.MipSlice = 0;
			uavDesc.Texture2DArray.FirstArraySlice = 0;
			uavDesc.Texture2DArray.ArraySize = (UINT)m_arraySizeOrDepth;

			srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
			srvDesc.Texture2DArray.MipLevels = numMips;
			srvDesc.Texture2DArray.MostDetailedMip = 0;
			srvDesc.Texture2DArray.FirstArraySlice = 0;
			srvDesc.Texture2DArray.ArraySize = (UINT)m_arraySizeOrDepth;
		}
	}
	else if (m_numFragments > 1)
	{
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMS;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DMS;
	}
	else
	{
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		rtvDesc.Texture2D.MipSlice = 0;

		uavDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
		uavDesc.Texture2D.MipSlice = 0;

		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = numMips;
		srvDesc.Texture2D.MostDetailedMip = 0;
	}

	if (m_srvHandle.ptr == D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN)
	{
		m_rtvHandle = device->AllocateDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		m_srvHandle = device->AllocateDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	}

	ID3D12Resource* resource = m_resource.Get();

	auto d3d12Device = device->GetD3D12Device();

	// Create the render target view
	d3d12Device->CreateRenderTargetView(resource, &rtvDesc, m_rtvHandle);

	// Create the shader resource view
	d3d12Device->CreateShaderResourceView(resource, &srvDesc, m_srvHandle);

	if (m_numFragments > 1)
		return;

	// Create the UAVs for each mip level (RWTexture2D)
	for (uint32_t i = 0; i < numMips; ++i)
	{
		if (m_uavHandle[i].ptr == D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN)
		{
			m_uavHandle[i] = device->AllocateDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		}

		d3d12Device->CreateUnorderedAccessView(resource, nullptr, &uavDesc, m_uavHandle[i]);

		uavDesc.Texture2D.MipSlice++;
	}
}

} // namespace Kodiak::DX12