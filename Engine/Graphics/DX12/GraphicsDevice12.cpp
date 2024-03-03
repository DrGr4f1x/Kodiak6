//
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Author:  David Elder
//

#include "Stdafx.h"

#include "GraphicsDevice12.h"

using namespace Kodiak;
using namespace Kodiak::DX12;
using namespace std;


GraphicsDevice::GraphicsDevice()
{
	LOG_INFO << "Creating DirectX 12 device";
}


GraphicsDevice::~GraphicsDevice()
{
	LOG_INFO << "Destroying DirectX 12 device";
}


Kodiak::DX12::GraphicsDevice* Kodiak::DX12::CreateDevice12(const Kodiak::GraphicsDeviceDesc& desc)
{
	GraphicsDevice* device = new GraphicsDevice;
	return device;
}