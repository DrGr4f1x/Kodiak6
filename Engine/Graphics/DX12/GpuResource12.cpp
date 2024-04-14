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

#include "GpuResource12.h"


namespace Kodiak::DX12
{

GpuResource::GpuResource(ResourceType resourceType, ID3D12Resource* resource, ResourceState usageState)
	: m_resourceType{ resourceType }
	, m_resource{ resource }
	, m_usageState{ usageState }
{}

} // namespace Kodiak::DX12