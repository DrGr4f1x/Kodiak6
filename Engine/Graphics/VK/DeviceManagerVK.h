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

#include "Graphics\DeviceManager.h"

namespace Kodiak::VK
{

class DeviceManagerVK : public DeviceManager
{
public:
	DeviceManagerVK() = default;
	~DeviceManagerVK() final = default;

protected:
	bool CreateInstanceInternal() final;
	bool CreateDevice() final;
	bool CreateSwapChain() final;
};

} // namespace Kodiak::VK