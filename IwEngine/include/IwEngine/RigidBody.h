#pragma once
#include <tuple>
#include "IwEngine\Common.h"
#include "Physics\CollisionDetectionMode.h"
#include "Physics\PhysicsMaterial.h"
#include "IwEngine\Math\Vector3.h"
#include "Component.h"

class RigidBody: public Component {
public:
	IWENGINE_API RigidBody(GameObject& gameObject)
		: Component(gameObject) {
	}
	RigidBody(GameObject& gameObject, float mass)
		: Component(gameObject), mass(mass) {}

	Math::Vector3 velocity;
	Math::Vector3 rotationalVelocity;
	Math::Vector3 torque;
	Math::Vector3 force; 

	float mass;
	float momentOfInertia;
	float drag;
	float angular_drag;
	bool use_gravity;
	bool is_kinematic;
	Physics::PhysicsMaterial material;
	Physics::CollisionDetectionMode collision_detection_mode;
	std::tuple<bool, bool, bool> freeze_position_xyz;
	std::tuple<bool, bool, bool> freeze_rotation;
};