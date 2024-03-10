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


namespace Kodiak::VK
{

inline std::string VkDeviceTypeToString(VkPhysicalDeviceType physicalDeviceType)
{
	switch (physicalDeviceType)
	{
	case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:	return "Integrated GPU"; break;
	case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:		return "Discrete GPU"; break;
	case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:		return "Virtual GPU"; break;
	default:										return "Other"; break;
	}
}


template <typename T> inline std::string VkTypeToString(T value)
{
	return std::format("{}", value);
}


template <> inline std::string VkTypeToString(VkPhysicalDeviceType value)
{
	return VkDeviceTypeToString(value);
}

} // namespace Kodiak::VK