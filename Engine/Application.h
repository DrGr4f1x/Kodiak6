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

#include "Graphics\GraphicsDevice.h"

namespace Kodiak
{

// Forward declarations
class FileSystem;
class InputSystem;
class LogSystem;
enum class DigitalInput;
enum class AnalogInput;


struct ApplicationDesc
{
	const std::string name{ "Unnamed" };
	uint32_t width{ 1920 };
	uint32_t height{ 1080 };
	const GraphicsApi api{ GraphicsApi::D3D12 };
};


class Application
{
public:
	Application();
	explicit Application(const ApplicationDesc& desc);
	virtual ~Application();

	void Run();

	// Override these methods in derived classes
	virtual void Configure();
	virtual void Startup() {}
	virtual void Shutdown() {}

	virtual bool Update() { return true; }
	virtual void UpdateUI() {}
	virtual void Render() {}

	// Accessors
	const HINSTANCE GetHINSTANCE() const { return m_hinst; }
	const HWND GetHWND() const { return m_hwnd; }
	uint32_t GetWidth() const { return m_displayWidth; }
	uint32_t GetHeight() const { return m_displayHeight; }

	// Application state
	bool IsPaused() const { return m_isPaused; }
	void Pause() { m_isPaused = true; }
	void Unpause() { m_isPaused = false; }
	void TogglePause() { m_isPaused = !m_isPaused; }
	void Stop() { m_isRunning = false; }

	// Input system state
	bool IsAnyPressed() const;
	bool IsPressed(DigitalInput di) const;
	bool IsFirstPressed(DigitalInput di) const;
	bool IsReleased(DigitalInput di) const;
	bool IsFirstReleased(DigitalInput di) const;
	float GetDurationPressed(DigitalInput di) const;
	float GetAnalogInput(AnalogInput ai) const;
	float GetTimeCorrectedAnalogInput(AnalogInput ai) const;
	void SetCaptureMouse(bool capture);
	bool GetCaptureMouse() const;

	std::string GetWindowTitle() const;

protected:
	const std::string m_name;
	std::string m_appNameWithApi;
	
	uint32_t m_displayWidth{ 1920 };
	uint32_t m_displayHeight{ 1080 };

	const GraphicsApi m_api{ GraphicsApi::D3D12 };

	// Application state
	bool m_isRunning{ false };
	bool m_isPaused{ false };
	bool m_showUI{ false };
	bool m_showGrid{ false };
	float m_frameTimer{ 0.0f };
	float m_appElapsedTime{ 0.0f };
	float m_timer{ 0.0f };
	float m_timerSpeed{ 1.0f };
	uint32_t m_lastFps{ 0 };
	uint32_t m_frameCounter{ 0 };
	std::chrono::time_point<std::chrono::high_resolution_clock> m_appStartTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTimestamp;

	HINSTANCE	m_hinst{};
	HWND		m_hwnd{};

	// Engine systems
	std::unique_ptr<FileSystem> m_filesystem;
	std::unique_ptr<LogSystem> m_logSystem;
	std::unique_ptr<InputSystem> m_inputSystem;
	DeviceHandle m_graphicsDevice;

private:
	void Initialize();
	void Finalize();
	bool Tick();

	void CreateGraphicsDevice();
};


Application* GetApplication();

GraphicsApi GetGraphicsApiFromCommandline(int argc, const char* const* argv);

} // namespace Kodiak