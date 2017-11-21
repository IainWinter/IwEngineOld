#include "Path.h"
#include <experimental/filesystem>

namespace filesystem = std::experimental::filesystem::v1;

bool Path::IsDirectory(std::string path) {
	return Path::IsDirectory(path.c_str());
}

bool Path::IsDirectory(const char* path) {
	return filesystem::is_directory(path);
}

bool Path::IsFile(std::string path) {
	return Path::IsFile(path.c_str());
}

bool Path::IsFile(const char* path) {
	return filesystem::is_regular_file(path);
}

std::string Path::Extension(std::string path) {
	return Path::Extension(path.c_str());
}

std::string Path::Extension(const char* path) {
	filesystem::path p = path;
	return p.extension().string();
}

std::string Path::Name(std::string path) {
	return Path::Name(path.c_str());
}

std::string Path::Name(const char * path) {
	filesystem::path p = path;
	return p.filename().string();
}