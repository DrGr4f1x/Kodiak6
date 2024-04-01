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

// Forward declarations
enum class Format : uint8_t;
enum class ResourceType : uint32_t;
struct ColorBufferCreationParams;
struct DepthBufferCreationParams;


class IGpuResource : public IObject
{
public:
	virtual ResourceType GetType() const noexcept = 0;
};
using GpuResourceHandle = IntrusivePtr<IGpuResource>;


class IPixelBuffer : public IGpuResource
{
public:
	virtual uint64_t GetWidth() const noexcept = 0;
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


class ICommandContext : public IObject
{
public:
	virtual ~ICommandContext() = default;

	virtual void Finish(bool bWaitForCompletion = false) = 0;

	virtual void BeginEvent(const std::string& label) = 0;
	virtual void EndEvent() = 0;
	virtual void SetMarker(const std::string& label) = 0;
};
using CommandContextHandle = IntrusivePtr<ICommandContext>;


class IGraphicsContext : public ICommandContext
{
public:
	virtual ~IGraphicsContext() = default;
};
using GraphicsContextHandle = IntrusivePtr<IGraphicsContext>;


class IComputeContext : public ICommandContext
{
public:
	virtual ~IComputeContext() = default;
};
using ComputeContextHandle = IntrusivePtr<IComputeContext>;


class IGraphicsDevice : public IObject
{
public:
	virtual ~IGraphicsDevice() = default;

	virtual bool Initialize() = 0;
	virtual bool CreateSwapChain() = 0;

	virtual void BeginFrame() = 0;
	virtual void Present() = 0;

	virtual ColorBufferHandle CreateColorBuffer(const ColorBufferCreationParams& creationParams) = 0;
	virtual DepthBufferHandle CreateDepthBuffer(const DepthBufferCreationParams& creationParams) = 0;

	virtual CommandContextHandle BeginCommandContext(const std::string& ID = "") = 0;
	virtual GraphicsContextHandle BeginGraphicsContext(const std::string& ID = "") = 0;
	virtual ComputeContextHandle BeginComputeContext(const std::string& ID = "", bool bAsync = false) = 0;

	virtual ColorBufferHandle GetCurrentSwapChainBuffer() = 0;
};
using DeviceHandle = IntrusivePtr<IGraphicsDevice>;


class IDeviceManager : public IObject
{
public:
	virtual ~IDeviceManager() = default;

	virtual void BeginFrame() = 0;
	virtual void Present() = 0;
};
using DeviceManagerHandle = IntrusivePtr<IDeviceManager>;

} // namespace Kodiak