#include <vector>
#include <limits>
#include <set>
#include "IwEngine\ColliderSystem.h"
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

	std::set<int> alreadyIterated;

	uint gCount = gameObjectIDs.size();
	for (size_t i = 0; i < gCount; i++) {
		for (size_t j = 0; j < gCount; j++) {
			//Don't interate twice
			if (i == j) continue;
			if (alreadyIterated.find(j) != alreadyIterated.end()) continue;
			alreadyIterated.insert(i);

			//SAT
			Transform* transform1 = componentLookUp.GetComponent<Transform>(gameObjectIDs[i]);
			Transform* transform2 = componentLookUp.GetComponent<Transform>(gameObjectIDs[j]);
			Collider* collider1 = componentLookUp.GetComponent<Collider>(gameObjectIDs[i]);
			Collider* collider2 = componentLookUp.GetComponent<Collider>(gameObjectIDs[j]);

			const Physics::Bounds& bounds1 = collider1->GetCollider();
			const Physics::Bounds& bounds2 = collider2->GetCollider();

			std::vector<Math::Vector3> axies1 = bounds1.GetAxies();
			std::vector<Math::Vector3> axies2 = bounds2.GetAxies();

			size_t count1 = axies1.size();
			size_t count2 = axies2.size();

			Math::Vector3 axis;
			Math::Vector3 pointOfContact;
			float distance = (std::numeric_limits<float>::max)();

			Math::Vector3 tmpAxis;
			float tmpDistance;
			for (size_t i = 0; i < count1 + count2; i++) {
				if (i < count1) {
					tmpAxis = axies1[i] * transform1->GetRotation();
				} else {
					tmpAxis = axies2[i - count1] * transform2->GetRotation();
				}

				//This can't be right?
				//tmpAxis.x = fabsf(tmpAxis.x);
				//tmpAxis.y = fabsf(tmpAxis.y);
				//tmpAxis.z = fabsf(tmpAxis.z);

				float min1, max1, min2, max2;
				bounds1.ProjectOntoAxis(tmpAxis, transform1->GetRotation(), transform1->GetPosition(), min1, max1);
				bounds2.ProjectOntoAxis(tmpAxis, transform2->GetRotation(), transform2->GetPosition(), min2, max2);

				if (min1 < min2) {
					tmpDistance = min2 - max1;
				} else {
					tmpDistance = min1 - max2;
				}

				if (tmpDistance > 0) {
					axis = Math::Vector3::Zero;
					break;
				} else {
					if (fabsf(tmpDistance) < fabsf(distance)) {
						distance = tmpDistance;
						axis = tmpAxis;

						if (min1 < min2) {
							pointOfContact = axis * (min2 + max1) / 2 + transform1->GetPosition();
						} else {
							pointOfContact = axis * (min1 + max2) / 2 + transform1->GetPosition();
						}
					}
				}
			}

			//Response
			if (axis != Math::Vector3::Zero) {
				std::cout << pointOfContact << std::endl;
				RigidBody* rigidbody1 = componentLookUp.GetComponent<RigidBody>(gameObjectIDs[i]);
				RigidBody* rigidbody2 = componentLookUp.GetComponent<RigidBody>(gameObjectIDs[j]);

				Math::Vector3 relitiveVelocity = rigidbody2->velocity - rigidbody1->velocity;

				float rvOnNormal = relitiveVelocity.Dot(axis);

				if (rvOnNormal > 0) {
					return;
				}

				float elasticity = min(collider1->GetMaterial().elasticity, collider2->GetMaterial().elasticity);

				float impulseScale = -(1 + elasticity) * rvOnNormal;
				impulseScale /= 1 / rigidbody1->mass + 1 / rigidbody2->mass;

				Math::Vector3 impulse = impulseScale * axis;

				rigidbody1->velocity -= impulse * (1 / rigidbody1->mass);
				rigidbody2->velocity += impulse * (1 / rigidbody2->mass);
			}
		}
	}
}