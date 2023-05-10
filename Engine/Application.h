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

class Application
{
public:
	Application();
	Application(const std::string& name);
	Application(const std::string& name, uint32_t displayWidth, uint32_t displayHeight);
	virtual ~Application();

	void Run();

	// Override these methods in derived classes
	virtual void Configure();
	virtual void Startup() {}
	virtual void Shutdown() {}

	virtual bool Update() { return true; }
	virtual void UpdateUI() {}
	virtual void Render() {}

protected:
	const std::string m_name;

	uint32_t m_displayWidth{ 1920 };
	uint32_t m_displayHeight{ 1080 };

private:
	void Initialize();
	void Finalize();
	bool Tick();
};

} // namespace Kodiak