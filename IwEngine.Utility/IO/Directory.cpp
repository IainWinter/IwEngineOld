#include "Directory.h"

namespace filesystem = std::experimental::filesystem::v1;

std::string* Directory::GetFiles(const char* directoryPath) {
	std::error_code errorCode;
	return Directory::GetFiles(directoryPath, errorCode);
}

std::string* Directory::GetFiles(const char* directoryPath, std::error_code& errorCode) {
	typedef filesystem::directory_iterator DirItr;
	typedef filesystem::path Path;

	DirItr itr = DirItr(directoryPath, errorCode);
	std::string* files = nullptr;

	if (!errorCode) {
		std::size_t fileCount = Directory::GetFileCount(directoryPath);
		files = new std::string[fileCount];
		for (std::size_t i = 0; i < fileCount; i++) {
			files[i] = itr->path().string();
			itr++;
		}
	}

	return files;
}

std::size_t Directory::GetFileCount(const char* directoryPath) {
	std::error_code errorCode;
	return Directory::GetFileCount(directoryPath, errorCode);
}

std::size_t Directory::GetFileCount(const char* directoryPath, std::error_code& errorCode) {
	typedef filesystem::directory_iterator DirIttr;
	return std::distance(DirIttr(directoryPath, errorCode), DirIttr());
}

bool Directory::Exists(const char* directoryPath) {
	std::error_code errorCode;
	return Directory::Exists(directoryPath, errorCode);
}

bool Directory::Exists(const char* directoryPath, std::error_code& errorCode) {
	return filesystem::is_directory(directoryPath, errorCode);
}