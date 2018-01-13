#pragma once

#include "IwEngine\ColliderSystem.h"
#include "IwEngine\Transform.h"
#include "IwEngine\RigidBody.h"
#include <vector>
#include "IwEngine\Physics\BoundingBox.h"
#include "IwEngine\Physics\BoundingSphere.h"
#include "IwEngine\Physics\CollisionData.h"

void System<Collider>::Update(ComponentLookUp& componentLookUp, float deltaTime) {
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
			Transform* transform1 = componentLookUp.GetComponentTable<Transform>()->GetComponent(gameObjectIDs[i]);
			Collider* collider1 = componentLookUp.GetComponentTable<Collider>()->GetComponent(gameObjectIDs[i]);
			Transform* transform2 = componentLookUp.GetComponentTable<Transform>()->GetComponent(gameObjectIDs[j]);
			Collider* collider2 = componentLookUp.GetComponentTable<Collider>()->GetComponent(gameObjectIDs[j]);


			
		}


		transform->SetPosition(transform->GetPosition() - Math::Vector3(deltaTime, 0, 0));
	}
}

void System<SphereCollider, BoxCollider>::Update(ComponentLookUp& componentLookUp, float deltaTime) {
	ComponentTable <Transform>* transformTable = componentLookUp.GetComponentTable<Transform>();
	ComponentTable <BoxCollider>* boxColliderTable = componentLookUp.GetComponentTable <BoxCollider>();
	ComponentTable <SphereCollider>* sphereColliderTable = componentLookUp.GetComponentTable <SphereCollider>();

	std::vector<int> transformKeys = transformTable->GetGameObjectIDs();
	std::vector<int> boxColliderKeys = boxColliderTable->GetGameObjectIDs();
	std::vector<int> sphereColliderKeys = sphereColliderTable->GetGameObjectIDs();
	std::vector<int> transformBoxKeys;
	std::vector<int> transformSphereKeys;

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
	for (int i = 0; i < transformBoxKeys.size() + transformSphereKeys.size(); i++){
		bool isColliding; 
		if (i <= boxColliderKeys.size()) {
			BoxCollider* collider = boxColliderTable->GetComponent(boxColliderKeys.at(i));
			Physics::BoundingBox box1 = collider->GetCollider;
			//Can't check for collision between box and sphere
			for (int j = i+1; j < boxColliderKeys.size; j++) {
				BoxCollider* other = boxColliderTable->GetComponent(boxColliderKeys.at(j));
				Physics::BoundingBox box2 = other->GetCollider;
				box1.IntersectBoundingBox (box2);
				//still need to process and return if colliding 
			}
		}
		else {
			SphereCollider* collider = sphereColliderTable->GetComponent(sphereColliderKeys.at(i));
			Physics::BoundingSphere sphere1 = collider->GetCollider;
			for (int j = i + 1; j < sphereColliderKeys.size; j++) {
				SphereCollider* other = sphereColliderTable->GetComponent(sphereColliderKeys.at(j));
				Physics::BoundingSphere sphere2 = other->GetCollider;
				sphere1.IntersectBS(sphere2);
			}
		}
	}
}
