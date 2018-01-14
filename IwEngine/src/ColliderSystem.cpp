#pragma once

#include "IwEngine\ColliderSystem.h"
#include "IwEngine\Transform.h"
#include <vector>
#include "IwEngine\Physics\BoundingBox.h"
#include "IwEngine\Physics\BoundingSphere.h"
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

			const Physics::BoundingMesh& bounds1 = collider1->GetCollider();
			const Physics::BoundingMesh& bounds2 = collider2->GetCollider();

			bounds1.Intersects(bounds2, transform1, transform2);
		}
	}
}
//
//void System<SphereCollider, BoxCollider>::Update(ComponentLookUp& componentLookUp, float deltaTime) {
//	ComponentTable <Transform>* transformTable = componentLookUp.GetComponentTable<Transform>();
//	ComponentTable <BoxCollider>* boxColliderTable = componentLookUp.GetComponentTable <BoxCollider>();
//	ComponentTable <SphereCollider>* sphereColliderTable = componentLookUp.GetComponentTable <SphereCollider>();
//
//	std::vector<int> transformKeys = transformTable->GetGameObjectIDs();
//	std::vector<int> boxColliderKeys = boxColliderTable->GetGameObjectIDs();
//	std::vector<int> sphereColliderKeys = sphereColliderTable->GetGameObjectIDs();
//	std::vector<int> transformBoxKeys;
//	std::vector<int> transformSphereKeys;
//	//check for components of type transform and collider and put them in seperate vector
//	for (int i = 0; i < transformKeys.size(); i++) {
//		for (int j = 0; j < boxColliderKeys.size() + sphereColliderKeys.size(); j++) {
//			if (j <= boxColliderKeys.size()) {
//				if (transformKeys.at(i) == boxColliderKeys.at(j)) {
//					transformBoxKeys.push_back(boxColliderKeys.at(j));
//				}
//			}
//				else {
//					if (transformKeys.at(i) == sphereColliderKeys.at(j)) {
//						transformSphereKeys.push_back(sphereColliderKeys.at(j));
//					}
//				}
//		}
//	}
//	//check all components with transform and collider for collisions
//	for (int i = 0; i < transformBoxKeys.size() + transformSphereKeys.size(); i++){
//		bool isColliding; 
//		if (i <= boxColliderKeys.size()) {
//			BoxCollider* collider = boxColliderTable->GetComponent(boxColliderKeys.at(i));
//			Physics::BoundingBox box1 = collider->GetCollider;
//			//Can't check for collision between box and sphere
//			for (int j = i+1; j < boxColliderKeys.size; j++) {
//				BoxCollider* other = boxColliderTable->GetComponent(boxColliderKeys.at(j));
//				Physics::BoundingBox box2 = other->GetCollider;
//				Physics::CollisionData boxCollision = box1.IntersectBoundingBox (box2);
//				isColliding = boxCollision.GetIntersect;
//				if (isColliding) {
//					//collision response stuff
//				}
//			}
//		}
//		else {
//			SphereCollider* collider = sphereColliderTable->GetComponent(sphereColliderKeys.at(i));
//			Physics::BoundingSphere sphere1 = collider->GetCollider;
//			for (int j = i + 1; j < sphereColliderKeys.size; j++) {
//				SphereCollider* other = sphereColliderTable->GetComponent(sphereColliderKeys.at(j));
//				Physics::BoundingSphere sphere2 = other->GetCollider;
//				Physics::CollisionData sphereCollision = sphere1.IntersectBS(sphere2);
//				isColliding = sphereCollision.GetIntersect; 
//				if (isColliding) {
//					//collision response stuff
//				}
//			}
//		}
//	}
//}
