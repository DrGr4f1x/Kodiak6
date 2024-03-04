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

namespace Kodiak::DX12
{

struct DxgiFormatMapping
{
	Format engineFormat;
	DXGI_FORMAT resourceFormat;
	DXGI_FORMAT srvFormat;
	DXGI_FORMAT rtvFormat;
};

const DxgiFormatMapping& FormatToDxgi(Format engineFormat);

} // namespace Kodiak::DX12