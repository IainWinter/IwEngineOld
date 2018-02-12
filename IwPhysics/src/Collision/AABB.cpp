#include "IwPhysics\Collision\AABB.h"

iwphysics::AABB::AABB() 
	: min(0), max(0) {}

iwphysics::AABB::AABB(iwmath::vector3 center, iwmath::vector3 scale)
	: min(center - scale / 2), max(center + scale / 2) {}

bool iwphysics::AABB::intersects(const AABB& other) const {
	return (min.x <= other.max.x && min.x >= other.max.x) &&
		   (min.y <= other.max.y && min.y >= other.max.y) &&
		   (min.z <= other.max.z && min.z >= other.max.z);
}

bool iwphysics::AABB::fits(const AABB& other) const {
	return (min.x < other.min.x && max.x > other.max.x) &&
		   (min.y < other.min.y && max.y > other.max.y) &&
		   (min.z < other.min.z && max.z > other.max.z);
}

iwmath::vector3 iwphysics::AABB::mid() const {
	return (min + max) / 2;
}
