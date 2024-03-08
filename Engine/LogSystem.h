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

enum class LogSeverity
{
	Fatal,
	Error,
	Warning,
	Notice,
	Info,
	Debug,
	Log
};


struct LogMessage
{
	std::string messageStr;
	LogSeverity level;
};

std::string LogSeverityToString(LogSeverity level);
void PostLogMessage(LogMessage&& message);


class LogSystem : NonCopyable, NonMovable
{
public:
	LogSystem();
	~LogSystem();

	bool IsInitialized() const { return m_initialized; }

	void PostLogMessage(LogMessage&& message);

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


template <LogSeverity TLevel>
class Logger
{
public:
	Logger()
	{
		namespace chr = std::chrono;
		auto tpSys = chr::system_clock::now();
		auto tpLoc = chr::zoned_time{ chr::current_zone(), tpSys }.get_local_time();
		
		m_stream << format("[{}]", chr::floor<chr::milliseconds>(tpLoc)) << " " << LogSeverityToString(TLevel) << " ";
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
#define LOG_FATAL Logger<LogSeverity::Fatal>().MessageStream()
#define LOG_ERROR Logger<LogSeverity::Error>().MessageStream()
#define LOG_WARNING Logger<LogSeverity::Warning>().MessageStream()
#define LOG_NOTICE Logger<LogSeverity::Notice>().MessageStream()
#define LOG_INFO Logger<LogSeverity::Info>().MessageStream()
#define LOG_DEBUG Logger<LogSeverity::Debug>().MessageStream()

} // namespace Kodiak