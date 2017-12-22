#include "IwEngine\Utility\IO\File.h"
#include "IwEngine\Utility\Logger.h"
#include <vector>
#include <cstdio>
#include <cerrno>


static void ReportError(int errerno, const std::string& addInfo) {
	std::string error; 

	error.resize(256);

	strerror_s(&error[0], 100, errerno);

	int i = error.find('\0');
	error = error.substr(0, i);

	error.append(" (");
	error.append(std::to_string(errerno));
	error.append("): ");
	error.append(addInfo);
	Utility::Error(error);
}

IWENGINE_API std::string Utility::IO::ReadFile(const char* filePath) {
	std::string contents;
	FILE* file;
	errno_t errorCode = fopen_s(&file, filePath, "rb");
	if (file) {
		fseek(file, 0, SEEK_END);
		contents.resize(ftell(file));
		rewind(file);
		fread(&contents[0], 1, contents.size(), file);
		fclose(file);
	} else {
		ReportError(errorCode, filePath);
	}

	return contents;
}

IWENGINE_API bool Utility::IO::FileExists(const char* filePath) {
	FILE* file;
	fopen_s(&file, filePath, "rb");
	if (file) {
		fclose(file);
	}

	return file;
}

IWENGINE_API uintmax_t Utility::IO::GetFileSize(const char* filePath) {
	uintmax_t bytes;
	FILE* file;
	errno_t errorCode = fopen_s(&file, filePath, "rb");
	if (file) {
		fseek(file, 0, SEEK_END);
		bytes = ftell(file);
		fclose(file);
	} else {
		ReportError(errorCode, filePath);
	}

	return bytes;
}