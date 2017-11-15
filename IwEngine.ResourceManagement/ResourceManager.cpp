#include "ResourceManager.h"
#include "ResourceLoader.h"

class StringLoader : public ResourceLoader<std::string> {
public:
	StringLoader() : ResourceLoader() { }

	virtual void Load(std::string fileName, std::shared_ptr<std::string> ptr) const {
		*ptr = fileName;
	}
};

int main() {
	ResourceManager m = ResourceManager();

	StringLoader strLrd = StringLoader();

	m.RegisterLoader<std::string>(&strLrd);

	std::shared_ptr<std::string> ptr = m.Load<std::string>(std::string("Hello"));

}

template<typename T>
void ResourceManager::RegisterLoader(ResourceLoader<T>* resourceLoader) {
	resourceLoaders.emplace(typeid(T), &resourceLoader);
}

ResourceManager::ResourceManager() {
	resourceLoaders = std::unordered_map<std::type_index, ResourceLoaderBase*>();
	loadedResources = std::unordered_map<std::string, std::weak_ptr<void>>();
}

ResourceManager::~ResourceManager() {
}


template<typename T>
std::shared_ptr<T> ResourceManager::Load(std::string fileName) {
	ResourceLoader<T>* typeLoader = (ResourceLoader<T>*)resourceLoaders[typeid(T)];

	std::shared_ptr<T> ptr = std::make_shared<T>();

	typeLoader->.Load(fileName, ptr);

	//loadedResources.emplace(fileName, ptr);

	return ptr;
}