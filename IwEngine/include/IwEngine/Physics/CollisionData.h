#pragma once

#include "IwEngine\Common.h"

namespace Physics {
	class IWENGINE_API CollisionData {
	private:
		bool intersect;
		float distance;
	public:
		CollisionData(bool does_intersect, float dist) {
			intersect = does_intersect;
			distance = dist;
		}

		bool GetIntersect() {
			return intersect;
		}

		float GetDistance() {
			return distance;
		}
	};
}