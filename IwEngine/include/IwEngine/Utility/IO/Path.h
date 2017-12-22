#pragma once

#include "IwEngine\Common.h"
#include <string>

namespace Utility {
	namespace IO {
		IWENGINE_API bool IsDirectory(const char* path);
		IWENGINE_API bool IsFile(const char* path);
		IWENGINE_API const char* GetFileExtension(const char* path);
		IWENGINE_API const char* GetFileName(const char* path);
	}
}