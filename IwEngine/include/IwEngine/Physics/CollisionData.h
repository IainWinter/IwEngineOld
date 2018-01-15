#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Math\Vector3.h"

class Collider;
namespace Physics {
	struct IWENGINE_API CollisionData {
		Collider* const collider1;
		Collider* collider2;
		Math::Vector3 axis;
		bool intersects;
		float distance;
		CollisionData(Collider* const collider1, Collider* collider2, Math::Vector3& axis, bool intersecting, float distance)
			: collider1(collider1),
			collider2(collider2),
			axis(axis),
			intersects(intersects),
			distance(distance) {}
	};
}