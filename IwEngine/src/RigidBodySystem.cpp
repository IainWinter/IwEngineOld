#include "IwEngine\RigidBodySystem.h"

void System<RigidBody, Transform>::Update(ComponentLookUp& componentLookUp, float deltaTime) {
	std::vector<int> transformGOIDs = componentLookUp.GetComponentTable<Transform>()->GetGameObjectIDs();
	std::vector<int> rigidBodyGOIDs = componentLookUp.GetComponentTable<RigidBody>()->GetGameObjectIDs();

	std::vector<int> gameObjectIDs = std::vector<int>();

	uint tCount = transformGOIDs.size();
	uint rCount = rigidBodyGOIDs.size();
	for (uint i = 0; i < tCount; i++) {
		for (uint j = 0; j < rCount; j++) {
			if (transformGOIDs[i] == rigidBodyGOIDs[j]) {
				gameObjectIDs.push_back(i);
				i++;
			}
		}
	}

	uint gCount = gameObjectIDs.size();
	for (size_t i = 0; i < gCount; i++) {
		Transform* transform = componentLookUp.GetComponentTable<Transform>()->GetComponent(gameObjectIDs[i]);
		RigidBody* rigidBody = componentLookUp.GetComponentTable<RigidBody>()->GetComponent(gameObjectIDs[i]);

		transform->SetPosition(transform->GetPosition() - Math::Vector3(deltaTime, 0, 0));
	}
}
