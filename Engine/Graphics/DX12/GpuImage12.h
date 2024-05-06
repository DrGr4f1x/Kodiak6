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

#include "Graphics\DX12\DirectXCommon.h"

namespace Kodiak::DX12
{

class GpuImage : public virtual IGpuImage
{
public:
	ResourceType GetType() const noexcept override
	{
		return m_resourceType;
	}

	ResourceState GetUsageState() const noexcept override
	{
		return m_usageState;
	}

	void SetUsageState(ResourceState usageState) noexcept override
	{
		m_usageState = usageState;
	}

protected:
	GpuImage() noexcept = default;
	GpuImage(ResourceType resourceType, ID3D12Resource* resource, ResourceState usageState) noexcept;

protected:
	ResourceType m_resourceType{ ResourceType::Unknown };

	IntrusivePtr<ID3D12Resource> m_resource;
	ResourceState m_usageState{ ResourceState::Undefined };
	ResourceState m_transitioningState{ ResourceState::Undefined };
};

} // namespace Kodiak::DX12