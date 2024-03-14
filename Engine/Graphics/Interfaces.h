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

#include "Graphics\Formats.h"

namespace Kodiak
{

// Forward declarations
enum class Format : uint8_t;
enum class ResourceType : uint32_t;


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

	constexpr GraphicsDeviceOptions& SetUseDebugRuntime(bool value) { useDebugRuntime = value; return *this; }
	constexpr GraphicsDeviceOptions& SetLogDeviceFeatures(bool value) { logDeviceFeatures = value; return *this; }
};

inline GraphicsDeviceOptions g_graphicsDeviceOptions{};


class IGpuResource : public IObject
{
public:
	virtual ResourceType GetType() const noexcept = 0;
};
using GpuResourceHandle = IntrusivePtr<IGpuResource>;


class IPixelBuffer : public IGpuResource
{
public:
	virtual uint32_t GetWidth() const noexcept = 0;
	virtual uint32_t GetHeight() const noexcept = 0;
	virtual uint32_t GetDepth() const noexcept = 0;
	virtual uint32_t GetArraySize() const noexcept = 0;
	virtual uint32_t GetNumMips() const noexcept = 0;
	virtual uint32_t GetNumSamples() const noexcept = 0;
	virtual Format GetFormat() const noexcept = 0;
};
using PixelBufferHandle = IntrusivePtr<IPixelBuffer>;


class IColorBuffer : public IPixelBuffer
{
public:
	virtual void SetClearColor(Color clearColor) noexcept = 0;
	virtual Color GetClearColor() const noexcept = 0;
	virtual void SetMsaaMode(uint32_t numColorSamples, uint32_t numCoverageSamples) noexcept = 0;
};
using ColorBufferHandle = IntrusivePtr<IColorBuffer>;


class IDepthBuffer : public IPixelBuffer
{
public:
	virtual float GetClearDepth() const noexcept = 0;
	virtual uint8_t GetClearStencil() const noexcept = 0;
};
using DepthBufferHandle = IntrusivePtr<IDepthBuffer>;


class IGraphicsDevice : public IObject
{
public:
	virtual ~IGraphicsDevice() = default;
};
using DeviceHandle = IntrusivePtr<IGraphicsDevice>;


} // namespace Kodiak