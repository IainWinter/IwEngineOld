#pragma once
#include <cstddef>
#include <system_error>
#include <experimental/filesystem>

class Directory {
public:
	static std::string* GetFiles(const char* directoryPath);
	static std::string* GetFiles(const char* directoryPath, std::error_code& errorCode);
	static std::size_t GetFileCount(const char* directoryPath);
	static std::size_t GetFileCount(const char* directoryPath, std::error_code& errorCode);
	static bool Exists(const char* directoryPath);
	static bool Exists(const char* directoryPath, std::error_code& errorCode);

private:
	Directory();
};