#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Physics\Physics.h"
#include "IwEngine\Math\Math.h"

namespace Physics {
	class IWENGINE_API MeshCollider {
	public:
		MeshCollider(int count) {
			Math::Vector3* _collider = new Math::Vector3[count];
		}
	};
}