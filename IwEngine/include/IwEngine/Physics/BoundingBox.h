#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Math\Vector3.h"
#include "CollisionData.h"
#include "IwEngine\Physics\BoundingMesh.h"

namespace Physics {
	struct IWENGINE_API BoundingBox : public BoundingMesh {
	public:
		BoundingBox(Math::Vector3 origin, Math::Vector3 scale) 
			: BoundingMesh(new Math::Vector3[]{ 
			origin,
			Math::Vector3(origin.x,			  origin.y + scale.y, origin.z),
			Math::Vector3(origin.x,			  origin.y + scale.y, origin.z + scale.z),
			Math::Vector3(origin.x,			  origin.y,			  origin.z + scale.z),
			Math::Vector3(origin.x + scale.x, origin.y,			  origin.z),
			Math::Vector3(origin.x + scale.x, origin.y + scale.y, origin.z),
			Math::Vector3(origin.x + scale.x, origin.y + scale.y, origin.z + scale.z),
			Math::Vector3(origin.x + scale.x, origin.y,			  origin.z + scale.z)
		}) {}
	};
}