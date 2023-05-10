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

#include "TEMPLATEApp.h"

using namespace Kodiak;


int wmain(int argc, char** argv)
{
	GraphicsApi api = GetGraphicsApiFromCommandline(argc, argv);

	ApplicationDesc desc{
		"TEMPLATE",
		1920,
		1080,
		api
	};

	TEMPLATEApp app(desc);
	app.Run();

	return 0;
}