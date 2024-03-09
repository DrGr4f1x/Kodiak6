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

#include "TestApp.h"

using namespace Kodiak;


int main(int argc, char* argv[])
{
	GraphicsApi api = GetGraphicsApiFromCommandline(argc, argv);

	ApplicationDesc desc{ /*DO NOT MODIFY*/ s_appName, 1920, 1080, api };

	TestApp app(desc);
	app.Run();

	return 0;
}