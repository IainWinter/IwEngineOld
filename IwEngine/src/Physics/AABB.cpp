#pragma once 
#include "IwEngine\Physics\Physics.h"

Physics::CollisionData Physics::AABB::IntersectAABB(const AABB& other)
{
	Math::Vector3 distance1 = other.min - max;
	Math::Vector3 distance2 = min - other.max;
	Math::Vector3 distance;
	float max_distance;
	if (distance1.LengthFast() > distance2.LengthFast())
	{
		distance = distance1 - distance2;
		max_distance = distance1.LengthFast();
	}
	else {
		distance = distance2 - distance1; 
		max_distance = distance2.LengthFast();
	}
	return CollisionData(max_distance < 0, max_distance);
}