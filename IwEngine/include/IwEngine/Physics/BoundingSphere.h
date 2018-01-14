#pragma once

#include "IwEngine\Math\Vector3.h"
#include "CollisionData.h"

namespace Physics {
	struct IWENGINE_API BoundingSphere : public BoundingMesh {
	public:
		BoundingSphere(Math::Vector3& center, float radius) 
			: BoundingMesh(new Math::Vector3[]{ center, center + radius }) {}
	};
}