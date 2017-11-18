#ifdef _WIN32 || _WIN64
#include <windows.h>
#endif

#include "Directory.h"

static char** GetFiles(const char* directoryPath) {
	int fileCount = GetFileCount(directoryPath);

	char** fileNames = new char*[fileCount];

	WIN32_FIND_DATA wfd;
	HANDLE handle = FindFirstFile(directoryPath, &wfd);
	if (handle == INVALID_HANDLE_VALUE) {
		throw "Invalid directory path";
	}

	int currentFile = 0;
	do {
		fileCount[currentFile] = wfd.cFileName;
	}
}

static int GetFileCount(const char* dircotryPath) {
	int counter = 0;
	WIN32_FIND_DATA wfd;
	HANDLE handle = FindFirstFile(dircotryPath, &wfd);
	if (handle == INVALID_HANDLE_VALUE) {
		throw "Invalid directory path";
	}

	do {
		counter++;
	} while (FindNextFile(handle, &wfd));

	FindClose(handle);

	return counter;
}