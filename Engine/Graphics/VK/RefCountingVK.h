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
	explicit CVkInstance(VkInstance instance) noexcept 
		: m_instance{ instance } 
	{}

	~CVkInstance() final
	{
		Destroy();
	}

	VkInstance Get() const noexcept { return m_instance; }
	operator VkInstance() const noexcept { return Get(); }

	void Destroy();

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
		Destroy();
	}

	VkPhysicalDevice Get() const noexcept { return m_physicalDevice; }
	operator VkPhysicalDevice() const noexcept { return Get(); }

	void Destroy();

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

	~CVkDevice() final
	{
		Destroy();
	}

	VkDevice Get() const noexcept { return m_device; }
	operator VkDevice() const { return Get(); }

	void Destroy();

private:
	VkPhysicalDeviceHandle m_physicalDevice;
	VkDevice m_device{ VK_NULL_HANDLE };
};
using VkDeviceHandle = IntrusivePtr<CVkDevice>;


//
// VkSurfaceKHR
//
class CVkSurface : public IntrusiveCounter<IObject>, public NonCopyable
{
public:
	CVkSurface() noexcept = default;
	CVkSurface(CVkInstance* instance, VkSurfaceKHR surface) noexcept
		: m_instance{ instance }
		, m_surfaceKHR{ surface }
	{}

	~CVkSurface() final
	{
		Destroy();
	}

	VkSurfaceKHR Get() const noexcept { return m_surfaceKHR; }
	operator VkSurfaceKHR() const noexcept { return Get(); }

	void Destroy();

private:
	VkInstanceHandle m_instance;
	VkSurfaceKHR m_surfaceKHR{ VK_NULL_HANDLE };
};
using VkSurfaceHandle = IntrusivePtr<CVkSurface>;


//
// VmaAllocator
//
class CVmaAllocator : public IntrusiveCounter<IObject>, public NonCopyable
{
public:
	CVmaAllocator() noexcept = default;
	CVmaAllocator(CVkDevice* device, VmaAllocator allocator) noexcept
		: m_device{ device }
		, m_allocator{ allocator }
	{}

	~CVmaAllocator() final
	{
		Destroy();
	}

	VmaAllocator Get() const noexcept { return m_allocator; }
	operator VmaAllocator() const noexcept { return Get(); }

	void Destroy();

private:
	VkDeviceHandle m_device;
	VmaAllocator m_allocator{ VK_NULL_HANDLE };
};
using VmaAllocatorHandle = IntrusivePtr<CVmaAllocator>;


//
// VkImage
//
class CVkImage : public IntrusiveCounter<IObject>, public NonCopyable
{
public:
	CVkImage(CVkDevice* cdevice, VkImage image) noexcept
		: m_device{ cdevice }
		, m_allocator{}
		, m_image{ image }
		, m_allocation{ VK_NULL_HANDLE }
	{}

	CVkImage(CVkDevice* device, CVmaAllocator* allocator, VkImage image, VmaAllocation allocation) noexcept
		: m_device{ device }
		, m_allocator{ allocator }
		, m_image{ image }
		, m_allocation{ allocation }
		, m_bOwnsImage{ true }
	{}

	~CVkImage() final
	{
		Destroy();
	}

	VkImage Get() const noexcept { return m_image; }
	operator VkImage() const noexcept { return Get(); }

	void Destroy();

private:
	VkDeviceHandle m_device;
	VmaAllocatorHandle m_allocator;
	VkImage m_image{ VK_NULL_HANDLE };
	VmaAllocation m_allocation{ VK_NULL_HANDLE };
	bool m_bOwnsImage{ false };
};
using VkImageHandle = IntrusivePtr<CVkImage>;


//
// VkSwapchainKHR
//
class CVkSwapchain : public IntrusiveCounter<IObject>, public NonCopyable
{
public:
	CVkSwapchain() noexcept = default;
	CVkSwapchain(CVkDevice* device, VkSwapchainKHR swapchain)
		: m_device{ device }
		, m_swapchainKHR{ swapchain }
	{}

	~CVkSwapchain()
	{
		Destroy();
	}

	VkSwapchainKHR Get() const noexcept { return m_swapchainKHR; }
	operator VkSwapchainKHR() const noexcept { return Get(); }

	void Destroy();

private:
	VkDeviceHandle m_device;
	VkSwapchainKHR m_swapchainKHR{ VK_NULL_HANDLE };
};
using VkSwapchainHandle = IntrusivePtr<CVkSwapchain>;


//
// VkSemaphore
//
class CVkSemaphore : public IntrusiveCounter<IObject>, public NonCopyable
{
public:
	CVkSemaphore() noexcept = default;
	CVkSemaphore(CVkDevice* device, VkSemaphore semaphore)
		: m_device{ device }
		, m_semaphore{ semaphore }
	{}

	~CVkSemaphore()
	{
		Destroy();
	}

	VkSemaphore Get() const noexcept { return m_semaphore; }
	operator VkSemaphore() const noexcept { return Get(); }

	void Destroy();

private:
	VkDeviceHandle m_device;
	VkSemaphore m_semaphore{ VK_NULL_HANDLE };
};
using VkSemaphoreHandle = IntrusivePtr<CVkSemaphore>;


//
// VkDebugUtilsMessengerEXT
//
class CVkDebugUtilsMessenger : public IntrusiveCounter<IObject>, public NonCopyable
{
public:
	CVkDebugUtilsMessenger() noexcept = default;
	CVkDebugUtilsMessenger(CVkInstance* instance, VkDebugUtilsMessengerEXT messenger)
		: m_instance{ instance }
		, m_messenger{ messenger }
	{}

	~CVkDebugUtilsMessenger()
	{
		Destroy();
	}

	VkDebugUtilsMessengerEXT Get() const noexcept { return m_messenger; }
	operator VkDebugUtilsMessengerEXT() const noexcept { return Get(); }

	void Destroy();

private:
	VkInstanceHandle m_instance;
	VkDebugUtilsMessengerEXT m_messenger{ VK_NULL_HANDLE };
};
using VkDebugUtilsMessengerHandle = IntrusivePtr<CVkDebugUtilsMessenger>;

} // namespace Kodiak::VK