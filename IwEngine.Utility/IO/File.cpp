#include "File.h"

namespace filesystem = std::experimental::filesystem::v1;

void File::WriteWithMode(const char* filePath, const char** lines, int length, int mode) {
	std::ofstream file(filePath, mode);

	for (size_t i = 0; i < length; i++) {
		file << lines[i] << std::endl;
	}

	file.close();
}

void File::WriteWithMode(const std::string& filePath, const std::string* lines, int length, int mode) {
	std::ofstream file(filePath, mode);

	for (size_t i = 0; i < length; i++) {
		file << lines[i].c_str() << std::endl;
	}

	file.close();
}

void File::WriteWithMode(const char* filePath, const char* text, int mode) {
	std::ofstream file(filePath, mode);
	file << text;
}

void File::WriteWithMode(const std::string & filePath, const std::string & text, int mode) {
	std::ofstream file(filePath, mode);
	file << text.c_str();
}

void File::AppendAllLines(const char* filePath, const char** lines, int length) {
	File::WriteWithMode(filePath, lines, length, std::ios_base::app);
}

void File::AppendAllLines(const std::string& filePath, const std::string* lines, int length) {
	File::WriteWithMode(filePath, lines, length, std::ios_base::app);
}

void File::AppendAllText(const char* filePath, const char* text) {
	File::WriteWithMode(filePath, text, 0);
}

void File::AppendAllText(const std::string& filePath, const std::string& text) {
	File::WriteWithMode(filePath, text, 0);
}

void File::WriteAllLines(const char* filePath, const char** lines, int length) {
	File::WriteWithMode(filePath, lines, length, 0);
}

void File::WriteAllLines(const std::string & filePath, const std::string * lines, int length) {
	File::WriteWithMode(filePath, lines, length, 0);
}

void File::WriteAllText(const char* filePath, const char* text) {
	File::WriteWithMode(filePath, text, 0);
}

void File::WriteAllText(const std::string & filePath, const std::string & text) {
	File::WriteWithMode(filePath, text, 0);
}

std::ofstream File::Create(const char* filePath) {
	return std::ofstream(filePath);
}

std::ofstream File::Create(const std::string & filePath) {
	return File::Create(filePath.c_str());
}

void File::Delete(const char* filePath) {
	remove(filePath);
}

void File::Delete(const std::string & filePath) {
	File::Delete(filePath.c_str());
}

std::ifstream File::Open(const char* filePath) {
	return std::ifstream(filePath);
}

std::ifstream File::Open(const std::string & filePath) {
	return std::ifstream(filePath);
}

bool File::Exists(const char* filePath) {
	std::error_code errorCode;
	return File::Exists(filePath, errorCode);
}

bool File::Exists(const char* filePath, std::error_code& errorCode) {
	return filesystem::is_regular_file(filePath, errorCode);
}