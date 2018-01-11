#pragma once

#include "IwEngine\System.h"
#include "IwEngine\Rigidbody.h"
#include "IwEngine\Utility\Logger.h"

template<>
class IWENGINE_API System<RigidBody> : public ISystem {
	virtual void Update(ComponentLookUp& componentLookUp, float deltaTime);
};
