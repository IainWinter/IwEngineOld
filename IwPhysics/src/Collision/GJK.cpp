#include "GJK.h"
#include <vector>

iwphysics::collision_data* iwphysics::GJK(
	const collider* bounds1, 
	const collider* bounds2,
	const collision_transformation& collisionTrans) 
{
	return new collision_data(bounds1, bounds2, iwmath::vector3());
}

iwmath::vector3 iwphysics::support(
	const collider& bounds1, 
	const collider& bounds2,
	const collision_transformation& collisionTrans,
	const iwmath::vector3& direction)
{
	return iwmath::vector3();
}

iwmath::vector3 iwphysics::simplex(
	const iwmath::vector3& a, 
	const iwmath::vector3& b) 
{
	return iwmath::vector3();
}

iwmath::vector3 iwphysics::simplex(
	const iwmath::vector3& a, 
	const iwmath::vector3& b, 
	const iwmath::vector3& c)
{
	return iwmath::vector3();
}

iwmath::vector3 iwphysics::simplex(
	const iwmath::vector3& a, 
	const iwmath::vector3& b,
	const iwmath::vector3& c, 
	const iwmath::vector3& d) 
{
	return iwmath::vector3();
}