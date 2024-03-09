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

#include "Formats.h"


namespace Kodiak
{

struct GraphicsDeviceDesc
{
	GraphicsApi api{ GraphicsApi::Unknown };

	std::string appName;

	HINSTANCE hinstance{ 0 };
	HWND hwnd{ 0 };

	uint32_t width{ 0 };
	uint32_t height{ 0 };
	bool vsync{ false };

	Format colorFormat{ Format::SRGBA8_UNorm };
	Format depthFormat{ Format::D32S8 };

	// Setters
	constexpr GraphicsDeviceDesc& SetAPI(GraphicsApi value) { api = value; return *this; }
	GraphicsDeviceDesc& SetAppName(const std::string& value) { appName = value; return *this; }
	constexpr GraphicsDeviceDesc& SetHInstance(HINSTANCE value) { hinstance = value; return *this; }
	constexpr GraphicsDeviceDesc& SetHWnd(HWND value) { hwnd = value; return *this; }
	constexpr GraphicsDeviceDesc& SetWidth(uint32_t value) { width = value; return *this; }
	constexpr GraphicsDeviceDesc& SetHeight(uint32_t value) { height = value; return *this; }
	constexpr GraphicsDeviceDesc& SetVSync(bool value) { vsync = value; return *this; }
	constexpr GraphicsDeviceDesc& SetColorFormat(Format value) { colorFormat = value; return *this; }
	constexpr GraphicsDeviceDesc& SetDepthFormat(Format value) { depthFormat = value; return *this; }
};


struct GraphicsDeviceOptions
{
	bool useDebugRuntime{ false };
	bool logDeviceFeatures{ true };
};

inline GraphicsDeviceOptions g_graphicsDeviceOptions{};


class IGraphicsDevice : public IObject
{
public:
	virtual ~IGraphicsDevice() = default;
};

using DeviceHandle = IntrusivePtr<IGraphicsDevice>;


inline IGraphicsDevice* g_graphicsDevice{ nullptr };


DeviceHandle CreateDevice(const GraphicsDeviceDesc& desc);

bool IsDeveloperModeEnabled();

bool IsRenderDocAvailable();

inline LogCategory LogGraphics{ "LogGraphics" };

} // namespace Kodiak