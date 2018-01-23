#pragma once

#include "IwEngine\Math\Vector3.h"
#include "IwEngine\Physics\Bounds.h"

namespace Physics {
	struct IWENGINE_API BoundingSphere : public Bounds {
	private:
		Math::Vector3* _center;
		float _radius;
	public:
		BoundingSphere(Math::Vector3& center, float radius);
		~BoundingSphere();
		Math::Vector3 GetSupport(const Math::Vector3& direction, const Math::Quaternion& rotation) const;
		float GetVolume() const;
	};
}