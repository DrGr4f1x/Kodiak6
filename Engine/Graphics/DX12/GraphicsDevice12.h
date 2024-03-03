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

namespace Kodiak::DX12
{

class GraphicsDevice : public TRefCount<Kodiak::IGraphicsDevice>
{
public:
	GraphicsDevice();
	~GraphicsDevice() final;
};

using DeviceHandle = Microsoft::WRL::ComPtr<Kodiak::DX12::GraphicsDevice>;

Kodiak::DX12::GraphicsDevice* CreateDevice12(const GraphicsDeviceDesc& desc);

} // namespace Kodiak::DX12