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

#include "GraphicsDevice.h"

// DirectX 12
#include "DX12\GraphicsDevice12.h"

// Vulkan
#include "VK\GraphicsDeviceVK.h"

using namespace Kodiak;
using namespace std;


namespace Kodiak
{

GUID IGraphicsDevice::IID = IID_IGraphicsDevice;

DeviceHandle CreateDevice(const GraphicsDeviceDesc& desc)
{
	switch (desc.api)
	{
	case GraphicsApi::D3D12:
		return Kodiak::DX12::CreateDevice12(desc);
		break;

	case GraphicsApi::Vulkan:
		return Kodiak::VK::CreateDeviceVK(desc);
		break;

	case GraphicsApi::Unknown:
	default:
		LOG_ERROR << "Unknown graphics API";
		Utility::ExitFatal("Unknown graphics API", "Unknown graphics API");
		return DeviceHandle();
	}
}

} // namespace Kodiak