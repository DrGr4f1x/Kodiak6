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

#include "LoaderVk.h"

namespace Kodiak::VK
{

//
// VkInstance
//
class CVkInstance : public IntrusiveCounter<IObject>, public NonCopyable
{
public:
	CVkInstance() noexcept = default;
	explicit CVkInstance(VkInstance instance) noexcept : m_instance{ instance } {}
	
	~CVkInstance() final
	{
		if (m_instance)
		{
			vkDestroyInstance(m_instance, nullptr);
			m_instance = VK_NULL_HANDLE;
		}
	}

	VkInstance Get() const noexcept { return m_instance; }
	operator VkInstance() const noexcept { return Get(); }

private:
	VkInstance m_instance{ VK_NULL_HANDLE };
};

using VkInstanceHandle = IntrusivePtr<CVkInstance>;

} // namespace Kodiak::VK