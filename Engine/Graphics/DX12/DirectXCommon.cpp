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

void SetDebugName(IDXGIObject* object, const string& name)
{
	if (g_graphicsDeviceOptions.ShouldUseDebugLayer())
	{
		object->SetPrivateData(WKPDID_D3DDebugObjectName, (UINT)name.size(), name.data());
	}
}


void SetDebugName(ID3D12Object* object, const string& name)
{
	if (g_graphicsDeviceOptions.ShouldUseDebugLayer())
	{
		object->SetName(MakeWStr(name).c_str());
	}
}

} // namespace Kodiak::DX12