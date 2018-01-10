#pragma once

#include <vector>
#include <map>
#include "IwEngine\Common.h"

//Marker interface
class IComponentTable {
public:
	virtual void RemoveComponent(int gameObjectID) = 0;
};

template<typename TComponent>
class ComponentTable : public IComponentTable {
private:
	std::map<int, int> _lookUp;
	std::vector<TComponent*> _components;
public:
	void AddComponent(int gameObjectID, TComponent* component) {
		int index = _components.size();
		bool unique = _lookUp.emplace(gameObjectID, index).second;
		if (unique) {
			_components.push_back(component);
		}
	}

	virtual void RemoveComponent(int gameObjectID) {
		int index = _lookUp[gameObjectID];
		if (index >= 0) {
			_lookUp.erase(gameObjectID);
			_components.erase(_components.begin() + index);
		}
	}

	TComponent* GetComponent(int gameObjectID) {
		int index = _lookUp[gameObjectID];
		if (index >= 0) {
			return _components[index];
		}

		return nullptr;
	}

	inline int GetComponentCount() {
		return _lookUp.size();
	}
};