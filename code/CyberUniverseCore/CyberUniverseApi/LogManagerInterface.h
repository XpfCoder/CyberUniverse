#pragma once
#include <string>
//#include ".\DeepWorldCore\Log\LogCategory.h"
//#include "DeepEyeExt/Log/LogCategory.h"


class ILogInterface;

// PRIO_DEFAULT = -1,		//自动推断，会根据Category默认值。如果这个也是，那就跟据系统默认
// PRIO_ALWAYS = 0,		//总是打印
// PRIO_EMERG = 100,	//紧急
// PRIO_FATAL = 200,	//致命
// PRIO_CRITICAL = 300,	//关键
// PRIO_ERROR = 400,	//错误
// PRIO_WARNING = 500,	//警告
// PRIO_NOTICE = 600,	//注意，用于轻微异常，尤其是预期会经常出现的异常
// PRIO_INFO = 700,	//信息
// PRIO_DEBUG = 800,	//调试1
// PRIO_DEBUG_2 = 900,	//调试2
// PRIO_DEBUG_3 = 1000,	//调试3
// PRIO_DEBUG_4 = 1100,	//调试4

namespace Resafety {
	namespace CyberUniverseStudio {
		enum class LoggingLevel
		{
			Start = -1,
			Errors,			//!< Only actual error conditions will be logged.
			Warnings,       //!< Warnings will be logged as well.
			Standard,		//!< Basic events will be logged (default level).
			Informative,	//!< Useful tracing (object creations etc) information will be logged.
			Insane,			//!< Mostly everything gets logged (use for heavy tracing only, log WILL be big).
			End,
		};

		//class ILogManager
		//{
		//public:
		//	virtual void setLoggingLevel(LoggingLevel level) = 0;
		//	virtual bool init(const std::string& logDir, const std::string& logFileName) = 0;
		//public:
		//	virtual void logStandard(const char* format, ...) = 0;
		//	virtual void logError(const char* format, ...) = 0;
		//	virtual void logWarning(const char* format, ...) = 0;
		//};

		//DEEPWORLD_API ILogManager* GetLogManager();
		__declspec(dllexport) ILogInterface* GetLogManager();
		__declspec(dllexport) int GetLogPriority(LoggingLevel logLevel);


	}
}
