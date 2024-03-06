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

	HINSTANCE hinst{ 0 };
	HWND hwnd{ 0 };

	uint32_t width{ 0 };
	uint32_t height{ 0 };
	bool vsync{ false };

	Format colorFormat{ Format::SRGBA8_UNorm };
	Format depthFormat{ Format::D32S8 };
};


class IGraphicsDevice : public IObject
{
public:
	static GUID IID;

	virtual ~IGraphicsDevice() = default;
};

using DeviceHandle = Microsoft::WRL::ComPtr<IGraphicsDevice>;


extern IGraphicsDevice* g_graphicsDevice;


DeviceHandle CreateDevice(const GraphicsDeviceDesc& desc);

bool IsDeveloperModeEnabled();

bool IsRenderDocAvailable();

} // namespace Kodiak