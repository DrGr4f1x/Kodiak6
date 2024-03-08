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

#include "Graphics\GraphicsDevice.h"

namespace Kodiak::VK
{

class GraphicsDevice : public TRefCount<Kodiak::IGraphicsDevice>
{
public:
	GraphicsDevice();
	~GraphicsDevice() final;

	void Initialize(const GraphicsDeviceDesc& desc);
};

using DeviceHandle = Microsoft::WRL::ComPtr<GraphicsDevice>;

GraphicsDevice* CreateDeviceVK(const GraphicsDeviceDesc& desc);

inline LogCategory LogVulkan{ "LogVulkan" };

} // namespace Kodiak::VK