#include <vector>
#include <limits>
#include <set>
#include "IwEngine\ColliderSystem.h"
#include "IwEngine\Physics\CollisionData.h"
#include "Physics\GJK.h"

void System<Collider, Transform>::Update(ComponentLookUp& componentLookUp, float deltaTime) {
	std::vector<int> transformGOIDs = componentLookUp.GetComponentTable<Transform>()->GetGameObjectIDs();
	std::vector<int> colliderGOIDs = componentLookUp.GetComponentTable<Collider>()->GetGameObjectIDs();

	std::vector<int> gameObjectIDs = std::vector<int>();

	uint tCount = transformGOIDs.size();
	uint rCount = colliderGOIDs.size();
	for (uint i = 0; i < tCount; i++) {
		for (uint j = 0; j < rCount; j++) {
			if (transformGOIDs[i] == colliderGOIDs[j]) {
				gameObjectIDs.push_back(transformGOIDs[i]);
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

			Transform* transform1 = componentLookUp.GetComponent<Transform>(gameObjectIDs[i]);
			Transform* transform2 = componentLookUp.GetComponent<Transform>(gameObjectIDs[j]);

			const Physics::Bounds& bounds1 = componentLookUp.GetComponent<Collider>(gameObjectIDs[i])->GetCollider();
			const Physics::Bounds& bounds2 = componentLookUp.GetComponent<Collider>(gameObjectIDs[j])->GetCollider();

			Physics::ColliderGJK(
				bounds1, bounds2, 
				{ 
					transform1->GetPosition(), transform2->GetPosition(),
					transform1->GetRotation(), transform2->GetRotation() 
				}
			);
		}
	}

	/*std::set<int> alreadyIterated;

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
			float distance = (std::numeric_limits<float>::max)();

			Math::Vector3 tmpPoc;
			Math::Vector3 tmpAxis;
			float tmpDistance;
			for (size_t i = 0; i < count1 + count2; i++) {
				if (i < count1) {
					tmpAxis = axies1[i] * transform1->GetRotation();
					tmpPoc = tmpAxis + transform1->GetPosition();
				} else {
					tmpAxis = axies2[i - count1] * transform2->GetRotation();
					tmpPoc = tmpAxis + transform1->GetPosition();
				}

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

					}
				}
			}

			//Response
			if (axis != Math::Vector3::Zero) {
				std::cout << distance << std::endl;

				RigidBody* rigidbody1 = componentLookUp.GetComponent<RigidBody>(gameObjectIDs[i]);
				RigidBody* rigidbody2 = componentLookUp.GetComponent<RigidBody>(gameObjectIDs[j]);

				if (!rigidbody1 || !rigidbody2) return;

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

				//Correction
				float Ainv_mass;
				float Binv_mass;
				if (rigidbody1->mass == 0) {
					Ainv_mass = 0;
				} else {
					Ainv_mass = 1 / rigidbody1->mass;
				}

				if (rigidbody2->mass == 0) {
					Binv_mass = 0;
				} else {
					Binv_mass = 1 / rigidbody2->mass;
				}

				const float percent = 0.8f;
				const float slop = 0.1f;
				Math::Vector3 correction = max(distance - slop, .0001f) / (Ainv_mass + Binv_mass) * percent * axis;
				transform1->SetPosition(transform1->GetPosition() -= Ainv_mass * correction);
				transform2->SetPosition(transform2->GetPosition() += Binv_mass * correction);
			}
		}
	}*/
}

Math::Vector3 System<Collider, Transform>::SimplexDirection(const Math::Vector3& a, const Math::Vector3& b) {
	if (SameDirection(b - a, -a)) {
		return (b - a).Cross(-a).Cross(b - a);
	} else {
		return -a;
	}
}

Math::Vector3 System<Collider, Transform>::SimplexDirection(const Math::Vector3& a, const Math::Vector3& b, const Math::Vector3& c) {
	Math::Vector3 abc = (b - a).Cross(c - a);
	if (SameDirection(abc.Cross(c - a), -a)) {
		if (SameDirection(c - a, -a)) {
			return (c - a).Cross(-a).Cross(c - a);
		}

		if (SameDirection(b - a, -a)) {
			return (b - a).Cross(-a).Cross(b - a);
		}

		return -a;
	}

	if (SameDirection((b - a).Cross(abc), -a)) {
		if (SameDirection(b - a, -a)) {
			return (b - a).Cross(-a).Cross(b - a);
		}

		return -a;
	}

	if (SameDirection(abc, -a)) {
		return abc;
	}

	return -abc;
}

Math::Vector3 System<Collider, Transform>::SimplexDirection(const Math::Vector3& a, const Math::Vector3& b,
	const Math::Vector3& c, const Math::Vector3& d) {
	Math::Vector3 abd = (b - a).Cross(d - a);
	Math::Vector3 bcd = (c - b).Cross(d - c);
	Math::Vector3 cad = (a - c).Cross(d - a);

	if (SameDirection(abd, -a)) {
		Math::Vector3 dir = SimplexDirection(a, b, d);
		if (abd != -dir) {
			return dir;
		}

		return 0;
	}

	if (SameDirection(bcd, -a)) {
		Math::Vector3 dir = SimplexDirection(b, c, d);
		if (bcd != -dir) {
			return dir;
		}

		return 0;
	}

	if (SameDirection(cad, -a)) {
		Math::Vector3 dir = SimplexDirection(c, a, d);
		if (cad != -dir) {
			return dir;
		}

		return 0;
	}

	return 0;
}

bool System<Collider, Transform>::SameDirection(const Math::Vector3& direction, const Math::Vector3& ao) {
	return direction.Dot(ao) > 0;
}
