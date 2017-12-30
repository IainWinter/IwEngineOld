#pragma once 
#include "IwEngine\Physics\Physics.h"

Physics::CollisionData Physics::BoundingSphere::IntersectBS(const BoundingSphere& other) 
{
	float radiusLength = radius + other.radius; 
	float centerDistance = (center + other.center).Length();

	if (centerDistance < radiusLength)
	{
		CollisionData(true, centerDistance - radiusLength);
	}
	else
	{
		CollisionData(false, centerDistance - radiusLength);
	}
}