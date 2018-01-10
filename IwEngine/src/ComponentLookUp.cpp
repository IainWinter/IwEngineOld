#include "IwEngine\ComponentLookUp.h"

void ComponentLookUp::RemoveAllComponents(int gameObjectID) {
	for (auto const& table : _componentTables) {
		table.second->RemoveComponent(gameObjectID);
	}
}