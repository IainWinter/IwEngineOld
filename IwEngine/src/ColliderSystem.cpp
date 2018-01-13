#pragma once

#include "IwEngine\ColliderSystem.h"
#include "IwEngine\Transform.h"
#include "IwEngine\RigidBody.h"
#include <vector>


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
		if (i <= boxColliderKeys.size()) {
			BoxCollider collider = boxColliderTable.GetComponent(boxColliderKeys.at(i));
	}
}
