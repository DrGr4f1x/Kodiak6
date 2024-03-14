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

#include "DeviceManager.h"

#include "Graphics\DX12\DeviceManager12.h"
#include "Graphics\VK\DeviceManagerVK.h"

namespace Kodiak
{

DeviceManager* DeviceManager::Create(GraphicsApi api)
{
	switch (api)
	{
	case GraphicsApi::D3D12:
		return new DX12::DeviceManager12();
		break;

	case GraphicsApi::Vulkan:
		return new VK::DeviceManagerVK();
		break;

		// Fall back to DX12
	default:
		return new DX12::DeviceManager12();
		break;
	}
}


bool DeviceManager::CreateDeviceAndSwapChain(const DeviceDesc& desc)
{
	m_desc = desc;

	if (!CreateInstance())
	{
		return false;
	}

	if (!CreateDevice())
	{
		return false;
	}

	if (!CreateSwapChain())
	{
		return false;
	}

	return true;
}


bool DeviceManager::CreateInstance()
{
	if (m_instanceCreated)
	{
		return true;
	}

	m_bIsDeveloperModeEnabled = IsDeveloperModeEnabled();
	m_bIsRenderDocAvailable = IsRenderDocAvailable();

	m_instanceCreated = CreateInstanceInternal();

	return m_instanceCreated;
}


bool DeviceManager::CreateDevice()
{

	return true;
}


bool DeviceManager::CreateSwapChain()
{

	return true;
}

} // namespace Kodiak