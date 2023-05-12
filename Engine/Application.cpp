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

#include "Filesystem.h"

#pragma comment(lib, "runtimeobject.lib")

using namespace Kodiak;
using namespace std;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


Application::Application()
	: m_name("Unnamed")
{}


Application::Application(const ApplicationDesc& desc)
	: m_name(desc.name)
	, m_displayWidth(desc.width)
	, m_displayHeight(desc.height)
	, m_api{desc.api}
{}


Application::~Application()
{
	Finalize();
}


void Application::Run()
{
	Microsoft::WRL::Wrappers::RoInitializeWrapper InitializeWinRT(RO_INIT_MULTITHREADED);
	assert_succeeded(InitializeWinRT);

	string appNameWithAPI = GraphicsApiToString(m_api) + " " + m_name;

	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hinst;
	wcex.hIcon = LoadIcon(m_hinst, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = appNameWithAPI.c_str();
	wcex.hIconSm = LoadIcon(m_hinst, IDI_APPLICATION);
	assert_msg(0 != RegisterClassEx(&wcex), "Unable to register a window");

	// Create window
	RECT rc = { 0, 0, (LONG)m_displayWidth, (LONG)m_displayHeight };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	m_hwnd = CreateWindow(appNameWithAPI.c_str(), appNameWithAPI.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, m_hinst, nullptr);

	assert(m_hwnd != 0);

	Initialize();

	ShowWindow(m_hwnd, SW_SHOWDEFAULT);

	m_appStartTime = std::chrono::high_resolution_clock::now();

	do
	{
		MSG msg = {};
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
			break;
	} while (Tick());	// Returns false to quit loop

	Shutdown();
}


void Application::Configure()
{
	// Setup file system
	auto filesystem = GetFilesystem();

	filesystem->SetDefaultRootPath();
}


void Application::Initialize()
{
	// Create engine systems
	m_filesystem = make_unique<Filesystem>(m_name);

	Configure();

	Startup();

	m_isRunning = true;
}


void Application::Finalize()
{
	Shutdown();
}


bool Application::Tick()
{
	return true;
}


GraphicsApi Kodiak::GetGraphicsApiFromCommandline(int argc, const char* const* argv)
{
	for (int i = 1; i < argc; ++i)
	{
		const char* arg = argv[i];

		if (!strcmp(arg, "-d3d12") || !strcmp(arg, "-dx12"))
		{
			return GraphicsApi::D3D12;
		}
		else if (!strcmp(arg, "-vk") || !strcmp(arg, "-vulkan"))
		{
			return GraphicsApi::Vulkan;
		}
	}

	// Default to D3D12
	return GraphicsApi::D3D12;
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	}

	case WM_MOUSEMOVE:
	{
		/*if (g_application)
		{
			g_application->OnMouseMove(LOWORD(lParam), HIWORD(lParam));
		}*/
		break;
	}

	case WM_SIZE:
		//Graphics::Resize((UINT)(UINT64)lParam & 0xFFFF, (UINT)(UINT64)lParam >> 16);
		break;

	case WM_CLOSE:
		//GetApplication()->Stop(); // TODO - Can we detect device removed in Vulkan?  This is hacky...
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}