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

#include "Graphics\GraphicsEnums.h"

namespace Kodiak::DX12
{

D3D12_BLEND BlendToDX12(Blend blend);

D3D12_BLEND_OP BlendOpToDX12(BlendOp blendOp);

D3D12_LOGIC_OP LogicOpToDX12(LogicOp logicOp);

D3D12_COLOR_WRITE_ENABLE ColorWriteToDX12(ColorWrite colorWrite);

D3D12_DEPTH_WRITE_MASK DepthWriteToDX12(DepthWrite depthWrite);

} // namespace Kodiak::DX12