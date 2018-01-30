#pragma once

#include "IwEngine\Physics\CollisionData.h"
#include "IwEngine\Physics\Bounds.h"

namespace Physics {
	struct CollisionTransformation {
		const math::vector3& pos1;
		const math::vector3& pos2;
		const math::quaternion& rot1;
		const math::quaternion& rot2;
	};

	void ColliderGJK(
		const Bounds& bounds1, 
		const Bounds& bounds2, const CollisionTransformation& collisionTrans);
	math::vector3 Support(const Bounds& bounds1, const Bounds& bounds2, const math::vector3& direction, const CollisionTransformation& collisionTrans);
	math::vector3 Simplex(const math::vector3& a, const math::vector3& b);
	math::vector3 Simplex(const math::vector3& a, const math::vector3& b, const math::vector3& c);
	math::vector3 Simplex(const math::vector3& a, const math::vector3& b, const math::vector3& c, const math::vector3& d);
}