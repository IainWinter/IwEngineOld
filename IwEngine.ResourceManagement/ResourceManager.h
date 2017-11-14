#pragma once

#include <unordered_map>
#include <string>
#include <typeindex>
#include <memory>
#include "ResourceLoader.h"

class ResourceManager {
private:
	std::unordered_map<std::type_index, ResourceLoaderBase*> resourceLoaders;
	std::unordered_map<std::string, std::weak_ptr<void>> loadedResources;
public:
	ResourceManager();
	~ResourceManager();
	template<class T> std::shared_ptr<T> Load(std::string fileName);
	void Unload(std::string fileName);
	template<class T> std::shared_ptr<T> FindResource(std::string fileName);
	template<class T> std::shared_ptr<T>* FindAllResourcesOfType();
	template<class T> void RegisterLoader(ResourceLoaderBase resourceLoader);
	template<class T> void UnregisterLoader();
	template<class T> bool HasLoader();
};