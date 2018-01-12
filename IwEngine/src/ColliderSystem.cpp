#pragma once

#include "IwEngine\ColliderSystem.h"
#include "IwEngine\Transform.h"
#include "IwEngine\RigidBody.h"
#include <vector>


void System<SphereCollider, BoxCollider>::Update(ComponentLookUp& componentLookUp, float deltaTime) {
	ComponentTable <Transform>* transformTable = componentLookUp.GetComponentTable<Transform>();
	std::vector<int> transformKeys = transformTable->GetGameObjectIDS();
	
}

