#pragma once

#include "IwEngine\ComponentTable.h"

class ComponentLookUp {
private:
	std::map<int, IComponentTable*> _componentTables;
public:
	ComponentLookUp() {}

	ComponentLookUp(const ComponentLookUp&) = delete;
	const ComponentLookUp& operator=(const ComponentLookUp&) = delete;

	template<typename TComponent>
	void AddComponent(int gameObjectID, TComponent* component) {
		int componentID = typeid(TComponent).hash_code();
		bool hasTable = _componentTables.count(componentID);
		ComponentTable<TComponent>* table;
		if (!hasTable) {
			table = new ComponentTable<TComponent>();
			_componentTables.emplace(componentID, table);
		} else {
			table = dynamic_cast<ComponentTable<TComponent>*>(_componentTables[componentID]);
		}

		table->AddComponent(gameObjectID, component);
	}

	template<typename TComponent>
	void RemoveComponent(int gameObjectID, TComponent* component) {
		int componentID = typeid(TComponent).hash_code();
		bool hasTable = _componentTables.count(componentID);
		if (hasTable) {
			ComponentTable<TComponent>* table = dynamic_cast<ComponentTable<TComponent>*>(_componentTables[componentID]);
			table->RemoveComponent(gameObjectID);

			//Remove unused table
			if (table->GetComponentCount() == 0) {
				_componentTables.erase(componentID);
			}
		}
	}

	void RemoveAllComponents(int gameObjectID);

	template<typename TComponent>
	TComponent* GetComponent(int gameObjectID) {
		int componentID = typeid(TComponent).hash_code();
		bool hasTable = _componentTables.count(componentID);
		if (hasTable) {
			return dynamic_cast<ComponentTable<TComponent>*>(_componentTables[componentID])
				->GetComponent(gameObjectID);
		}

		return nullptr;
	}
};