#include "ResourceManager.h"
#include "ResourceLoader.h"
#include <iostream>

class StringLoader : public ResourceLoader<std::string> {
public:
	StringLoader() : ResourceLoader() {}

	virtual std::string Load(const char* fileName) const {
		return fileName;
	}
};

int main() {
	ResourceManager m = ResourceManager();

	m.RegisterLoader<std::string, StringLoader>();

	{
		std::shared_ptr<std::string> ptr = m.Load<std::string>("Hello");
		std::cout << *ptr << std::endl;
	}

	m.FindResource("Hello");

	system("pause");
}

ResourceManager::ResourceManager() {
	resourceLoaders = std::unordered_map<std::type_index, std::unique_ptr<ResourceLoaderBase>>();
	loadedResources = std::unordered_map<std::string, std::weak_ptr<void>>();
}

ResourceManager::~ResourceManager() {

}

template<typename TResource, typename TLoader, typename... TArgs>
void ResourceManager::RegisterLoader(TArgs&&... args) {
	resourceLoaders.emplace(typeid(TResource), std::make_unique<TLoader>(args...));
}

template<typename TResource>
std::shared_ptr<TResource> ResourceManager::Load(const char* fileName) {
	typedef ResourceLoader<TResource> TLoader;
	TLoader* typeLoader = (TLoader*)resourceLoaders[typeid(TResource)].get();

	TResource resource = typeLoader->Load(fileName);
	std::shared_ptr<TResource> resourcePtr = std::make_shared<TResource>(resource);

	loadedResources.emplace(fileName, resourcePtr);

	return resourcePtr;
}