#pragma once

#ifdef _DLL
#define IWUTILITY_API __declspec(dllexport)
#else
#define IWUTILITY_API __declspec(dllimport)
#endif

#include <iostream>
#include <fstream>
#include <experimental/filesystem>

namespace Utility {
	namespace IO {
		class File {
		public:
			IWUTILITY_API static void WriteWithMode(const char* filePath, const char** lines, size_t length, int mode);
			IWUTILITY_API static void WriteWithMode(const std::string& filePath, const std::string* lines, size_t length, int mode);
			IWUTILITY_API static void WriteWithMode(const char* filePath, const char* text, int mode);
			IWUTILITY_API static void WriteWithMode(const std::string& filePath, const std::string& text, int mode);
			IWUTILITY_API static void AppendAllLines(const char* filePath, const char** lines, size_t length);
			IWUTILITY_API static void AppendAllLines(const std::string& filePath, const std::string* lines, size_t length);
			IWUTILITY_API static void AppendText(const char* filePath, const char* text);
			IWUTILITY_API static void AppendText(const std::string& filePath, const std::string& text);
			IWUTILITY_API static void WriteAllLines(const char* filePath, const char** lines, size_t length);
			IWUTILITY_API static void WriteAllLines(const std::string& filePath, const std::string* lines, size_t length);
			IWUTILITY_API static void WriteText(const char* filePath, const char* text);
			IWUTILITY_API static void WriteText(const std::string& filePath, const std::string& text);
			IWUTILITY_API static std::ofstream Create(const char* filePath);
			IWUTILITY_API static std::ofstream Create(const std::string& filePath);
			IWUTILITY_API static void Delete(const char* filePath);
			IWUTILITY_API static void Delete(const std::string& filePath);
			IWUTILITY_API static std::ifstream Open(const char* filePath);
			IWUTILITY_API static std::ifstream Open(const std::string& filePath);
			IWUTILITY_API static std::string* ReadAllLines(const char* filePath);
			IWUTILITY_API static std::string* ReadAllLines(const std::string& filePath);
			IWUTILITY_API static bool Exists(const char* filePath);
			IWUTILITY_API static bool Exists(const char* filePath, std::error_code& errorCode);
			IWUTILITY_API static uintmax_t GetSize(const char* filePath);
			IWUTILITY_API static uintmax_t GetSize(const std::string& filePath);
		private:
			File();
		};
	}
}