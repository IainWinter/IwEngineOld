#pragma once

#ifdef _DLL
#define IWENGINE_API __declspec(dllexport)
#else
#define IWENGINE_API __declspec(dllimport)
#endif

#include <string>

namespace Utility {
	namespace IO {
		class Path {
		public:
			IWENGINE_API static bool IsDirectory(std::string path);
			IWENGINE_API static bool IsDirectory(const char* path);
			IWENGINE_API static bool IsFile(std::string path);
			IWENGINE_API static bool IsFile(const char* path);
			IWENGINE_API static std::string Extension(std::string path);
			IWENGINE_API static std::string Extension(const char* path);
			IWENGINE_API static std::string Name(std::string path);
			IWENGINE_API static std::string Name(const char* path);
		private:
			Path();
		};
	}
}