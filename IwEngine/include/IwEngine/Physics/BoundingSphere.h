#pragma once

#include "IwEngine\Math\Vector3.h"
#include "CollisionData.h"

namespace Physics {
	class IWENGINE_API BoundingSphere {
	private:
		Math::Vector3 center;
		float radius;
	public:
		BoundingSphere(Math::Vector3& cen, float rad) {
			center.Equals(cen);
			radius = rad;
		};

		CollisionData IntersectBS(const BoundingSphere& other) const;

		Math::Vector3 GetCenter() {
			return center;
		}

		float GetRadius() {
			return radius;
		}
	};
}