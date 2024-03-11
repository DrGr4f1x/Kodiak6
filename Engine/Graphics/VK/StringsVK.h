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


inline std::string VkTypeToString(VkConformanceVersion conformanceVersion)
{
	return std::format("{}.{}.{}.{}", conformanceVersion.major, conformanceVersion.minor, conformanceVersion.subminor, conformanceVersion.patch);
}


inline std::string VkTypeToString(VkDriverId driverId)
{
	switch (driverId)
	{
	case VK_DRIVER_ID_AMD_PROPRIETARY: return "AMD Proprietary"; break;
	case VK_DRIVER_ID_AMD_OPEN_SOURCE: return "AMD Open Source"; break;
	case VK_DRIVER_ID_MESA_RADV: return "Mesa RADV"; break;
	case VK_DRIVER_ID_NVIDIA_PROPRIETARY: return "NVIDIA Proprietary"; break;
	case VK_DRIVER_ID_INTEL_PROPRIETARY_WINDOWS: return "Intel Proprietary Windows"; break;
	case VK_DRIVER_ID_INTEL_OPEN_SOURCE_MESA: return "Intel Open Source Mesa"; break;
	case VK_DRIVER_ID_IMAGINATION_PROPRIETARY: return "Imagination Proprietary"; break;
	case VK_DRIVER_ID_QUALCOMM_PROPRIETARY: return "Qualcomm Proprietary"; break;
	case VK_DRIVER_ID_ARM_PROPRIETARY: return "ARM Proprietary"; break;
	case VK_DRIVER_ID_GOOGLE_SWIFTSHADER: return "Google SwiftShader"; break;
	case VK_DRIVER_ID_GGP_PROPRIETARY: return "GGP Proprietary"; break;
	case VK_DRIVER_ID_BROADCOM_PROPRIETARY: return "Broadcom Proprietary"; break;
	case VK_DRIVER_ID_MESA_LLVMPIPE: return "Mesa LLVMpipe"; break;
	case VK_DRIVER_ID_MOLTENVK: return "MoltenVK"; break;
	case VK_DRIVER_ID_COREAVI_PROPRIETARY: return "CoreAVI Proprietary"; break;
	case VK_DRIVER_ID_JUICE_PROPRIETARY: return "Juice Proprietary"; break;
	case VK_DRIVER_ID_VERISILICON_PROPRIETARY: return "VeriSilicon Proprietary"; break;
	case VK_DRIVER_ID_MESA_TURNIP: return "Mesa Turnip"; break;
	case VK_DRIVER_ID_MESA_V3DV: return "Mesa V3DV"; break;
	case VK_DRIVER_ID_MESA_PANVK: return "Mesa PanVK"; break;
	case VK_DRIVER_ID_SAMSUNG_PROPRIETARY: return "Samsung Proprietary"; break;
	case VK_DRIVER_ID_MESA_VENUS: return "Mesa Venus"; break;
	case VK_DRIVER_ID_MESA_DOZEN: return "Mesa Dozen"; break;
	case VK_DRIVER_ID_MESA_NVK: return "Mesa NVK"; break;
	case VK_DRIVER_ID_IMAGINATION_OPEN_SOURCE_MESA: return "Imagination Open Source Mesa"; break;
	case VK_DRIVER_ID_MESA_AGXV: return "Mesa AGXV"; break;
	default: return "Unknown"; break;
	}
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


inline std::string VkTypeToString(VkPointClippingBehavior pointClippingBehavior)
{
	switch (pointClippingBehavior)
	{
	case VK_POINT_CLIPPING_BEHAVIOR_USER_CLIP_PLANES_ONLY: return "User Clip Planes Only"; break;
	default: return "All Planes"; break;
	}
}


inline std::string VkTypeToString(VkShaderFloatControlsIndependence shaderFloatControlsIndependence)
{
	switch (shaderFloatControlsIndependence)
	{
	case VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_ALL: return "All"; break;
	case VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_NONE: return "None"; break;
	default: return "32-bit Only"; break;
	}
}


inline std::string VkSampleCountFlagsToString(VkSampleCountFlags sampleCountFlags)
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


inline std::string VkShaderStageFlagsToString(VkShaderStageFlags shaderStageFlags)
{
	const uint32_t numFlags = __popcnt(shaderStageFlags);

	static const std::string stageMap[]
	{
		"Vertex",
		"Tessellation Control",
		"Tessellation Evaluation",
		"Geometry",
		"Fragment",
		"Compute",
		"Task",
		"Mesh"
		"RayGen",
		"Any Hit",
		"Closest Hit",
		"Miss",
		"Intersection",
		"Callable"
	};

	std::string result;
	uint32_t testBit = 1;
	uint32_t bitsCounted = 0;
	for (uint32_t i = 1; i < _countof(stageMap); ++i)
	{
		if ((shaderStageFlags & testBit) == testBit)
		{
			++bitsCounted;
			result += stageMap[i - 1];
			if (bitsCounted != numFlags)
			{
				result += ", ";
			}
		}
		testBit = (1 << i);
	}
	if ((shaderStageFlags & VK_SHADER_STAGE_ALL_GRAPHICS) == VK_SHADER_STAGE_ALL_GRAPHICS)
	{
		result += ", All Graphics";
	}

	return result;
}


inline std::string VkSubgroupFeatureFlagsToString(VkSubgroupFeatureFlags subgroupFeatureFlags)
{
	const uint32_t numFlags = __popcnt(subgroupFeatureFlags);

	static const std::string subgroupFeatureMap[]
	{
		"Basic",
		"Vote",
		"Arithmetic",
		"Ballot",
		"Shuffle",
		"Shuffle Relative",
		"Clustered",
		"Quad",
		"Partition",
		"Rotate",
		"Rotate Clustered"
	};

	std::string result;
	uint32_t testBit = 1;
	uint32_t bitsCounted = 0;
	for (uint32_t i = 1; i < _countof(subgroupFeatureMap); ++i)
	{
		if ((subgroupFeatureFlags & testBit) == testBit)
		{
			++bitsCounted;
			result += subgroupFeatureMap[i - 1];
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
DECLARE_STRING_FORMATTERS(Kodiak::VK::LUID)
DECLARE_STRING_FORMATTERS(VkConformanceVersion)
DECLARE_STRING_FORMATTERS(VkDriverId)
DECLARE_STRING_FORMATTERS(VkPhysicalDeviceType)
DECLARE_STRING_FORMATTERS(VkPointClippingBehavior)
DECLARE_STRING_FORMATTERS(VkShaderFloatControlsIndependence)

#undef DECLARE_STRING_FORMATTERS