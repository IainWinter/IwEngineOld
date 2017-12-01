#pragma once

#ifdef _DLL
#define IWUTILITY_API __declspec(dllexport)
#else
#define IWUTILITY_API __declspec(dllimport)
#endif

#include <cstddef>
#include <system_error>
#include <experimental/filesystem>

namespace IwUtility {
	namespace IO {
		class Directory {
		public:
			IWUTILITY_API static std::string* GetFiles(const char* directoryPath, bool recurse);
			IWUTILITY_API static std::string* GetFiles(const char* directoryPath, bool recurse, size_t& fileCount);
			IWUTILITY_API static size_t GetFileCount(const char* directoryPath, bool recurse);
			IWUTILITY_API static bool Exists(const char* directoryPath);
		private:
			Directory();
		};
	}
}