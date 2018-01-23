#pragma once

#include "IwEngine\Physics\CollisionData.h"
#include "IwEngine\Physics\Bounds.h"

namespace Physics {
	CollisionData ColliderGJK(
		const Bounds& bounds1, 
		const Bounds& bounds2, 
		const Math::Vector3& pos1, 
		const Math::Vector3& pos2, 
		const Math::Quaternion& rot1, 
		const Math::Quaternion& rot2);
	Math::Vector3 Support(const Bounds& bounds1, const Bounds& bounds2, const Math::Vector3& direction);
	Math::Vector3 Simplex(const Math::Vector3& a, const Math::Vector3& b);
	Math::Vector3 Simplex(const Math::Vector3& a, const Math::Vector3& b, const Math::Vector3& c);
	Math::Vector3 Simplex(const Math::Vector3& a, const Math::Vector3& b, const Math::Vector3& c, const Math::Vector3& d);
}