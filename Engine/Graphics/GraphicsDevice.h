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

};

class IGraphicsDevice : public IObject
{
public:
	static GUID IID;

	virtual ~IGraphicsDevice() = default;
};

using DeviceHandle = Microsoft::WRL::ComPtr<IGraphicsDevice>;

DeviceHandle CreateDevice(const GraphicsDeviceDesc& desc);

} // namespace Kodiak