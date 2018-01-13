#pragma once

#include "IwEngine\ColliderSystem.h"
#include "IwEngine\Transform.h"
#include <vector>
#include "IwEngine\Physics\BoundingBox.h"
#include "IwEngine\Physics\BoundingSphere.h"
#include "IwEngine\Physics\CollisionData.h"


void System<SphereCollider, BoxCollider>::Update(ComponentLookUp& componentLookUp, float deltaTime) {
	ComponentTable <Transform>* transformTable = componentLookUp.GetComponentTable<Transform>();
	ComponentTable <BoxCollider>* boxColliderTable = componentLookUp.GetComponentTable <BoxCollider>();
	ComponentTable <SphereCollider>* sphereColliderTable = componentLookUp.GetComponentTable <SphereCollider>();

	std::vector<int> transformKeys = transformTable->GetGameObjectIDs();
	std::vector<int> boxColliderKeys = boxColliderTable->GetGameObjectIDs();
	std::vector<int> sphereColliderKeys = sphereColliderTable->GetGameObjectIDs();
	std::vector<int> transformBoxKeys;
	std::vector<int> transformSphereKeys;
	//check for components of type transform and collider and put them in seperate vector
	for (int i = 0; i < transformKeys.size(); i++) {
		for (int j = 0; j < boxColliderKeys.size() + sphereColliderKeys.size(); j++) {
			if (j <= boxColliderKeys.size()) {
				if (transformKeys.at(i) == boxColliderKeys.at(j)) {
					transformBoxKeys.push_back(boxColliderKeys.at(j));
				}
			}
				else {
					if (transformKeys.at(i) == sphereColliderKeys.at(j)) {
						transformSphereKeys.push_back(sphereColliderKeys.at(j));
					}
				}
		}
	}
	//check all components with transform and collider for collisions
	for (int i = 0; i < transformBoxKeys.size() + transformSphereKeys.size(); i++){
		bool isColliding; 
		if (i <= boxColliderKeys.size()) {
			BoxCollider* collider = boxColliderTable->GetComponent(boxColliderKeys.at(i));
			Physics::BoundingBox box1 = collider->GetCollider;
			//Can't check for collision between box and sphere
			for (int j = i+1; j < boxColliderKeys.size; j++) {
				BoxCollider* other = boxColliderTable->GetComponent(boxColliderKeys.at(j));
				Physics::BoundingBox box2 = other->GetCollider;
				Physics::CollisionData boxCollision = box1.IntersectBoundingBox (box2);
				isColliding = boxCollision.GetIntersect;
				if (isColliding) {
					//collision response stuff
				}
			}
		}
		else {
			SphereCollider* collider = sphereColliderTable->GetComponent(sphereColliderKeys.at(i));
			Physics::BoundingSphere sphere1 = collider->GetCollider;
			for (int j = i + 1; j < sphereColliderKeys.size; j++) {
				SphereCollider* other = sphereColliderTable->GetComponent(sphereColliderKeys.at(j));
				Physics::BoundingSphere sphere2 = other->GetCollider;
				Physics::CollisionData sphereCollision = sphere1.IntersectBS(sphere2);
				isColliding = sphereCollision.GetIntersect; 
				if (isColliding) {
					//collision response stuff
				}
			}
		}
	}
}
