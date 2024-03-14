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

#include "DirectXCommon.h"

using namespace std;

namespace Kodiak::DX12
{

void SetDebugName(ID3D12Object* object, const string& name)
{
	bool bSetDebugName = g_graphicsDeviceOptions.useDebugRuntime;
#if ENABLE_DX12_DEBUG_MARKUP
	bSetDebugName = true;
#endif
	if (bSetDebugName)
	{
		object->SetPrivateData(WKPDID_D3DDebugObjectName, (UINT)name.size(), name.data());
	}
}

} // namespace Kodiak::DX12