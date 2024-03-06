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

IGraphicsDevice* g_graphicsDevice = nullptr;

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


bool IsDeveloperModeEnabled()
{
	static bool initialized = false;
	static bool isDeveloperModeEnabled = false;

	if (!initialized)
	{
		HKEY hKey;
		auto err = RegOpenKeyExW(HKEY_LOCAL_MACHINE, LR"(SOFTWARE\Microsoft\Windows\CurrentVersion\AppModelUnlock)", 0, KEY_READ, &hKey);
		if (err == ERROR_SUCCESS)
		{
			DWORD value{};
			DWORD dwordSize = sizeof(DWORD);
			err = RegQueryValueExW(hKey, L"AllowDevelopmentWithoutDevLicense", 0, NULL, reinterpret_cast<LPBYTE>(&value), &dwordSize);
			RegCloseKey(hKey);
			if (err == ERROR_SUCCESS)
			{
				isDeveloperModeEnabled = (value != 0);
			}
		}

		LOG_INFO << "Developer mode is " << (isDeveloperModeEnabled ? "enabled" : "not enabled");

		initialized = true;
	}
	return isDeveloperModeEnabled;
}


bool IsRenderDocAvailable()
{
	static bool initialized = false;
	static bool isRenderDocAvailable = false;

	if (!initialized)
	{
		if (HMODULE hmod = GetModuleHandleA("renderdoc.dll"))
		{
			isRenderDocAvailable = true;
		}

		LOG_INFO << "RenderDoc is " << (isRenderDocAvailable ? "attached" : "not attached");

		initialized = true;
	}
	return isRenderDocAvailable;
}

} // namespace Kodiak