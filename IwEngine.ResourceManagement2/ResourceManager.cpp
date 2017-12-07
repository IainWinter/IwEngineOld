#include "ResourceManager.h"
#include "IO\Directory.h"
#include "IO\File.h"
#include "IO\Path.h"

using namespace IwUtility::IO;

ResourceManager::ResourceManager() {
	info = std::vector<ResourceInfo*>();
	busy = std::vector<Resource*>();
}

ResourceManager::~ResourceManager() {
	for (ResourceInfo* r : info) {
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

int ResourceManager::LoadResourceIntoBusy(ResourceInfo* resourceInfo) {
	for (auto& b : busy) {
		if (b->info == resourceInfo) {
			return -1;
		}
	}

	Resource* resource = new Resource(resourceInfo);
	busy.push_back(resource);
	return busy.size() - 1;
}

void ResourceManager::LoadSceneInfo(const char* sceneFolder) {
	size_t resourceCount;
	std::string* resourcePaths = Directory::GetFiles(sceneFolder, true, resourceCount);

	info.reserve(resourceCount);

	for (size_t i = 0; i < resourceCount; i++) {
		ResourceInfo* resourceInfo = LoadResourceInfo(resourcePaths[i]);
		info.push_back(resourceInfo);
	}
}

Resource* ResourceManager::LoadResource(const char* resourcePath) {
	for (auto& i : info) {
		if (strcmp(i->name, resourcePath) == 0) {
			int busyIndex = LoadResourceIntoBusy(i);
			return busy[busyIndex];
		}
	}
}

int main() {
	ResourceManager r = ResourceManager();
	r.LoadSceneInfo("C:\\Users\\Iain\\Desktop\\test1\\");
	Resource* res = r.LoadResource("C:\\Users\\Iain\\Desktop\\test1\\scripts\\scriptA.txt"); //Cut this down to be relative path
}