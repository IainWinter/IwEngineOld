#pragma once
#include "CollisionDetectionMode.h"
#include <tuple>

class RigidBody {
public:
	float mass;
	float drag;
	float angular_drag;
	bool use_gravity;
	bool is_kinematic;
	CollisionDetectionMode collision_detection_mode;
	std::tuple<bool, bool, bool> freeze_position_xyz;
	std::tuple<bool, bool, bool> freeze_rotation;
};