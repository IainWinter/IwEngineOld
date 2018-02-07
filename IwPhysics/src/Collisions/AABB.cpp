#include "IwPhysics\Collisions\AABB.h"

using namespace iwphysics;

AABB::AABB() 
	: min(0), max(0) {}

AABB::AABB(iwmath::vector3 min, iwmath::vector3 max)
	: min(min), max(max) {}

bool AABB::intersects(const AABB& other) const {
	return (min.x <= other.max.x && min.x >= other.max.x) &&
		   (min.y <= other.max.y && min.y >= other.max.y) &&
		   (min.z <= other.max.z && min.z >= other.max.z);
}
