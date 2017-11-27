#pragma once
#include "Resource.cpp"
#include <vector>

class ResourceManager {
private:
	std::vector<Resource> free;
	std::vector<Resource> busy;
	ResourceInfo* LoadResourceInfo(const std::string& resourcePath) const;
public:
	ResourceManager();
	~ResourceManager();
	void LoadSceneInfo(const char* sceneFolder);

};