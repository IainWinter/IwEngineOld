#pragma once

#include "IwEngine\Common.h"
#include "Color.h"
#include <string>

namespace Utility {
	IWENGINE_API void Info(const std::string& message);
	IWENGINE_API void Debug(const std::string& message);
	IWENGINE_API void Warn(const std::string& message);
	IWENGINE_API void Error(const std::string& message);
	IWENGINE_API void ThrowRunTimeError(const std::string& message);
	IWENGINE_API void Log(const char* level, const std::string& message, ConsoleColorCode colorCode);
	IWENGINE_API void Log(const char* level, const std::string& message, ConsoleColorCode fg, ConsoleColorCode bg);
}