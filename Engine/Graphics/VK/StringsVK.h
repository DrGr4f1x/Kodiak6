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

inline std::string VkTypeToString(VkPhysicalDeviceType physicalDeviceType)
{
	switch (physicalDeviceType)
	{
	case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:	return "Integrated GPU"; break;
	case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:		return "Discrete GPU"; break;
	case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:		return "Virtual GPU"; break;
	default:										return "Other"; break;
	}
}


inline std::string VkTypeToString(VkSampleCountFlags sampleCountFlags)
{
	const uint32_t numFlags = __popcnt(sampleCountFlags);

	static const std::string countMap[] = {	
		"1",
		"2",
		"4",
		"8",
		"16",
		"32",
		"64"
	};

	std::string result;
	uint32_t testBit = 1;
	uint32_t bitsCounted = 0;
	for (uint32_t i = 1; i < _countof(countMap); ++i)
	{
		if ((sampleCountFlags & testBit) == testBit)
		{
			++bitsCounted;
			result += countMap[i-1];
			if (bitsCounted != numFlags)
			{
				result += ", ";
			}
		}
		testBit = (1 << i);
	}

	return result;
}

} // namespace Kodiak::VK


#define DECLARE_STRING_FORMATTERS(VK_TYPE) \
template <> \
struct std::formatter<VK_TYPE> : public std::formatter<std::string> \
{ \
	auto format(VK_TYPE value, std::format_context& ctx) const \
	{ \
		auto str = Kodiak::VK::VkTypeToString(value); \
		return std::formatter<std::string>::format(str, ctx); \
	} \
}; \
inline std::ostream& operator<<(VK_TYPE type, std::ostream& os) { os << Kodiak::VK::VkTypeToString(type); return os; }


DECLARE_STRING_FORMATTERS(VkPhysicalDeviceType)

#undef DECLARE_STRING_FORMATTERS