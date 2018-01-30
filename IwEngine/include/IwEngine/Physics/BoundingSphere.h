#pragma once

#include "IwMath\vector3.h"
#include "IwEngine\Physics\Bounds.h"

namespace Physics {
	struct IWENGINE_API BoundingSphere : public Bounds {
	private:
		math::vector3* _center;
		float _radius;
	public:
		BoundingSphere(math::vector3& center, float radius);
		~BoundingSphere();
		math::vector3 GetSupport(const math::vector3& direction, const math::quaternion& rotation, const math::vector3& position) const;
		float GetVolume() const;
	};
}