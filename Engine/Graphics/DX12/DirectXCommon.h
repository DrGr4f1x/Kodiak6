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

// DirectX 12 headers
#define FORCE_D3D12_VALIDATION 0
#define ENABLE_D3D12_VALIDATION (ENABLE_VALIDATION || FORCE_D3D12_VALIDATION)

#define FORCE_D3D12_DEBUG_MARKERS 0
#define ENABLE_D3D12_DEBUG_MARKERS (ENABLE_DEBUG_MARKERS || FORCE_D3D12_DEBUG_MARKERS)

#include <dxgi1_4.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <dxgiformat.h>
#include "directx\d3d12.h"
#include "directx\d3dx12.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")


#include "Graphics\GraphicsCommon.h"
#include "Graphics\DX12\Enums12.h"


namespace Kodiak::DX12
{

void SetDebugName(IDXGIObject* object, const std::string& name);
void SetDebugName(ID3D12Object* object, const std::string& name);

inline LogCategory LogDirectX{ "LogDirectX" };

} // namespace Kodiak::DX12