#pragma once
#include <tuple>
#include "IwEngine\Common.h"
#include "Physics\CollisionDetectionMode.h"
#include "Physics\PhysicsMaterial.h"
#include "IwEngine\Math\Vector3.h"
#include "Component.h"

class IWENGINE_API RigidBody: public Component {
public:
	RigidBody(GameObject& gameObject)
		: Component(gameObject) {
	}

	Math::Vector3 velocity;
	Math::Vector3 acceleration;
	Math::Vector3 rotationalVelocity;
	Math::Vector3 rotationalAcceleration;

	float mass;
	float drag;
	float angular_drag;
	bool use_gravity;
	bool is_kinematic;
	Physics::PhysicsMaterial material;
	Physics::CollisionDetectionMode collision_detection_mode;
	std::tuple<bool, bool, bool> freeze_position_xyz;
	std::tuple<bool, bool, bool> freeze_rotation;
};