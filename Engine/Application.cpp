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

#include "Application.h"


using namespace Kodiak;
using namespace std;


Application::Application()
	: m_name("Unnamed")
{}


Application::Application(const string& name)
	: m_name(name)
{}


Application::Application(const string& name, uint32_t displayWidth, uint32_t displayHeight)
	: m_name(name)
	, m_displayWidth(displayWidth)
	, m_displayHeight(displayHeight)
{}


Application::~Application()
{
	Finalize();
}


void Application::Run()
{

}


void Application::Configure()
{

}


void Application::Initialize()
{

}


void Application::Finalize()
{

}


bool Application::Tick()
{
	return true;
}