#include "ResourceManager.h"
#include "IO\Directory.h"
#include "IO\File.h"
#include "IO\Path.h"

using namespace IwUtility::IO;

ResourceManager::ResourceManager() {
	free = std::vector<Resource*>();
	busy = std::vector<Resource*>();
}

ResourceManager::~ResourceManager() {
	for (Resource* r : free) {
		delete r;
	}

	for (Resource* r : busy) {
		delete r;
	}
}

ResourceInfo* ResourceManager::LoadResourceInfo(const std::string& resourcePath) const {
	uintmax_t fileSize = File::GetSize(resourcePath);
	return new ResourceInfo(resourcePath.c_str(), fileSize);
}

void ResourceManager::LoadSceneInfo(const char* sceneFolder) {
	size_t resourceCount;
	std::string* resourcePaths = Directory::GetFiles(sceneFolder, true, resourceCount);

	free.reserve(resourceCount);

	for (size_t i = 0; i < resourceCount; i++) {
		ResourceInfo* info = LoadResourceInfo(resourcePaths[i]);
		Resource* resource = new Resource(info);
		free.push_back(resource);
	}
}

int main() {
	ResourceManager r = ResourceManager();
	r.LoadSceneInfo("C:\\Users\\Iain\\Desktop\\test1\\");
}