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

#include "Graphics\Interfaces.h"
#include "Graphics\DX12\DirectXCommon.h"


namespace Kodiak::DX12
{

class GpuResource : public virtual IGpuResource
{
	friend class CommandContext;

public:
	// IGpuResource
	ResourceType GetType() const noexcept override { return m_resourceType; }

	ID3D12Resource* GetResource() noexcept { return m_resource; }
	ResourceState GetUsageState() const noexcept { return m_usageState; }

protected:
	GpuResource() = default;
	GpuResource(ResourceType resourceType, ID3D12Resource* resource, ResourceState usageState);

protected:
	ResourceType m_resourceType{ ResourceType::Texture2D };

	IntrusivePtr<ID3D12Resource> m_resource;
	ResourceState m_usageState{ ResourceState::Undefined };
	ResourceState m_transitioningState{ ResourceState::Undefined };
};

} // namespace Kodiak::DX12