#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Math\Vector3.h"
#include "IwEngine\Physics\CollisionData.h"
#include "IwEngine\Transform.h"

namespace Physics {
	class IWENGINE_API BoundingMesh {
		Math::Vector3* _collider;
		uint _count;
	public:
		BoundingMesh(Math::Vector3* collider, uint count);
		~BoundingMesh();

		inline const Math::Vector3* GetCollider() const {
			return _collider;
		}

		inline uint GetCount() const {
			return _count;
		}

		CollisionData Intersects(const BoundingMesh& other, const Transform* transform, const Transform* otherTransform) const;
	};
}