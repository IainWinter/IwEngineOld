#pragma once

#include "Resource.cpp"
#include <vector>

class ResourceManager {
private:
	std::vector<Resource> free;
	std::vector<Resource> busy;
public:
	ResourceManager();
	~ResourceManager();
	void LoadSceneInfo(const char* sceneFolder);
};

