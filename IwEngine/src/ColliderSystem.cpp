#include "IwEngine\ColliderSystem.h"
#include <vector>
#include "IwEngine\Physics\CollisionData.h"

void System<Collider, Transform>::Update(ComponentLookUp& componentLookUp, float deltaTime) {
	std::vector<int> transformGOIDs = componentLookUp.GetComponentTable<Transform>()->GetGameObjectIDs();
	std::vector<int> colliderGOIDs = componentLookUp.GetComponentTable<Collider>()->GetGameObjectIDs();

	std::vector<int> gameObjectIDs = std::vector<int>();

	uint tCount = transformGOIDs.size();
	uint rCount = colliderGOIDs.size();
	for (uint i = 0; i < tCount; i++) {
		for (uint j = 0; j < rCount; j++) {
			if (transformGOIDs[i] == colliderGOIDs[j]) {
				gameObjectIDs.push_back(i);
				i++;
			}
		}
	}

	uint gCount = gameObjectIDs.size();
	for (size_t i = 0; i < gCount; i++) {
		for (size_t j = 0; j < gCount; j++) {
			if (i == j) continue;
			Transform* transform1 = componentLookUp.GetComponent<Transform>(gameObjectIDs[i]);
			Transform* transform2 = componentLookUp.GetComponent<Transform>(gameObjectIDs[j]);
			Collider* collider1 = componentLookUp.GetComponent<Collider>(gameObjectIDs[i]);
			Collider* collider2 = componentLookUp.GetComponent<Collider>(gameObjectIDs[j]);

			const Physics::Bounds& bounds1 = collider1->GetCollider();
			const Physics::Bounds& bounds2 = collider2->GetCollider();

			std::vector<Math::Vector3> axies1 = bounds1.GetAxies();
			std::vector<Math::Vector3> axies2 = bounds2.GetAxies();

			std::vector<Math::Vector3> axies;
			size_t count1 = axies1.size();
			size_t count2 = axies2.size();

			Math::Vector3 axis;
			float distance;
			for (size_t i = 0; i < count1 + count2; i++) {
				if (i < count1) {
					axis = axies1[i] * transform1->GetRotation();
				} else {
					axis = axies2[i - count1] * transform2->GetRotation();
				}

				float min1, max1, min2, max2;
				bounds1.ProjectOntoAxis(axis, transform1->GetRotation(), transform1->GetPosition(), min1, max1);
				bounds2.ProjectOntoAxis(axis, transform2->GetRotation(), transform2->GetPosition(), min2, max2);

				if (min1 < min2) {
					distance = min2 - max1;
				} else {
					distance = min1 - max2;
				}

				if (distance > 0) {
					break;
				}
			}

			collider1->SetCollisionData(collider2, axis, distance < 0, distance);
			collider2->SetCollisionData(collider1, axis, distance < 0, -distance);
		}
	}
}