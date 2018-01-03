#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Math\Vector3.h"
#include "CollisionData.h"

namespace Physics {
	struct IWENGINE_API AABB {
	private:
		Math::Vector3 max;
		Math::Vector3 min;
	public:
		AABB(const Math::Vector3 min_ex, Math::Vector3 max_ex) {
			min = min_ex;
			max = max_ex;
		}

		inline const Math::Vector3 GetMin() const {
			return min;
		}

		inline const Math::Vector3 GetMax() const {
			return max;
		}

		CollisionData AABB::IntersectAABB(const AABB& other) const;
	};
}