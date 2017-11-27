#pragma once
#include <cstddef>
#include <system_error>
#include <experimental/filesystem>

class Directory {
public:
	static std::string* GetFiles(const char* directoryPath);
	static std::string* GetFiles(const char* directoryPath, std::error_code& errorCode);
	static std::string* GetFiles(const char* directoryPath, size_t& fileCount);
	static std::string* GetFiles(const char* directoryPath, std::error_code& errorCode, size_t& fileCount);
	static size_t GetFileCount(const char* directoryPath);
	static size_t GetFileCount(const char* directoryPath, std::error_code& errorCode);
	static bool Exists(const char* directoryPath);
	static bool Exists(const char* directoryPath, std::error_code& errorCode);
private:
	Directory();
};