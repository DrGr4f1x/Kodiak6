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
#include "Graphics\DeviceManager.h"
#include "External\CLI11\CLI\CLI.hpp"


#pragma comment(lib, "runtimeobject.lib")


using namespace Kodiak;
using namespace std;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static Kodiak::Application* g_application = nullptr;


Application::Application()
{
	m_appNameWithApi = format("[{}] {}", GraphicsApiToString(m_appDesc.api), m_appDesc.name);
	g_application = this;
}


Application::Application(const std::string& appName)
{
	m_appDesc.name = appName;
	m_appNameWithApi = format("[{}] {}", GraphicsApiToString(m_appDesc.api), m_appDesc.name);
	g_application = this;
}


Application::~Application()
{
	g_application = nullptr;
	Finalize();
}


int Application::Run(int argc, char* argv[])
{
	int res = ProcessCommandLine(argc, argv);
	if (res != 0)
	{
		return res;
	}

	Microsoft::WRL::Wrappers::RoInitializeWrapper InitializeWinRT(RO_INIT_MULTITHREADED);
	assert_succeeded(InitializeWinRT);

	m_appNameWithApi = format("[{}] {}", GraphicsApiToString(m_appDesc.api), m_appDesc.name);

	// Register class
	WNDCLASSEX wcex{};
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
	wcex.lpszClassName = m_appNameWithApi.c_str();
	wcex.hIconSm = LoadIcon(m_hinst, IDI_APPLICATION);
	assert_msg(0 != RegisterClassEx(&wcex), "Unable to register a window");

	// Create window
	RECT rc = { 0, 0, (LONG)m_appDesc.width, (LONG)m_appDesc.height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	m_hwnd = CreateWindow(m_appNameWithApi.c_str(), m_appNameWithApi.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, m_hinst, nullptr);

	assert(m_hwnd != 0);

	Initialize();

	ShowWindow(m_hwnd, SW_SHOWDEFAULT);

	m_appStartTime = std::chrono::high_resolution_clock::now();

	do
	{
		MSG msg{};
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
			break;
	} while (Tick());	// Returns false to quit loop

	Shutdown();

	return 0;
}


int Application::ProcessCommandLine(int argc, char* argv[])
{
	CLI::App app{ "Kodiak App", m_appDesc.name };
	argv = app.ensure_utf8(argv);

	// Graphic API selection
	bool bDX12{ false };
	bool bVulkan{ false };
	auto dxOpt = app.add_flag("--dx,--dx12,--d3d12", bDX12, "Select DirectX renderer");
	auto vkOpt = app.add_flag("--vk,--vulkan", bVulkan, "Select Vulkan renderer");
	dxOpt->excludes(vkOpt);
	vkOpt->excludes(dxOpt);

	// Width, height
	auto widthOpt = app.add_option("--resx,--width", m_appDesc.width, "Sets initial window width");
	auto heightOpt = app.add_option("--resy,--height", m_appDesc.height, "Sets initial window height");
	
	// Parse command line
	CLI11_PARSE(app, argc, argv);

	// Set application parameters from command line
	m_appDesc.api = bVulkan ? GraphicsApi::Vulkan : GraphicsApi::D3D12;
	m_appNameWithApi = format("[{}] {}", GraphicsApiToString(m_appDesc.api), m_appDesc.name);

	return 0;
}


void Application::Configure()
{
	// Setup file system
	auto filesystem = GetFileSystem();

	filesystem->SetDefaultRootPath();
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
	m_filesystem = make_unique<FileSystem>(m_appDesc.name);
	m_filesystem->SetDefaultRootPath();
	m_logSystem = make_unique<LogSystem>();

	// This is the first place we can post a startup message
	LogInfo(LogApplication) << "App: " << m_appDesc.name << " starting up" << endl;
	LogInfo(LogApplication) << "  API: " << GraphicsApiToString(m_appDesc.api) << endl;
	LogInfo(LogApplication) << endl;

	m_inputSystem = make_unique<InputSystem>(m_hwnd);

	LogInfo << "LogInfo test" << endl;
	LogInfo(LogApplication) << "Engine systems initialized" << endl;
	LogInfo(LogApplication) << endl;

	Configure();

	CreateDeviceManager();

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
	if (m_inputSystem->IsFirstPressed(DigitalInput::kKey_escape))
		return false;

	bool res = Update();
	if (res)
	{
		//m_grid->Update(m_camera);

		m_deviceManager->BeginFrame();

		Render();

		m_deviceManager->Present();
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


void Application::CreateDeviceManager()
{
	m_deviceManager.reset(DeviceManager::Create(m_appDesc.api));

	auto deviceDesc = DeviceDesc{}
		.SetAppName(m_appDesc.name)
		.SetEnableDebugRuntime(m_appDesc.useDebugLayer)
		.SetBackBufferWidth(m_appDesc.width)
		.SetBackBufferHeight(m_appDesc.height)
		.SetHwnd(m_hwnd);

	if (!m_deviceManager->CreateDeviceAndSwapChain(deviceDesc))
	{
		LogFatal(LogApplication) << "Failed to create graphics device and swap chain" << endl;
	}
}


Kodiak::Application* Kodiak::GetApplication()
{
	return g_application;
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