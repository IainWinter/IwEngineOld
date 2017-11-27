#include "ResourceManager.h"
#include "..//IwEngine.Utility/IO/IO.h"

ResourceManager::ResourceManager() {
	free = std::vector<Resource>();
	busy = std::vector<Resource>();
}

ResourceManager::~ResourceManager() {
	for (Resource& r : free) {
		delete &r;
	}

	for (Resource& r : busy) {
		delete &r;
	}
}

void ResourceManager::LoadSceneInfo(const char* sceneFolder) {
	size_t resourceCount;
	std::string* resourcePaths = Directory::GetFiles(sceneFolder, resourceCount);
	for (size_t i = 0; i < resourceCount; i++) {
		free.resize(free.size() + resourceCount);
		if (Path::IsFile(resourcePaths[i])) {
			ResourceInfo* info = LoadResourceInfo(resourcePaths[i]);
			Resource* resource = new Resource(info);
			free.push_back(*resource);
		}

		if (Path::IsDirectory(resourcePaths[i])) {
			LoadSceneInfo(resourcePaths[i].c_str());
		}
	}
}

ResourceInfo* ResourceManager::LoadResourceInfo(const std::string& resourcePath) const {
	uintmax_t fileSize = File::GetSize(resourcePath);
	return new ResourceInfo(resourcePath.c_str(), fileSize);
}

int main() {
	ResourceManager r = ResourceManager();
	r.LoadSceneInfo("C:\\Users\\Iain\\Desktop\\test1\\");
}