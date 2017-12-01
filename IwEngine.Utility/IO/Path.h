#pragma once

#ifdef _DLL
#define IWUTILITY_API __declspec(dllexport)
#else
#define IWUTILITY_API __declspec(dllimport)
#endif
#include <string>

namespace IwUtility {
	namespace IO {
		class Path {
		public:
			IWUTILITY_API static bool IsDirectory(std::string path);
			IWUTILITY_API static bool IsDirectory(const char* path);
			IWUTILITY_API static bool IsFile(std::string path);
			IWUTILITY_API static bool IsFile(const char* path);
			IWUTILITY_API static std::string Extension(std::string path);
			IWUTILITY_API static std::string Extension(const char* path);
			IWUTILITY_API static std::string Name(std::string path);
			IWUTILITY_API static std::string Name(const char* path);
		private:
			Path();
		};
	}
}