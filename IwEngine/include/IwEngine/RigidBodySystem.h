#pragma once

#include "IwEngine\System.h"
#include "IwEngine\Rigidbody.h"
#include "IwEngine\Transform.h"
#include "IwEngine\Collider.h"


template<>
class IWENGINE_API System<RigidBody, Transform> : public ISystem {
	virtual void Update(ComponentLookUp& componentLookUp, float deltaTime);
	void checkGravity(RigidBody* rigidbody);
	void drag(RigidBody* rigidbody, Collider* collider);
	void motion(RigidBody* rigidbody, Transform* transform, Math::Vector3 position, float deltaTime);
	void rotate(RigidBody* rigidbody, Transform* transform, float deltaTime); 
};
