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

} // namespace Kodiak