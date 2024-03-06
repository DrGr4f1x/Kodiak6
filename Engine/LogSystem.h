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

#include <concurrent_queue.h>

namespace Kodiak
{

enum class LogLevel
{
	Fatal,
	Error,
	Warning,
	Notice,
	Info,
	Debug
};


struct LogMessage
{
	std::string messageStr;
	LogLevel level;
};

std::string LogLevelToString(LogLevel level);
void PostLogMessage(const LogMessage&& message);


class LogSystem : NonCopyable, NonMovable
{
public:
	LogSystem();
	~LogSystem();

	bool IsInitialized() const { return m_initialized; }

	void PostLogMessage(const LogMessage&& message);

private:
	void CreateLogFile();
	void Initialize();
	void Shutdown();

private:
	std::mutex m_initializationMutex;
	std::mutex m_outputMutex;
	std::ofstream m_file;
	Concurrency::concurrent_queue<LogMessage> m_messageQueue;
	std::atomic<bool> m_haltLogging;
	std::future<void> m_workerLoop;
	std::atomic<bool> m_initialized;
};


template <LogLevel TLevel>
class Logger
{
public:
	Logger()
	{
		m_stream << LogLevelToString(TLevel) << ": ";
	}

	~Logger()
	{
		m_stream << std::endl;

		PostLogMessage({ m_stream.str(), TLevel });
	}

	std::ostringstream& MessageStream() { return m_stream; }

private:
	std::ostringstream m_stream;
};

LogSystem* GetLogSystem();


#define LOG(level) Logger<level>().MessageStream()
#define LOG_FATAL Logger<LogLevel::Fatal>().MessageStream()
#define LOG_ERROR Logger<LogLevel::Error>().MessageStream()
#define LOG_WARNING Logger<LogLevel::Warning>().MessageStream()
#define LOG_NOTICE Logger<LogLevel::Notice>().MessageStream()
#define LOG_INFO Logger<LogLevel::Info>().MessageStream()
#define LOG_DEBUG Logger<LogLevel::Debug>().MessageStream()

#define ENDL std::endl 

} // namespace Kodiak