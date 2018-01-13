#include "IwEngine\RigidBodySystem.h"

void System<RigidBody, Transform>::Update(ComponentLookUp& componentLookUp, float deltaTime) {
	ComponentTable <Transform>* transformTable = componentLookUp.GetComponentTable<Transform>();
	ComponentTable <RigidBody>* rigidBodyTable = componentLookUp.GetComponentTable<RigidBody>();
	std::vector<int> transformKeys = transformTable->GetGameObjectIDs();
	std::vector<int> rigidBodyKeys = rigidBodyTable->GetGameObjectIDs();
	std::vector<int> Objects;
	for (int i = 0; i < transformKeys.size(); i++) {
		for (int j = 0; j < rigidBodyKeys.size(); j++) {
			if (transformKeys.at(i) == rigidBodyKeys.at(j)) {
				Objects.push_back(rigidBodyKeys.at(j));
			}
		}
	}
}
