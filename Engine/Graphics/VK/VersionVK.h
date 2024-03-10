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

struct VulkanVersionInfo
{
	uint32_t variant{ 0 };
	uint32_t major{ 0 };
	uint32_t minor{ 0 };
	uint32_t patch{ 0 };
};

VulkanVersionInfo DecodeVulkanVersion(uint32_t packedVersion);
std::string VulkanVersionInfoToString(VulkanVersionInfo versionInfo);
std::string VulkanVersionToString(uint32_t packedVersion);

} // namespace Kodiak::VK


template <>
struct std::formatter<Kodiak::VK::VulkanVersionInfo> : public std::formatter<std::string>
{
	auto format(Kodiak::VK::VulkanVersionInfo value, std::format_context& ctx) const
	{
		auto str = Kodiak::VK::VulkanVersionInfoToString(value);
		return std::formatter<std::string>::format(str, ctx);
	}
};

inline std::ostream& operator<<(Kodiak::VK::VulkanVersionInfo type, std::ostream& os)
{ 
	os << Kodiak::VK::VulkanVersionInfoToString(type);
	return os; 
}