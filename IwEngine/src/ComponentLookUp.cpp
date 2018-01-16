#include "IwEngine\ComponentLookUp.h"

ComponentLookUp::ComponentLookUp() {
}

ComponentLookUp::~ComponentLookUp() {
	std::map<int, IComponentTable*>::iterator itr = _componentTables.begin();
	while (itr != _componentTables.end()) {
		delete itr->second;
		itr++;
	}
}

void ComponentLookUp::RemoveAllComponents(int gameObjectID) {
	for (auto const& table : _componentTables) {
		table.second->RemoveComponent(gameObjectID);
	}
}