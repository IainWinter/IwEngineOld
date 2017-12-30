#include "IwEngine\Utility\Logger.h"
#include <stdexcept>

void Utility::Info(const std::string& message) {
	Log("Info", message, ConsoleColorCode::WHITE);
}

void Utility::Debug(const std::string& message) {
	Log("Debug", message, ConsoleColorCode::LIGHT_AGUA);
}

void Utility::Warn(const std::string& message) {
	Log("Warning", message, ConsoleColorCode::LIGHT_YELLOW);
}

void Utility::Error(const std::string& message) {
	Log("Error", message, ConsoleColorCode::LIGHT_RED);
}

void Utility::ThrowRunTimeError(const std::string& message) {
	Log("Exception", message, ConsoleColorCode::LIGHT_RED);
	throw std::runtime_error(message);
}

void Utility::Log(const char* level, const std::string& message, ConsoleColorCode colorCode) {
	Log(level, message, colorCode, ConsoleColorCode::BLACK);
}

void Utility::Log(const char* level, const std::string& message, ConsoleColorCode fg, ConsoleColorCode bg) {
	ConsoleColorModifier mod(fg, bg);
	std::cout << mod << "[" << level << "] " << message.c_str() << std::endl;
}