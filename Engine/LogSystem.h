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

enum class Severity
{
	Fatal,
	Error,
	Warning,
	Notice,
	Info,
	Debug,
	None
};


class LogCategory
{
public:
	LogCategory() = default;
	explicit LogCategory(const std::string& name) : m_name{ name } {}

	constexpr operator bool() { return m_name.empty(); }

	const std::string& GetName() const
	{
		return m_name;
	}

private:
	std::string m_name;
};


struct LogMessage
{
	std::string messageStr;
	Severity severity;
	LogCategory category;
};

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


class BaseLog
{
public:
	BaseLog() = default;
	BaseLog(Severity severity, LogCategory category) 
		: m_severity{ severity }
		, m_category{ category }
	{}
	~BaseLog()
	{
		m_stream.flush();

		PostLogMessage({ m_stream.str(), m_severity, m_category });
	}

	std::ostringstream& MessageStream() { return m_stream; }


private:
	std::ostringstream m_stream;
	Severity m_severity{ Severity::Info };
	LogCategory m_category;
};

LogSystem* GetLogSystem();


#define Log(CAT) BaseLog(Severity::None, CAT).MessageStream()
#define LogFatal(CAT) BaseLog(Severity::Fatal, CAT).MessageStream()
#define LogError(CAT) BaseLog(Severity::Error, CAT).MessageStream()
#define LogWarning(CAT) BaseLog(Severity::Warning, CAT).MessageStream()
#define LogNotice(CAT) BaseLog(Severity::Notice, CAT).MessageStream()
#define LogInfo(CAT) BaseLog(Severity::Info, CAT).MessageStream()
#define LogDebug(CAT) BaseLog(Severity::Debug, CAT).MessageStream()

} // namespace Kodiak