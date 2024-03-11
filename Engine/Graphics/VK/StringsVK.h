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

// TODO - Move this somewhere else
struct UUID
{
	uint32_t value1{ 0 };
	uint16_t value2{ 0 };
	uint16_t value3{ 0 };
	uint16_t value4{ 0 };
	uint64_t value5{ 0 };
};

inline UUID AsUUID(uint8_t uuid[VK_UUID_SIZE])
{
	UUID result{};
	result.value1 = (uuid[0] << 24) | (uuid[1] << 16) | (uuid[2] << 8) | uuid[3];
	result.value2 = (uuid[4] << 8) | uuid[5];
	result.value3 = (uuid[6] << 8) | uuid[7];
	result.value4 = (uuid[8] << 8) | uuid[9];
	result.value5 = ((uint64_t)uuid[10] << 40) | ((uint64_t)uuid[11] << 32) | (uuid[12] << 24) | (uuid[13] << 16) | (uuid[14] << 8) | uuid[15];
	return result;
}


inline std::string VkTypeToString(UUID uuid)
{
	return std::format("{:08X}-{:04X}-{:04X}-{:04X}-{:012X}",
		uuid.value1, uuid.value2, uuid.value3, uuid.value4,	uuid.value5);
}


struct LUID
{
	uint32_t value1{ 0 };
	uint32_t value2{ 0 };
};

inline LUID AsLUID(uint8_t luid[VK_LUID_SIZE])
{
	LUID result{};
	result.value1 = (luid[0] << 24) | (luid[1] << 16) | (luid[2] << 8) | luid[3];
	result.value2 = (luid[4] << 24) | (luid[5] << 16) | (luid[6] << 8) | luid[7];
	return result;
}


inline std::string VkTypeToString(LUID luid)
{
	return std::format("{:08X}-{:08X}", luid.value1, luid.value2);
}


inline std::string VkTypeToString(uint8_t luid[VK_LUID_SIZE])
{
	return "luid";
}


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


DECLARE_STRING_FORMATTERS(Kodiak::VK::UUID)
DECLARE_STRING_FORMATTERS(Kodiak::VK::LUID);
DECLARE_STRING_FORMATTERS(VkPhysicalDeviceType)

#undef DECLARE_STRING_FORMATTERS