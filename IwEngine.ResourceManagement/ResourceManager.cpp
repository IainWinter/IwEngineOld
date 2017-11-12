#include "ResourceManager.h"
#include "ResourceLoader.h"

ResourceManager::ResourceManager() {
	resourceLoaders = std::unordered_map<std::type_index, ResourceLoader<void>*>();
	resources = std::unordered_map<std::string, std::weak_ptr<void>>();
}

ResourceManager::~ResourceManager() {
}

template<typename T>
std::shared_ptr<T> ResourceManager::Load(std::string fileName) {
	typedef T type_def;
	int i = resourceLoaders.find(typeid(type_def));

	return std::make_shared<T>(fileName);
}

int main() {
	ResourceManager m = ResourceManager();

	StringLoader strLrd = StringLoader();

	m.RegisterLoader<std::string>(strLrd);
	std::shared_ptr<std::string> ptr = m.Load<std::string>(std::string("Hello"));
}

class StringLoader : public ResourceLoader<std::string> {
	virtual void Load(std::shared_ptr<std::string> ptr) const {
		ptr = std::make_shared<std::string>("Test");
	}
};