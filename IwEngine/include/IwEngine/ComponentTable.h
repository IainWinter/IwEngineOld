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
	std::map<int, int> _lookUp;
	std::vector<TComponent*> _components;
public:
	ComponentTable();
	~ComponentTable();

	void AddComponent(int gameObjectID, TComponent* component);
	void RemoveComponent(int gameObjectID);
	TComponent* GetComponent(int gameObjectID);
	std::vector<int> GetGameObjectIDs();

	inline int GetComponentCount() {
		return _lookUp.size();
	}

	inline std::vector<TComponent*>& GetComponents() {
		return _components;
	}
};


template<typename TComponent>
ComponentTable<TComponent>::ComponentTable() {}

template<typename TComponent>
ComponentTable<TComponent>::~ComponentTable() {
	for (std::vector<TComponent*>::iterator it = _components.begin(); it != _components.end(); ++it) {
		delete (*it);
	}

	_components.clear();
}

template<typename TComponent>
void ComponentTable<TComponent>::AddComponent(int gameObjectID, TComponent* component) {
	int index = _components.size();
	bool unique = _lookUp.emplace(gameObjectID, index).second;
	if (unique) {
		_components.push_back(component);
	}
}

template<typename TComponent>
void ComponentTable<TComponent>::RemoveComponent(int gameObjectID) {
	int index = _lookUp[gameObjectID];
	if (index >= 0) {
		_lookUp.erase(gameObjectID);
		_components.erase(_components.begin() + index);
	}
}

template<typename TComponent>
TComponent* ComponentTable<TComponent>::GetComponent(int gameObjectID) {
	int index = _lookUp[gameObjectID];
	if (index >= 0) {
		return _components[index];
	}

	return nullptr;
}

template<typename TComponent>
std::vector<int> ComponentTable<TComponent>::GetGameObjectIDs() {
	std::vector<int> keys;
	keys.reserve(_lookUp.size());

	for (auto const& element : _lookUp) {
		keys.push_back(element.first);
	}

	return keys;
}