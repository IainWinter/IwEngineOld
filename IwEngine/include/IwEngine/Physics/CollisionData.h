#pragma once

#include "IwEngine\Common.h"
#include "IwMath\vector3.h"

namespace Physics {
	struct IWENGINE_API CollisionData {
		math::vector3 axis;
		bool intersects;
		float distance;
		CollisionData(math::vector3& axis, bool intersects, float distance)
			: axis(axis),
			intersects(intersects),
			distance(distance) {}
	};
}