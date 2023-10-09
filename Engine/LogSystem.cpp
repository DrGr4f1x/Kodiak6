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

LogSystem* g_logSystem = nullptr;

} // anonymous namespace


string Kodiak::LogLevelToString(LogLevel level)
{
	switch (level)
	{
	case LogLevel::Error:	return string("  Error");	break;
	case LogLevel::Warning:	return string("Warning");	break;
	case LogLevel::Debug:	return string("  Debug");	break;
	case LogLevel::Notice:	return string(" Notice");	break;
	default:				return string("   Info");	break;
	}
}


void Kodiak::PostLogMessage(const LogMessage& message)
{
	auto* logSystem = GetLogSystem();
	if (logSystem)
	{
		logSystem->PostLogMessage(message);
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


void LogSystem::PostLogMessage(const LogMessage& message)
{
	m_messageQueue.push(message);
}


void LogSystem::CreateLogFile()
{
	// Get the log directory path
	FileSystem* fs = GetFileSystem();
	fs->EnsureLogDirectory();
	auto logPath = fs->GetLogPath();

	// Build the filename
	SYSTEMTIME dateTime;
	GetLocalTime(&dateTime);

	// Append current date+time and extension to filename
	ostringstream sstream;
	sstream << "Log-";
	sstream << dateTime.wYear << dateTime.wMonth << dateTime.wDay;
	sstream << dateTime.wHour << dateTime.wMinute << dateTime.wSecond;
	sstream << ".txt";

	// Build the full path
	auto fullPath = logPath / sstream.str();

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
			while (!m_haltLogging)
			{
				LogMessage message;
				if (m_messageQueue.try_pop(message))
				{
					m_file << message;
				}
			}
		}
	);

	m_initialized = true;
}


void LogSystem::Shutdown()
{
	lock_guard<mutex> lock(m_initializationMutex);

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