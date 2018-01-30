#pragma once
#include <tuple>
#include "IwEngine\Common.h"
#include "Physics\CollisionDetectionMode.h"
#include "Physics\PhysicsMaterial.h"
#include "IwMath\vector3.h"
#include "Component.h"

class RigidBody: public Component {
public:
	math::vector3 velocity;
	math::vector3 rotationalVelocity;
	math::vector3 torque;
	math::vector3 force; 

	float mass;
	float momentOfInertia;
	float drag;
	float angular_drag;
	bool use_gravity;
	bool is_kinematic;
	Physics::CollisionDetectionMode collision_detection_mode;

	RigidBody(GameObject& gameObject, float mass, float momentOfInertia, float drag, bool use_gravity, math::vector3 velocity, math::vector3 rotationalVelocity)
		: Component(gameObject), mass(mass), velocity(velocity), rotationalVelocity(rotationalVelocity), momentOfInertia(momentOfInertia), use_gravity(use_gravity), drag(drag) {
	}

};