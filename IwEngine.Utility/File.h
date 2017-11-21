#pragma once

#include <iostream>

class File {
public:
	static void AppendAllLines(const char* filePath, const char** lines);
	static void AppendAllLines(const std::string filePath, const std::string* lines);
	static void AppendAllText(const char* filePath, const char** lines);
	static void AppendAllText(const std::string filePath, const std::string* lines);
	static void WriteAllLines(const char* filePath, const char** lines);
	static void WriteAllLines(const std::string filePath, const std::string* lines);
	static void WriteAllText(const char* filePath, const char** lines);
	static void WriteAllText(const std::string filePath, const std::string* lines);
	static std::iostream Create(const char* filePath);
	static std::iostream Create(const std::string* filePath);
	static void Delete(const char* filePath);
	static void Delete(const std::string* filePath);
private:
	File();
};

