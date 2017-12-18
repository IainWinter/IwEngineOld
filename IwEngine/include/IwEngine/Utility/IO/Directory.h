#pragma once

#include "IwEngine\Common.h"

#include <cstddef>
#include <system_error>
#include <experimental/filesystem>

namespace Utility {
	namespace IO {
		class IWENGINE_API Directory {
		public:
			static std::string* GetFiles(const char* directoryPath, bool recurse);
			static std::string* GetFiles(const char* directoryPath, bool recurse, size_t& fileCount);
			static size_t GetFileCount(const char* directoryPath, bool recurse);
			static bool Exists(const char* directoryPath);
		private:
			Directory();
		};
	}
}