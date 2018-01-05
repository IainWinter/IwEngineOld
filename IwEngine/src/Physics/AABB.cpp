#pragma once 

#include "IwEngine\Physics\CollisionData.h"
#include "IwEngine\Math\Vector3.h"
#include "IwEngine\Physics\CollisionData.h"
#include "IwEngine\Physics\AABB.h"

using namespace Physics;

CollisionData AABB::IntersectAABB(const AABB& other) const {
	Math::Vector3 distance1 = other.GetMin() - GetMax();
	Math::Vector3 distance2 = GetMin() - other.GetMax();

	Math::Vector3 distance;
	float max_distance;

	if (distance1.LengthFast() > distance2.LengthFast()) {
		distance = distance1 - distance2;
		max_distance = distance1.LengthFast();
	} else {
		distance = distance2 - distance1;
		max_distance = distance2.LengthFast();
	}

	return CollisionData(max_distance < 0, max_distance);
}