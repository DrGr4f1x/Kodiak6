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

#include "FileSystem.h"
#include "InputSystem.h"

#pragma comment(lib, "runtimeobject.lib")

using namespace Kodiak;
using namespace std;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static Kodiak::Application* g_application = nullptr;


Application::Application()
	: m_name("Unnamed")
{
	m_appNameWithApi = format("[{}] {}", GraphicsApiToString(m_api), m_name);
	g_application = this;
}


Application::Application(const ApplicationDesc& desc)
	: m_name(desc.name)
	, m_displayWidth(desc.width)
	, m_displayHeight(desc.height)
	, m_api(desc.api)
{
	m_appNameWithApi = format("[{}] {}", GraphicsApiToString(m_api), m_name);
	g_application = this;
}


Application::~Application()
{
	g_application = nullptr;
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
	auto filesystem = GetFileSystem();

	filesystem->SetDefaultRootPath();
}


bool Application::IsAnyPressed() const
{
	assert_msg(m_inputSystem, "Input system not initialized.");
	return m_inputSystem->IsAnyPressed();
}


bool Application::IsPressed(DigitalInput di) const
{
	assert_msg(m_inputSystem, "Input system not initialized.");
	return m_inputSystem->IsPressed(di);
}


bool Application::IsFirstPressed(DigitalInput di) const
{
	assert_msg(m_inputSystem, "Input system not initialized.");
	return m_inputSystem->IsFirstPressed(di);
}


bool Application::IsReleased(DigitalInput di) const
{
	assert_msg(m_inputSystem, "Input system not initialized.");
	return m_inputSystem->IsReleased(di);
}


bool Application::IsFirstReleased(DigitalInput di) const
{
	assert_msg(m_inputSystem, "Input system not initialized.");
	return m_inputSystem->IsFirstReleased(di);
}


float Application::GetDurationPressed(DigitalInput di) const
{
	assert_msg(m_inputSystem, "Input system not initialized.");
	return m_inputSystem->GetDurationPressed(di);
}


float Application::GetAnalogInput(AnalogInput ai) const
{
	assert_msg(m_inputSystem, "Input system not initialized.");
	return m_inputSystem->GetAnalogInput(ai);
}


float Application::GetTimeCorrectedAnalogInput(AnalogInput ai) const
{
	assert_msg(m_inputSystem, "Input system not initialized.");
	return m_inputSystem->GetTimeCorrectedAnalogInput(ai);
}


void Application::SetCaptureMouse(bool capture)
{
	assert_msg(m_inputSystem, "Input system not initialized.");
	m_inputSystem->SetCaptureMouse(capture);
}


bool Application::GetCaptureMouse() const
{
	assert_msg(m_inputSystem, "Input system not initialized.");
	return m_inputSystem->GetCaptureMouse();
}


string Application::GetWindowTitle() const
{
	if (m_showUI)
	{
		return format("{}", m_appNameWithApi);
	}
	else
	{
		return format("{} - {} fps", m_appNameWithApi, m_frameCounter);
	}
}


void Application::Initialize()
{
	// Create core engine systems
	m_filesystem = make_unique<FileSystem>(m_name);
	m_filesystem->SetDefaultRootPath();
	m_logSystem = make_unique<LogSystem>();

	// This is the first place we can post a startup message
	LOG_INFO << "App: " << m_name << " starting up";
	LOG_INFO << "  API: " << GraphicsApiToString(m_api) << ENDL;

	m_inputSystem = make_unique<InputSystem>(m_hwnd);

	LOG_INFO << "Engine systems initialized" << ENDL;

	Configure();

	CreateGraphicsDevice();

	Startup();

	m_isRunning = true;
}


void Application::Finalize()
{
	Shutdown();
}


bool Application::Tick()
{
	if (!m_isRunning)
		return false;

	auto timeStart = chrono::high_resolution_clock::now();

	m_inputSystem->Update(m_frameTimer);

	// Close on Escape key
	if (IsFirstPressed(DigitalInput::kKey_escape))
		return false;

	bool res = Update();
	if (res)
	{
		/*m_grid->Update(m_camera);

		Render();

		m_graphicsDevice->SubmitFrame();*/
	}

	++m_frameCounter;

	// Elapsed time for this frame
	auto timeEnd = chrono::high_resolution_clock::now();
	auto timeDiff = chrono::duration<double, std::milli>(timeEnd - timeStart).count();
	m_frameTimer = static_cast<float>(timeDiff) / 1000.0f;

	if (!m_isPaused)
	{
		m_timer += m_timerSpeed * m_frameTimer;
		if (m_timer > 1.0f)
		{
			m_timer -= 1.0f;
		}

		// Global elapsed time since application start
		auto globalTimeDiff = chrono::duration<double, std::milli>(timeEnd - m_appStartTime).count();
		m_appElapsedTime = static_cast<float>(globalTimeDiff) / 1000.0f;
	}

	float fpsTimer = (float)(std::chrono::duration<double, std::milli>(timeEnd - m_lastTimestamp).count());
	if (fpsTimer > 1000.0f)
	{
		m_lastFps = static_cast<uint32_t>((float)m_frameCounter * (1000.0f / fpsTimer));

		std::string windowTitle = GetWindowTitle();
		SetWindowText(m_hwnd, windowTitle.c_str());

		m_frameCounter = 0;
		m_lastTimestamp = timeEnd;
	}

	//PrepareUI();

	return res;
}


void Application::CreateGraphicsDevice()
{
	GraphicsDeviceDesc desc;
	desc.api = m_api;
	desc.appName = m_name;
	desc.hinstance = m_hinst;
	desc.hwnd = m_hwnd;
	desc.width = m_displayWidth;
	desc.height = m_displayHeight;

	m_graphicsDevice = CreateDevice(desc);
}


Kodiak::Application* Kodiak::GetApplication()
{
	return g_application;
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