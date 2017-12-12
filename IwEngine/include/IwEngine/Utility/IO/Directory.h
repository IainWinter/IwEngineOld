#pragma once

#ifdef IWENGINE_EXPORTS
#define IWENGINE_API __declspec(dllexport)
#else
#define IWENGINE_API __declspec(dllimport)
#endif

#include <cstddef>
#include <system_error>
#include <experimental/filesystem>

namespace Utility {
	namespace IO {
		class Directory {
		public:
			IWENGINE_API static std::string* GetFiles(const char* directoryPath, bool recurse);
			IWENGINE_API static std::string* GetFiles(const char* directoryPath, bool recurse, size_t& fileCount);
			IWENGINE_API static size_t GetFileCount(const char* directoryPath, bool recurse);
			IWENGINE_API static bool Exists(const char* directoryPath);
		private:
			Directory();
		};
	}
}