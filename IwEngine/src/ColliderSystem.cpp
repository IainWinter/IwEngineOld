#pragma once

#include "IwEngine\ColliderSystem.h"
#include "IwEngine\Transform.h"
#include "IwEngine\RigidBody.h"
#include <vector>


void System<SphereCollider, BoxCollider>::Update(ComponentLookUp& componentLookUp, float deltaTime) {
	ComponentTable <Transform>* transformTable = componentLookUp.GetComponentTable<Transform>();
	ComponentTable <BoxCollider>* boxColliderTable = componentLookUp.GetComponentTable <BoxCollider>();
	ComponentTable <SphereCollider>* sphereColliderTable = componentLookUp.GetComponentTable <SphereCollider>();

	std::vector<int> transformKeys = transformTable->GetGameObjectIDS();
	std::vector<int> boxColliderKeys = boxColliderTable->GetGameObjectIDS();
	std::vector<int> sphereColliderKeys = sphereColliderTable->GetGameObjectIDS();
	std::vector<int> checkObjects; 

	for (int i = 0; i < transformKeys.size(); i++) {
		for (int j = 0; j < boxColliderKeys.size() + sphereColliderKeys.size(); j++) {
			if (j <= boxColliderKeys.size()) {
				if (transformKeys.at(i) == boxColliderKeys.at(j)) {
					checkObjects.push_back(transformKeys.at(i));
				}
				else {
					if (transformKeys.at(i) == sphereColliderKeys.at(j)) {
						checkObjects.push_back(transformKeys.at(i));
					}
				}
			}
		}
	}
	for (int objectKey : checkObjects) {

	}
}

