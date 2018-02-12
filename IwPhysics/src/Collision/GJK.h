#pragma once

#include "IwPhysics\iwphysics.h"
#include "IwPhysics\Collision\collider.h"
#include "IwMath\vector3.h"

namespace iwphysics {
	struct collision_transformation {
		transformation transformation1;
		transformation transformation2;
	};

	struct collision_data {
		
	};

	collision_data* GJK(
		const collider& bounds1,
		const collider& bounds2, const collision_transformation& collisionTrans);

	//Furthest point in a direction
	iwmath::vector3 support(const collider& bounds1, const collider& bounds2, 
		const collision_transformation& collisionTrans, const iwmath::vector3& direction);
	
	//Line
	iwmath::vector3 simplex(const iwmath::vector3& a, const iwmath::vector3& b);
	
	//Triangle
	iwmath::vector3 simplex(const iwmath::vector3& a, const iwmath::vector3& b, 
		const iwmath::vector3& c);
	
	//Trapazoid
	iwmath::vector3 simplex(const iwmath::vector3& a, const iwmath::vector3& b, 
		const iwmath::vector3& c, const iwmath::vector3& d);
}