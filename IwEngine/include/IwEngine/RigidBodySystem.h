#pragma once

#include "IwEngine\System.h"
#include "IwEngine\Rigidbody.h"
#include "IwEngine\Transform.h"
#include "IwEngine\Physics\CollisionData.h"

template<>
class IWENGINE_API System<RigidBody, Transform> : public ISystem {
private:
	void CollisionResponce(RigidBody* rigidbody, RigidBody* other, const Physics::CollisionData* collisionData);
	virtual void Update(ComponentLookUp& componentLookUp, float deltaTime);
};
