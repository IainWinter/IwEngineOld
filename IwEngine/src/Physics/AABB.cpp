#pragma once 
#include "IwEngine\Physics\Physics.h"

Physics::CollisionData Physics::AABB::IntersectAABB(const AABB& other)
{
	Math::Vector3 distance1 = other.min - max;
	Math::Vector3 distance2 = min - other.max;
	Math::Vector3 distance;
	//Math::Vector3 = max distance1, distance2
}