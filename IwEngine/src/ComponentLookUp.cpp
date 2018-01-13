#include "IwEngine\ComponentLookUp.h"

ComponentLookUp::ComponentLookUp() {
}

ComponentLookUp::~ComponentLookUp() {
	uint tableCount = _componentTables.size();
	for (size_t i = 0; i < tableCount; i++) {
		_componentTables.erase(i);
	}
}

void ComponentLookUp::RemoveAllComponents(int gameObjectID) {
	for (auto const& table : _componentTables) {
		table.second->RemoveComponent(gameObjectID);
	}
}