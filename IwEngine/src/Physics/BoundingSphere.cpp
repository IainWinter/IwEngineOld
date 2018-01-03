#pragma once

#include "IwEngine\Physics\BoundingSphere.h"

using namespace Physics;

CollisionData BoundingSphere::IntersectBS(const BoundingSphere& other) const {
	float radiusLength = radius + other.radius;
	float centerDistance = (center + other.center).Length();

	bool intersects = centerDistance < radiusLength;

	return CollisionData(intersects, centerDistance - radiusLength);
}