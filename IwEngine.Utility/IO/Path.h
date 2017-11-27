#pragma once
#include <string>

class Path {
public:
	static bool IsDirectory(std::string path);
	static bool IsDirectory(const char* path);
	static bool IsFile(std::string path);
	static bool IsFile(const char* path);
	static std::string Extension(std::string path);
	static std::string Extension(const char* path);
	static std::string Name(std::string path);
	static std::string Name(const char* path);
private:
	Path();
};