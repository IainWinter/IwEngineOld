#pragma once

#include "IwEngine\ColliderSystem.h"
#include "IwEngine\Transform.h"

void System<SphereCollider, BoxCollider>::Update(ComponentLookUp& componentLookUp, float deltaTime) {
	componentLookUp.GetComponentTable <Transform>();
}

