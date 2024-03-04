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

D3D12_CULL_MODE CullModeToDX12(CullMode cullMode);

D3D12_FILL_MODE FillModeToDX12(FillMode fillMode);

D3D12_COMPARISON_FUNC ComparisonFuncToDX12(ComparisonFunc comparisonFunc);

D3D12_STENCIL_OP StencilOpToDX12(StencilOp stencilOp);

D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IndexBufferStripCutValueToDX12(IndexBufferStripCutValue indexBufferStripCutValue);

D3D12_PRIMITIVE_TOPOLOGY PrimitiveTopologyToDX12(PrimitiveTopology primitiveTopology);

D3D12_PRIMITIVE_TOPOLOGY_TYPE PrimitiveTopologyToPrimitiveTopologyTypeDX12(PrimitiveTopology primitiveTopology);

D3D12_SHADER_VISIBILITY ShaderStageToDX12(ShaderStage shaderStage);

D3D12_DESCRIPTOR_RANGE_TYPE DescriptorTypeToDX12(DescriptorType descriptorType);

} // namespace Kodiak::DX12