#pragma once

class Directory {
public:
	static char** GetFiles(const char* directoryPath);
	//static FileInfo* GetFileInfos(const char* directoryPath);
	static int GetFileCount(const char* directoryPath)

private:
	Directory();
};