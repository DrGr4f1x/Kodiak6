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

#include "Graphics\GraphicsCommon.h"


namespace Kodiak
{

struct AdapterInfo
{
	std::string name{};
	uint32_t vendorId{ 0 };
	uint32_t deviceId{ 0 };
	size_t dedicatedVideoMemory{ 0 };
	size_t dedicatedSystemMemory{ 0 };
	size_t sharedSystemMemory{ 0 };
	HardwareVendor vendor{ HardwareVendor::Unknown };
	AdapterType adapterType{ AdapterType::Other };
};


struct DeviceDesc
{
	std::string appName{};
	bool enableDebugRuntime{ false };
	bool logDeviceCaps{ true };
	bool allowSoftwareDevice{ false };
	bool preferDiscreteDevice{ true };

	// TODO - set these values from ApplicationInfo
	bool startMaximized{ false };
	bool startFullscreen{ false };
	bool allowModeSwitch{ true };
	int32_t windowPosX{ -1 };
	int32_t windowPosY{ -1 };
	uint32_t backBufferWidth{ 1920 };
	uint32_t backBufferHeight{ 1080 };
	uint32_t refreshRate{ 0 };
	bool enableVSync{ false };

	uint32_t numSwapChainBuffers{ 3 };
	Format swapChainFormat{ Format::SRGBA8_UNorm };
	uint32_t swapChainSampleCount{ 1 };
	uint32_t swapChainSampleQuality{ 0 };
	uint32_t maxFramesInFlight{ 2 };
	bool enablePerMonitorDPI{ false };

	// Setters
	DeviceDesc& SetAppName(const std::string& value) { appName = value; return *this; }
	constexpr DeviceDesc& SetEnableDebugRuntime(bool value) { enableDebugRuntime = value; return *this; }
	constexpr DeviceDesc& SetLogDeviceCaps(bool value) { logDeviceCaps = value; return *this; }
	constexpr DeviceDesc& SetAllowSoftwareDevice(bool value) { allowSoftwareDevice = value; return *this; }
	constexpr DeviceDesc& SetPreferDiscreteDevice(bool value) { preferDiscreteDevice = value; return *this; }
	constexpr DeviceDesc& SetStartMaximized(bool value) { startMaximized = value; return *this; }
	constexpr DeviceDesc& SetStartFullscreed(bool value) { startFullscreen = value; return *this; }
	constexpr DeviceDesc& SetAllowModeSwitch(bool value) { allowModeSwitch = value; return *this; }
	constexpr DeviceDesc& SetWindowPosX(uint32_t value) { windowPosX = value; return *this; }
	constexpr DeviceDesc& SetWindowPosY(uint32_t value) { windowPosY = value; return *this; }
	constexpr DeviceDesc& SetBackBufferWidth(uint32_t value) { backBufferWidth = value; return *this; }
	constexpr DeviceDesc& SetBackBufferHeight(uint32_t value) { backBufferHeight = value; return *this; }
	constexpr DeviceDesc& SetRefreshRate(uint32_t value) { refreshRate = value; return *this; }
	constexpr DeviceDesc& SetEnableVSync(bool value) { enableVSync = value; return *this; }
	constexpr DeviceDesc& SetNumSwapChainBuffers(uint32_t value) { numSwapChainBuffers = value; return *this; }
	constexpr DeviceDesc& SetSwapChainFormat(Format value) { swapChainFormat = value; return *this; }
	constexpr DeviceDesc& SetSwapChainSampleCount(uint32_t value) { swapChainSampleCount = value; return *this; }
	constexpr DeviceDesc& SetSwapChainSampleQuality(uint32_t value) { swapChainSampleQuality = value; return *this; }
	constexpr DeviceDesc& SetMaxFramesInFlight(uint32_t value) { maxFramesInFlight = value; return *this; }
	constexpr DeviceDesc& SetEnablePerMonitorDPI(bool value) { enablePerMonitorDPI = value; return *this; }
};


class DeviceManager
{
public:
	static DeviceManager* Create(GraphicsApi api);

	DeviceManager() = default;
	virtual ~DeviceManager() = default;

	bool CreateDeviceAndSwapChain(const DeviceDesc& desc);

	bool CreateInstance();

protected:
	virtual bool CreateInstanceInternal() = 0;
	virtual bool CreateDevice() = 0;
	virtual bool CreateSwapChain() = 0;

protected:
	DeviceDesc m_desc{};
	bool m_instanceCreated{ false };

	bool m_bIsDeveloperModeEnabled{ false };
	bool m_bIsRenderDocAvailable{ false };
};

} // namespace Kodiak