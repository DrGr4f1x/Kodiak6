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

#include "DeviceManagerVK.h"

#include "ExtensionManagerVK.h"
#include "Generated\LoaderVK.h"

using namespace std;


namespace Kodiak::VK
{

DeviceManagerVK::~DeviceManagerVK()
{
	delete m_extensionManager;
	m_extensionManager = nullptr;
}

bool DeviceManagerVK::CreateInstanceInternal()
{
	if (VK_SUCCESS != InitializeLoader())
	{
		LogFatal(LogVulkan) << "Failed to initialize Vulkan loader" << endl;
		return false;
	}

	if (!m_extensionManager)
	{
		m_extensionManager = new ExtensionManager{};
	}

	if (!m_extensionManager->Initialize())
	{
		return false;
	}

	SetRequiredInstanceLayersAndExtensions();

	VkApplicationInfo appInfo{ VK_STRUCTURE_TYPE_APPLICATION_INFO };
	appInfo.pApplicationName = m_desc.appName.c_str();
	appInfo.pEngineName = "Kodiak";
	appInfo.apiVersion = VK_API_VERSION_1_3;

	vector<const char*> instanceExtensions;
	vector<const char*> instanceLayers;
	m_extensionManager->GetEnabledInstanceExtensions(instanceExtensions);
	m_extensionManager->GetEnabledInstanceLayers(instanceLayers);

	VkInstanceCreateInfo createInfo{ VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = (uint32_t)instanceExtensions.size();
	createInfo.ppEnabledExtensionNames = instanceExtensions.data();
	createInfo.enabledLayerCount = (uint32_t)instanceLayers.size();
	createInfo.ppEnabledLayerNames = instanceLayers.data();

	VkInstance vkInstance{ VK_NULL_HANDLE };
	if (VK_FAILED(vkCreateInstance(&createInfo, nullptr, &vkInstance)))
	{
		LogFatal(LogVulkan) << "Failed to create Vulkan instance" << endl;
		return false;
	}

	uint32_t instanceVersion{ 0 };
	if (VK_SUCCEEDED(vkEnumerateInstanceVersion(&instanceVersion)))
	{
		m_versionInfo = DecodeVulkanVersion(instanceVersion);

		LogInfo(LogVulkan) << format("Created Vulkan instance, variant {}, API version {}",
			m_versionInfo.variant, m_versionInfo) << endl;
	}
	else
	{
		LogInfo(LogVulkan) << "Created Vulkan instance, but failed to enumerate version" << endl;
	}

	LoadInstanceFunctionsOnly(vkInstance);

	m_instance = VkInstanceHandle::Create(new CVkInstance(vkInstance));

	return true;
}


bool DeviceManagerVK::CreateDevice()
{
	return true;
}


bool DeviceManagerVK::CreateSwapChain()
{
	return true;
}


void DeviceManagerVK::SetRequiredInstanceLayersAndExtensions()
{
	vector<string> requiredLayers{};
	if (m_desc.enableDebugRuntime)
	{
		requiredLayers.push_back("VK_LAYER_KHRONOS_validation");
	}
	m_extensionManager->SetRequiredInstanceLayers(requiredLayers);

	vector<string> requiredExtensions{
		"VK_EXT_debug_report",
		"VK_KHR_win32_surface",
		"VK_KHR_surface"
	};
	m_extensionManager->SetRequiredInstanceExtensions(requiredExtensions);
}

} // namespace Kodiak::VK