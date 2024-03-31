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

#include "GraphicsCommon.h"

#include "Graphics\CreationParams.h"
#include "Graphics\DX12\DeviceManager12.h"
#include "Graphics\VK\DeviceManagerVK.h"


using namespace std;


namespace
{

Kodiak::DeviceManagerHandle CreateD3D12DeviceManager(const Kodiak::DeviceManagerCreationParams& creationParams)
{
	auto deviceManager = new Kodiak::DX12::DeviceManager(creationParams);
	return Kodiak::DeviceManagerHandle::Create(deviceManager);
}


Kodiak::DeviceManagerHandle CreateVulkanDeviceManager(const Kodiak::DeviceManagerCreationParams& creationParams)
{
	auto deviceManager = new Kodiak::VK::DeviceManager(creationParams);
	return Kodiak::DeviceManagerHandle::Create(deviceManager);
}

} // anonymous namespace


namespace Kodiak
{

extern LogCategory LogApplication;

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

		LogInfo(LogApplication) << "Developer mode is " << (isDeveloperModeEnabled ? "enabled" : "not enabled") << endl;

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

		LogInfo(LogApplication) << "RenderDoc is " << (isRenderDocAvailable ? "attached" : "not attached") << endl;

		initialized = true;
	}
	return isRenderDocAvailable;
}


DeviceManagerHandle CreateDeviceManager(const DeviceManagerCreationParams& creationParams)
{
	switch (creationParams.graphicsApi)
	{
	case GraphicsApi::Vulkan:
		return CreateVulkanDeviceManager(creationParams);
		break;

		// Default to D3D12
	default:
		return CreateD3D12DeviceManager(creationParams);
		break;
	}
}

} // namespace Kodiak