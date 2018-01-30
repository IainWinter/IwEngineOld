#include "IwEngine\Utility\IO\Path.h"
#include <experimental\filesystem>

namespace filesystem = std::experimental::filesystem::v1;

IWENGINE_API bool Utility::IO::IsDirectory(const char * path) {
	return filesystem::is_directory(path);
}

IWENGINE_API bool Utility::IO::IsFile(const char * path) {
	return filesystem::is_regular_file(path);
}

IWENGINE_API const char* Utility::IO::GetFileExtension(const char* path) {
	filesystem::path p = path;
	return p.extension().string().c_str();
}

IWENGINE_API const char* Utility::IO::GetFileName(const char* path) {
	filesystem::path p = path;
	return p.filename().string().c_str();
}
