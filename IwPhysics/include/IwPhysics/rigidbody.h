#pragma once

#include "iwphysics.h"
#include "IwMath\vector3.h"

namespace iwphysics {
	enum class IWPHYSICS_API collision_detection_mode {
		CONTINUOUS,
		DISCREAT
	};

	struct IWPHYSICS_API rigidbody_constraints {
		bool freeze_x;
		bool freeze_y;
		bool freeze_z;
		bool freeze_x_rotation;
		bool freeze_y_rotation;
		bool freeze_z_rotation;
	};

	class IWPHYSICS_API rigidbody {
	private:
		float mass;

		//Translational
		iwmath::vector3 velocity; //Velocity of rigidbody
		iwmath::vector3 force; //Net force on rigidody
		float drag; //Drag on rigidbody

		//Angular
		iwmath::vector3 angular_velocity; //Angular velocity in rad/sec
		iwmath::vector3 torque; //Torque on rigidbody
		iwmath::vector3 center_of_mass; //Center of mass in local space
		float angluar_drag; //Angular drag on rigidbody
		float moment_of_inertia; //Moment of inertia of rigidbody

		//Options
		bool use_gravity;
		bool is_kinematic;
		collision_detection_mode collision_detection_mode;
		rigidbody_constraints constrains;
	public:
	};
}
/*
What are properties of moving objects?

velocity
force -> gravity, friction, drag force
drag scale

angular velocity
angular force -> torque, angular friction, angular drag force
angular drag
center of mass
moment of inertia

options?
apply gravity
freeze roation
freeze movement
apply any dynamic properties?

*/