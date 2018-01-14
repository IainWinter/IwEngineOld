#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Math\Vector3.h"
#include "IwEngine\Physics\BoundingMesh.h"

namespace Physics {
	struct IWENGINE_API BoundingBox : public BoundingMesh {
	public:
		BoundingBox(const Math::Vector3& origin, const Math::Vector3& scale);
	};
}