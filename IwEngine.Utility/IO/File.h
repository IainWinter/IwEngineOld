#pragma once

#include <iostream>
#include <fstream>
#include <experimental/filesystem>

class File {
public:
	static void WriteWithMode(const char* filePath, const char** lines, int length, int mode);
	static void WriteWithMode(const std::string& filePath, const std::string* lines, int length, int mode);
	static void WriteWithMode(const char* filePath, const char* text, int mode);
	static void WriteWithMode(const std::string& filePath, const std::string& text, int mode);
	static void AppendAllLines(const char* filePath, const char** lines, int length);
	static void AppendAllLines(const std::string& filePath, const std::string* lines, int length);
	static void AppendText(const char* filePath, const char* text);
	static void AppendText(const std::string& filePath, const std::string& text);
	static void WriteAllLines(const char* filePath, const char** lines, int length);
	static void WriteAllLines(const std::string& filePath, const std::string* lines, int length);
	static void WriteText(const char* filePath, const char* text);
	static void WriteText(const std::string& filePath, const std::string& text);
	static std::ofstream Create(const char* filePath);
	static std::ofstream Create(const std::string& filePath);
	static void Delete(const char* filePath);
	static void Delete(const std::string& filePath);
	static std::ifstream Open(const char* filePath);
	static std::ifstream Open(const std::string& filePath);
	static bool Exists(const char* filePath);
	static bool Exists(const char* filePath, std::error_code& errorCode);

private:
	File();
};