#pragma once

#include "IwEngine\System.h"
#include "IwEngine\Rigidbody.h"
#include "IwEngine\Transform.h"

template<>
class IWENGINE_API System<RigidBody, Transform> : public ISystem {
	virtual void Update(ComponentLookUp& componentLookUp, float deltaTime);
};
