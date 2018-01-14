#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\ComponentTable.h"

class ComponentLookUp {
private:
	std::map<int, IComponentTable*> _componentTables;
public:
	IWENGINE_API ComponentLookUp();
	IWENGINE_API ~ComponentLookUp();

	IWENGINE_API ComponentLookUp(const ComponentLookUp&) = delete;
	IWENGINE_API const ComponentLookUp& operator=(const ComponentLookUp&) = delete;

	template<typename TComponent>
	void AddComponent(int gameObjectID, TComponent* component);

	template<typename TComponent>
	void RemoveComponent(int gameObjectID, TComponent* component);

	IWENGINE_API void RemoveAllComponents(int gameObjectID);

	template<typename TComponent>
	TComponent* GetComponent(int gameObjectID);

	template<typename TComponent>
	ComponentTable<TComponent>* GetComponentTable();
};

template<typename TComponent>
void ComponentLookUp::AddComponent(int gameObjectID, TComponent* component) {
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
void ComponentLookUp::RemoveComponent(int gameObjectID, TComponent* component) {
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

template<typename TComponent>
TComponent* ComponentLookUp::GetComponent(int gameObjectID) {
	int componentID = typeid(TComponent).hash_code();
	bool hasTable = _componentTables.count(componentID);
	if (hasTable) {
		return dynamic_cast<ComponentTable<TComponent>*>(_componentTables[componentID])
			->GetComponent(gameObjectID);
	}

	return nullptr;
}

template<typename TComponent>
ComponentTable<TComponent>* ComponentLookUp::GetComponentTable() {
	int componentID = typeid(TComponent).hash_code();
	ComponentTable<TComponent>* table = dynamic_cast<ComponentTable<TComponent>*>(_componentTables[componentID]);

	return table;
}
