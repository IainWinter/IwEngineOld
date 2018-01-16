#pragma once

#include "IwEngine\System.h"
#include "IwEngine\Collider.h"
#include "IwEngine\Transform.h"

template<>
class IWENGINE_API System<Collider, Transform> : public ISystem {
	virtual void Update(ComponentLookUp& componentLookUp, float deltaTime);
private:
	void Print(RigidBody* object1, RigidBody* object2);
};