#pragma once

#include "IwEngine\Common.h"
#include <string>
#include <vector>

namespace Utility {
	namespace IO {
		IWENGINE_API std::string ReadFile(const char* filePath);
		IWENGINE_API std::vector<std::string> ReadFileLines(const char* filePath);
		IWENGINE_API bool FileExists(const char* filePath);
		IWENGINE_API uintmax_t GetFileSize(const char* filePath);
	} 
}