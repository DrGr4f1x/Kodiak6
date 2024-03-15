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

#include "RefCountingVK.h"

namespace Kodiak::VK
{

CVkInstance::~CVkInstance()
{
	vkDestroyInstance(m_instance, nullptr);
	m_instance = VK_NULL_HANDLE;
}


CVkDevice::~CVkDevice()
{
	if (m_device)
	{
		vkDeviceWaitIdle(m_device);
	}
	vkDestroyDevice(m_device, nullptr);
	m_device = nullptr;
}

} // namespace Kodiak::VK