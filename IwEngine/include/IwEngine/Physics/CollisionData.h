#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Math\Vector3.h"

namespace Physics {
	struct IWENGINE_API CollisionData {
		Math::Vector3 axis;
		bool intersects;
		float distance;
		CollisionData(Math::Vector3& axis, bool intersects, float distance)
			: axis(axis),
			intersects(intersects),
			distance(distance) {}
	};
}