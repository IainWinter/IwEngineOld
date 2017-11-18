#pragma once

#include <unordered_map>
#include <string>
#include <typeindex>
#include <memory>
#include "ResourceLoader.h"
#include <vector>

class ResourceManager {
private:
	std::unordered_map<std::type_index, std::unique_ptr<ResourceLoaderBase>> resourceLoaders;
	std::unordered_map<std::string, std::weak_ptr<void>> loadedResources;
public:
	ResourceManager();
	~ResourceManager();
	template<typename TResource> std::shared_ptr<TResource> Load(const char* fileName);
	void Unload(const char* fileName);
	template<typename TResource> std::shared_ptr<TResource> FindResource(const char* fileName) const;
	template<typename TResource> std::shared_ptr<TResource>* FindAllResourcesOfType() const;
	template<typename TResource, typename TLoader, typename... TArgs> void RegisterLoader(TArgs&&... args);
	template<typename TResource> void UnregisterLoader();
	template<typename TResource> bool HasLoader() const;
};