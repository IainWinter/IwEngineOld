#include "IwEngine\Utility\IO\File.h"
#include <vector>

namespace filesystem = std::experimental::filesystem::v1;
using namespace Utility::IO;

void File::WriteWithMode(const char* filePath, const char** lines, size_t length, int mode) {
	std::ofstream file(filePath, mode);

	try {
		if (!file) {
			throw std::runtime_error("Bad path or permissions");
		}

		for (size_t i = 0; i < length; i++) {

			file << lines[i] << std::endl;
		}
	} catch (std::exception ex) {
		std::cout << ex.what() << std::endl << "Path: " << filePath << std::endl;
	}

	file.close();
}

void File::WriteWithMode(const std::string& filePath, const std::string* lines, size_t length, int mode) {
	std::ofstream file(filePath, mode);
	try {
		if (!file) {
			throw std::runtime_error("Bad path or permissions");
		}

		for (size_t i = 0; i < length; i++) {
			file << lines[i].c_str() << std::endl;
		}
	} catch (std::exception ex) {
		std::cout << ex.what() << std::endl << "Path: " << filePath << std::endl;
	}

	file.close();
}

void File::WriteWithMode(const char* filePath, const char* text, int mode) {
	std::ofstream file(filePath, mode);
	try {
		if (!file) {
			throw std::runtime_error("Bad path or permissions");
		}

		file << text;
	} catch (std::exception ex) {
		std::cout << ex.what() << std::endl << "Path: " << filePath << std::endl;
	}

	file.close();
}

void File::WriteWithMode(const std::string& filePath, const std::string& text, int mode) {
	std::ofstream file(filePath, mode);
	try {
		if (!file) {
			throw std::runtime_error("Bad path or permissions");
		}

		file << text.c_str();
	} catch (std::exception ex) {
		std::cout << ex.what() << std::endl << "Path: " << filePath << std::endl;
	}

	file.close();
}

void File::AppendAllLines(const char* filePath, const char** lines, size_t length) {
	File::WriteWithMode(filePath, lines, length, std::ios_base::app);
}

void File::AppendAllLines(const std::string& filePath, const std::string* lines, size_t length) {
	File::WriteWithMode(filePath, lines, length, std::ios_base::app);
}

void File::AppendText(const char* filePath, const char* text) {
	File::WriteWithMode(filePath, text, std::ios_base::app);
}

void File::AppendText(const std::string& filePath, const std::string& text) {
	File::WriteWithMode(filePath, text, std::ios_base::app);
}

void File::WriteAllLines(const char* filePath, const char** lines, size_t length) {
	File::WriteWithMode(filePath, lines, length, 0);
}

void File::WriteAllLines(const std::string& filePath, const std::string* lines, size_t length) {
	File::WriteWithMode(filePath, lines, length, 0);
}

void File::WriteText(const char* filePath, const char* text) {
	File::WriteWithMode(filePath, text, 0);
}

void File::WriteText(const std::string& filePath, const std::string& text) {
	File::WriteWithMode(filePath, text, 0);
}

std::ofstream File::Create(const char* filePath) {
	return std::ofstream(filePath);
}

std::ofstream File::Create(const std::string& filePath) {
	return File::Create(filePath.c_str());
}

void File::Delete(const char* filePath) {
	remove(filePath);
}

void File::Delete(const std::string& filePath) {
	File::Delete(filePath.c_str());
}

std::ifstream File::Open(const char* filePath) {
	return std::ifstream(filePath);
}

std::ifstream File::Open(const std::string& filePath) {
	return File::Open(filePath.c_str());
}

std::string* File::ReadAllLines(const char* filePath) {
	std::ifstream file = File::Open(filePath);
	std::vector<std::string> lines;
	try {
		if (!file) {
			throw std::runtime_error("Bad path or premissions");
		}

		lines = std::vector<std::string>();

		std::string line;
		while (file >> line) {
			lines.push_back(std::string(line).c_str());
		}
	} catch (std::exception ex) {
		std::cout << ex.what() << std::endl << "Path: " << filePath << std::endl;

	}

	return &lines[0];
}

std::string* File::ReadAllLines(const std::string & filePath) {
	return File::ReadAllLines(filePath.c_str());
}

bool File::Exists(const char* filePath) {
	std::error_code errorCode;
	return File::Exists(filePath, errorCode);
}

bool File::Exists(const char* filePath, std::error_code& errorCode) {
	return filesystem::is_regular_file(filePath, errorCode);
}

uintmax_t File::GetSize(const char * filePath) {
	return filesystem::file_size(filePath);
}

uintmax_t File::GetSize(const std::string & filePath) {
	return File::GetSize(filePath.c_str());
}