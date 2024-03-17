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

#include "Graphics\VK\VulkanCommon.h"


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
	~CVkInstance() final;

	VkInstance Get() const noexcept { return m_instance; }
	operator VkInstance() const noexcept { return Get(); }

private:
	VkInstance m_instance{ VK_NULL_HANDLE };
};
using VkInstanceHandle = IntrusivePtr<CVkInstance>;


//
// VkPhysicalDevice
//
class CVkPhysicalDevice : public IntrusiveCounter<IObject>, public NonCopyable
{
public:
	CVkPhysicalDevice() noexcept = default;
	CVkPhysicalDevice(CVkInstance* cinstance, VkPhysicalDevice physicalDevice) noexcept
		: m_instance{ cinstance }
		, m_physicalDevice{ physicalDevice }
	{}

	~CVkPhysicalDevice() final
	{
		m_physicalDevice = VK_NULL_HANDLE;
	}

	VkPhysicalDevice Get() const noexcept { return m_physicalDevice; }
	operator VkPhysicalDevice() const noexcept { return Get(); }

private:
	VkInstanceHandle m_instance;
	VkPhysicalDevice m_physicalDevice{ VK_NULL_HANDLE };
};
using VkPhysicalDeviceHandle = IntrusivePtr<CVkPhysicalDevice>;


//
// VkDevice
//
class CVkDevice : public IntrusiveCounter<IObject>, public NonCopyable
{
public:
	CVkDevice() noexcept = default;
	CVkDevice(CVkPhysicalDevice* physicalDevice, VkDevice device) noexcept
		: m_physicalDevice{ physicalDevice }
		, m_device{ device }
	{}
	~CVkDevice() final;

	VkDevice Get() const noexcept { return m_device; }
	operator VkDevice() const { return Get(); }

private:
	VkPhysicalDeviceHandle m_physicalDevice;
	VkDevice m_device{ VK_NULL_HANDLE };
};


//
// VkSurfaceKHR
//
class CVkSurface : public IntrusiveCounter<IObject>, public NonCopyable
{
public:
	CVkSurface() noexcept = default;
	~CVkSurface() final;

	VkSurfaceKHR Get() const noexcept { return m_surfaceKHR; }
	operator VkSurfaceKHR() const noexcept { return m_surfaceKHR; }

private:
	VkInstanceHandle m_instance;
	VkSurfaceKHR m_surfaceKHR{ VK_NULL_HANDLE };
};

} // namespace Kodiak::VK