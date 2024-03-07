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

#include "MySecondAppApp.h"

using namespace Kodiak;
using namespace std;


void MySecondAppApp::Configure()
{
	// Application config, before device creation
	Application::Configure();
}


void MySecondAppApp::Startup()
{
	// Application initialization, after device creation
}


void MySecondAppApp::Shutdown()
{
	// Application cleanup on shutdown
}


bool MySecondAppApp::Update()
{
	// Application update tick

	return true;
}


void MySecondAppApp::Render()
{
	// Application main render loop
}