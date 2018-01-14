#pragma once

#include "IwEngine\Common.h"

namespace Physics {
	struct IWENGINE_API CollisionData {
		bool intersects;
		float distance;
		CollisionData(bool intersects, float distance)
			: intersects(intersects), distance(distance) {}
	};
}