#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Math\Vector3.h"
#include "IwEngine\Physics\CollisionData.h"

namespace Physics {
	class IWENGINE_API BoundingMesh {
		Math::Vector3* _collider;
	public:
		BoundingMesh(int count);
		~BoundingMesh();

		virtual CollisionData Intersects(const BoundingMesh& other, const Math::Vector3& offset, const Math::Vector3& otherOffset);
	};
}