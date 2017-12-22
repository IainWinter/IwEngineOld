#pragma once

#include "IwEngine\Common.h"
#include <cstddef>
#include <system_error>
#include <experimental/filesystem>

namespace Utility {
	namespace IO {
		IWENGINE_API std::string* GetFiles(const char* directoryPath, bool recurse);
		IWENGINE_API std::string* GetFiles(const char* directoryPath, bool recurse, size_t& fileCount);
		IWENGINE_API size_t GetFileCount(const char* directoryPath, bool recurse);
		IWENGINE_API bool Exists(const char* directoryPath);
	}
}