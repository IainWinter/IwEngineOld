#pragma once

#include <vector>
#include <map>
#include "IwEngine\Common.h"

//Marker interface
class IComponentTable {
public:
	virtual void RemoveComponent(int gameObjectID) = 0;
	virtual ~IComponentTable() {};
};

template<typename TComponent>
class ComponentTable : public IComponentTable {
private:
	std::map<int, TComponent*> _components;
public:
	ComponentTable();
	~ComponentTable();

	void AddComponent(int gameObjectID, TComponent* component);
	void RemoveComponent(int gameObjectID);
	TComponent* GetComponent(int gameObjectID);
	std::vector<int> GetGameObjectIDs();

	inline int GetComponentCount() {
		return _components.size();
	}
};


template<typename TComponent>
ComponentTable<TComponent>::ComponentTable() {}

template<typename TComponent>
ComponentTable<TComponent>::~ComponentTable() {
	std::map<int, TComponent*>::iterator itr = _components.begin();
	while (itr != _components.end()) {
		delete itr->second;
		itr++;
	}
}

template<typename TComponent>
void ComponentTable<TComponent>::AddComponent(int gameObjectID, TComponent* component) {
	_components.emplace(gameObjectID, component);
}

template<typename TComponent>
void ComponentTable<TComponent>::RemoveComponent(int gameObjectID) {
	_components.erase(gameObjectID);
}

template<typename TComponent>
TComponent* ComponentTable<TComponent>::GetComponent(int gameObjectID) {
	if (_components.count(gameObjectID)) {
		return _components[gameObjectID];
	}

	return nullptr;
}

template<typename TComponent>
std::vector<int> ComponentTable<TComponent>::GetGameObjectIDs() {
	std::vector<int> keys;
	keys.reserve(_components.size());

	for (auto const& element : _components) {
		keys.push_back(element.first);
	}

	return keys;
}