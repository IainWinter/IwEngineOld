#pragma once

#include "IwEngine\ColliderSystem.h"
#include "IwEngine\Transform.h"
#include "IwEngine\RigidBody.h"
#include <vector>


void System<SphereCollider, BoxCollider>::Update(ComponentLookUp& componentLookUp, float deltaTime) {
	ComponentTable <Transform>* transformTable = componentLookUp.GetComponentTable<Transform>();
	ComponentTable <RigidBody>* rigidBodyTable = componentLookUp.GetComponentTable<RigidBody>();
	std::vector<int> transformKeys = transformTable->GetGameObjectIDS();
	std::vector<int> rigidBodyKeys = rigidBodyTable->GetGameObjectIDS();
	std::vector<int> Objects; 
	for (int i = 0; i < transformKeys.size(); i++){
		for (int j = 0; j < rigidBodyKeys.size; j++){
			if (transformKeys.at(i) = rigidBodyKeys.at(j)){
				Objects.push_back(rigidBodyKeys.at(j));
			}
		}
	}
}

