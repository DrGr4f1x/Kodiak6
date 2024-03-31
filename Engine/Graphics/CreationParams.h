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

#include "Graphics\Enums.h"
#include "Graphics\Formats.h"


namespace Kodiak
{

struct DeviceManagerCreationParams
{
	std::string appName{};
	GraphicsApi graphicsApi{ GraphicsApi::D3D12 };
	bool enableValidation{ false };
	bool enableDebugMarkers{ false };
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

	HWND hwnd{ nullptr };
	HINSTANCE hinstance{ nullptr };

	// Setters
	DeviceManagerCreationParams& SetAppName(const std::string& value) { appName = value; return *this; }
	constexpr DeviceManagerCreationParams& SetGraphicsApi(GraphicsApi value) noexcept { graphicsApi = value; return *this; }
	constexpr DeviceManagerCreationParams& SetEnableValidation(bool value) noexcept { enableValidation = value; return *this; }
	constexpr DeviceManagerCreationParams& SetEnableDebugMarkers(bool value) noexcept { enableDebugMarkers = value; return *this; }
	constexpr DeviceManagerCreationParams& SetLogDeviceCaps(bool value) noexcept { logDeviceCaps = value; return *this; }
	constexpr DeviceManagerCreationParams& SetAllowSoftwareDevice(bool value) noexcept { allowSoftwareDevice = value; return *this; }
	constexpr DeviceManagerCreationParams& SetPreferDiscreteDevice(bool value) noexcept { preferDiscreteDevice = value; return *this; }
	constexpr DeviceManagerCreationParams& SetStartMaximized(bool value) noexcept { startMaximized = value; return *this; }
	constexpr DeviceManagerCreationParams& SetStartFullscreen(bool value) noexcept { startFullscreen = value; return *this; }
	constexpr DeviceManagerCreationParams& SetAllowModeSwitch(bool value) noexcept { allowModeSwitch = value; return *this; }
	constexpr DeviceManagerCreationParams& SetWindowPosX(uint32_t value) noexcept { windowPosX = value; return *this; }
	constexpr DeviceManagerCreationParams& SetWindowPosY(uint32_t value) noexcept { windowPosY = value; return *this; }
	constexpr DeviceManagerCreationParams& SetBackBufferWidth(uint32_t value) noexcept { backBufferWidth = value; return *this; }
	constexpr DeviceManagerCreationParams& SetBackBufferHeight(uint32_t value) noexcept { backBufferHeight = value; return *this; }
	constexpr DeviceManagerCreationParams& SetRefreshRate(uint32_t value) noexcept { refreshRate = value; return *this; }
	constexpr DeviceManagerCreationParams& SetEnableVSync(bool value) noexcept { enableVSync = value; return *this; }
	constexpr DeviceManagerCreationParams& SetNumSwapChainBuffers(uint32_t value) noexcept { numSwapChainBuffers = value; return *this; }
	constexpr DeviceManagerCreationParams& SetSwapChainFormat(Format value) noexcept { swapChainFormat = value; return *this; }
	constexpr DeviceManagerCreationParams& SetSwapChainSampleCount(uint32_t value) noexcept { swapChainSampleCount = value; return *this; }
	constexpr DeviceManagerCreationParams& SetSwapChainSampleQuality(uint32_t value) noexcept { swapChainSampleQuality = value; return *this; }
	constexpr DeviceManagerCreationParams& SetMaxFramesInFlight(uint32_t value) noexcept { maxFramesInFlight = value; return *this; }
	constexpr DeviceManagerCreationParams& SetEnablePerMonitorDPI(bool value) noexcept { enablePerMonitorDPI = value; return *this; }
	constexpr DeviceManagerCreationParams& SetHwnd(HWND value) noexcept { hwnd = value; return *this; }
	constexpr DeviceManagerCreationParams& SetHinstance(HINSTANCE value) noexcept { hinstance = value; return *this; }
};

} // namespace Kodiak
