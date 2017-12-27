#pragma once

#include "IwEngine\Common.h"
#include "Physics\Physics.h"
#include "Math\Math.h"

class IWENGINE_API MeshCollider {

public:
	MeshCollider(int count) {
		Math::Vector3* collider = new Math::Vector3[count];
	}
};