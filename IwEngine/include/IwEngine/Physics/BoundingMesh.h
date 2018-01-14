#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Math\Vector3.h"
#include "IwEngine\Physics\CollisionData.h"
#include "IwEngine\Transform.h"

namespace Physics {
	class IWENGINE_API BoundingMesh {
		Math::Vector3* _collider;
	public:
		BoundingMesh(Math::Vector3* collider);
		~BoundingMesh();

		inline const Math::Vector3* GetCollider() const {
			return _collider;
		}

		CollisionData Intersects(const BoundingMesh& other, const Transform* transform, const Transform* otherTransform) const;
	};
}