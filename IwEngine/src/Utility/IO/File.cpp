#include "IwEngine\Utility\IO\File.h"
#include "IwEngine\Utility\Logger.h"
#include <vector>
#include <cstdio>
#include <cerrno>

#define MAX_LINE_LENGTH 1000

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
	errno_t errorCode = fopen_s(&file, filePath, "rt");
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

IWENGINE_API std::string* Utility::IO::ReadFileLines(const char* filePath) {
	std::vector<std::string> lines;
	FILE* file;
	errno_t errorCode = fopen_s(&file, filePath, "rt");
	if (file) {
		int lineCount = 0;
		for (char c = getc(file); c != EOF; c = getc(file)) {
			if (c == '\n') lineCount++;
		}

		rewind(file);
		lines.reserve(lineCount + 1);

		char line[MAX_LINE_LENGTH];
		while (fgets(line, MAX_LINE_LENGTH, file)) {
			char& last = line[strlen(line) - 1];
			if (last == '\n') {
				last = '\0';
			}
			
			lines.push_back(line);
		}
	} else {
		ReportError(errorCode, filePath);
	}

	size_t size = lines.size();
	std::string* aLines = new std::string[size];
	for (size_t i = 0; i < size; i++) {
		aLines[i] = lines[i];
	}

	return aLines;
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