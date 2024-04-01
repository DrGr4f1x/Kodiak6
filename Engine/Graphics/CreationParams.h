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


struct PixelBufferCreationParams
{
	std::string name;
	ResourceType resourceType{ ResourceType::Texture2D };
	uint64_t width{ 0 };
	uint32_t height{ 0 };
	uint32_t arraySizeOrDepth{ 0 };
	uint32_t numMips{ 1 };
	uint32_t numSamples{ 1 };
	Format format{ Format::Unknown };
};


struct ColorBufferCreationParams : public PixelBufferCreationParams
{
	uint32_t numFragments{ 1 };
	Color clearColor{ DirectX::Colors::Black };

	ColorBufferCreationParams& SetName(const std::string& value) { name = value; return *this; }
	constexpr ColorBufferCreationParams& SetResourceType(ResourceType value) noexcept { resourceType = value; return *this; }
	constexpr ColorBufferCreationParams& SetWidth(uint64_t value) noexcept { width = value; return *this; }
	constexpr ColorBufferCreationParams& SetHeight(uint32_t value) noexcept { height = value; return *this; }
	constexpr ColorBufferCreationParams& SetArraySize(uint32_t value) noexcept { arraySizeOrDepth = value; return *this; }
	constexpr ColorBufferCreationParams& SetDepth(uint32_t value) noexcept { arraySizeOrDepth = value; return *this; }
	constexpr ColorBufferCreationParams& SetNumMips(uint32_t value) noexcept { numMips = value; return *this; }
	constexpr ColorBufferCreationParams& SetNumSamples(uint32_t value) noexcept { numSamples = value; return *this; }
	constexpr ColorBufferCreationParams& SetFormat(Format value) noexcept { format = value; return *this; }
	constexpr ColorBufferCreationParams& SetNumFragments(uint32_t value) noexcept { numFragments = value; return *this; }
	ColorBufferCreationParams& SetClearColor(Color value) noexcept { clearColor = value; return *this; }
};


struct DepthBufferCreationParams : public PixelBufferCreationParams
{
	float clearDepth{ 1.0f };
	uint8_t clearStencil{ 0 };

	DepthBufferCreationParams& SetName(const std::string& value) { name = value; return *this; }
	constexpr DepthBufferCreationParams& SetResourceType(ResourceType value) noexcept { resourceType = value; return *this; }
	constexpr DepthBufferCreationParams& SetWidth(uint64_t value) noexcept { width = value; return *this; }
	constexpr DepthBufferCreationParams& SetHeight(uint32_t value) noexcept { height = value; return *this; }
	constexpr DepthBufferCreationParams& SetArraySize(uint32_t value) noexcept { arraySizeOrDepth = value; return *this; }
	constexpr DepthBufferCreationParams& SetDepth(uint32_t value) noexcept { arraySizeOrDepth = value; return *this; }
	constexpr DepthBufferCreationParams& SetNumMips(uint32_t value) noexcept { numMips = value; return *this; }
	constexpr DepthBufferCreationParams& SetNumSamples(uint32_t value) noexcept { numSamples = value; return *this; }
	constexpr DepthBufferCreationParams& SetFormat(Format value) noexcept { format = value; return *this; }
	constexpr DepthBufferCreationParams& SetClearDepth(float value) noexcept { clearDepth = value; return *this; }
	constexpr DepthBufferCreationParams& SetClearStencil(uint8_t value) noexcept { clearStencil = value; return *this; }
};

} // namespace Kodiak
