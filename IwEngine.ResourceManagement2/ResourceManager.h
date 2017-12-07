#pragma once
#include "Resource.cpp"
#include <vector>

class ResourceManager {
private:
	std::vector<ResourceInfo*> info;
	std::vector<Resource*> busy;
	ResourceInfo* LoadResourceInfo(const std::string& resourcePath) const;
	int LoadResourceIntoBusy(ResourceInfo* recource);
public:
	ResourceManager();
	~ResourceManager();
	void LoadSceneInfo(const char* sceneFolder);
	Resource* LoadResource(const char* resourcePath);
};