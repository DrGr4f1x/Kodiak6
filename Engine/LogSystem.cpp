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

#include "FileSystem.h"

#include <iostream>

#include "LogSystem.h"

using namespace std;
using namespace Kodiak;


namespace
{

LogSystem* g_logSystem{ nullptr };

bool outputToFile{ true };
bool outputToConsole{ true };
bool outputToDebug{ true };

} // anonymous namespace


string SeverityToString(Severity level)
{
	using enum Severity;

	switch (level)
	{
	case Fatal:		return "Fatal";	break;
	case Error:		return "Error";	break;
	case Warning:	return "Warning";	break;
	case Debug:		return "Debug";	break;
	case Notice:	return "Notice";	break;
	case Info:		return "Info"; break;
	default:		return "";	break;
	}
}


void Kodiak::PostLogMessage(LogMessage&& message)
{
	auto* logSystem = GetLogSystem();
	if (logSystem)
	{
		logSystem->PostLogMessage(move(message));
	}
}


LogSystem::LogSystem()
	: m_initialized(false)
{
	Initialize();

	assert(g_logSystem == nullptr);
	g_logSystem = this;
}


LogSystem::~LogSystem()
{
	g_logSystem = nullptr;
	Shutdown();
}


void LogSystem::PostLogMessage(LogMessage&& message)
{
	m_messageQueue.push(move(message));
}


void LogSystem::CreateLogFile()
{
	// Get the log directory path
	FileSystem* fs = GetFileSystem();
	fs->EnsureLogDirectory();
	auto logPath = fs->GetLogPath();

	// Build the filename
	namespace chr = std::chrono;
	auto systemTime = chr::system_clock::now();
	auto localTime = chr::zoned_time{ chr::current_zone(), systemTime }.get_local_time();
	string filename = format("Log-{:%Y%m%d%H%M%S}.txt", chr::floor<chr::seconds>(localTime));

	// Build the full path
	auto fullPath = logPath / filename;

	// Open the file stream
	m_file.open(fullPath.c_str(), ios::out | ios::trunc);
	m_file << fixed;

	// Create a hard link to the non-timestamped file
	auto logFilePath = logPath / "Log.txt";
	filesystem::remove(logFilePath);
	try
	{
		filesystem::create_hard_link(fullPath, logFilePath);
	}
	catch (filesystem::filesystem_error e)
	{
		cerr << e.what() << " " << e.path1().string() << " " << e.path2().string() << endl;
	}
}


void LogSystem::Initialize()
{
	lock_guard<mutex> lock(m_initializationMutex);

	// Only initialize if we are in uninitialized state
	if (m_initialized)
	{
		return;
	}

	CreateLogFile();

	m_haltLogging = false;

	m_workerLoop = async(launch::async,
		[&]
		{
			using enum Severity;

			while (!m_haltLogging)
			{
				LogMessage message{};
				if (m_messageQueue.try_pop(message))
				{
					namespace chr = std::chrono;
					const auto systemTime = chr::system_clock::now();
					const auto localTime = chr::zoned_time{ chr::current_zone(), systemTime }.get_local_time();
					const auto localTimeStr = format("[{:%Y.%m.%d-%H.%M.%S}]", chr::floor<chr::milliseconds>(localTime));

					const string categoryStr = message.category ? "" : format("{}: ", message.category.GetName());
					const string severityStr = (message.severity == Severity::Log) ? "" : format("{}: ", SeverityToString(message.severity));

					const string messageStr = format("{} {}{}{}", localTimeStr, categoryStr, severityStr, message.messageStr);


					if (outputToFile)
					{
						m_file.flush();
						m_file << messageStr;
					}

					if (outputToConsole)
					{
						if (message.severity == Fatal || message.severity == Error)
						{
							cerr << messageStr;
						}
						else
						{
							cout << messageStr;
						}
					}

					if (outputToDebug)
					{
						OutputDebugStringA(messageStr.c_str());
					}

					if (message.severity == Fatal)
					{
						m_file.close();
						Utility::ExitFatal(messageStr, "Fatal Error");
					}
				}
			}
		}
	);

	m_initialized = true;
}


void LogSystem::Shutdown()
{
	lock_guard<mutex> lock{ m_initializationMutex };

	// Only shutdown if we are in initialized state
	if (!m_initialized)
	{
		return;
	}

	m_haltLogging = true;
	m_workerLoop.get();

	m_file.flush();
	m_file.close();

	m_initialized = false;
}


Kodiak::LogSystem* Kodiak::GetLogSystem()
{
	return g_logSystem;
}