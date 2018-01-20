#pragma once
#include <tuple>
#include "IwEngine\Common.h"
#include "Physics\CollisionDetectionMode.h"
#include "Physics\PhysicsMaterial.h"
#include "IwEngine\Math\Vector3.h"
#include "Component.h"

class RigidBody: public Component {
public:
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
	Physics::CollisionDetectionMode collision_detection_mode;

	RigidBody(GameObject& gameObject, float mass, float momentOfInertia, float drag, bool use_gravity, Math::Vector3 velocity, Math::Vector3 rotationalVelocity)
		: Component(gameObject), mass(mass), velocity(velocity), rotationalVelocity(rotationalVelocity), momentOfInertia(momentOfInertia), use_gravity(use_gravity), drag(drag) {
	}

};