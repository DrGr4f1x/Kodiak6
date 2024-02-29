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


namespace Kodiak
{

// Forward declarations
class FileSystem;
class InputSystem;
class LogSystem;


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

protected:
	const std::string m_name;
	
	uint32_t m_displayWidth{ 1920 };
	uint32_t m_displayHeight{ 1080 };

	const GraphicsApi m_api{ GraphicsApi::D3D12 };

	// Application state
	bool m_isRunning{ false };
	bool m_isPaused{ false };
	std::chrono::time_point<std::chrono::high_resolution_clock> m_appStartTime;

	HINSTANCE	m_hinst{ 0 };
	HWND		m_hwnd{ 0 };

	// Engine systems
	std::unique_ptr<FileSystem> m_filesystem;
	std::unique_ptr<LogSystem> m_logSystem;
	std::unique_ptr<InputSystem> m_inputSystem;

private:
	void Initialize();
	void Finalize();
	bool Tick();
};


Application* GetApplication();

GraphicsApi GetGraphicsApiFromCommandline(int argc, const char* const* argv);

} // namespace Kodiak