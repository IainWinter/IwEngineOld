#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Math\Vector3.h"

namespace Physics {
	class IWENGINE_API PhysicsHelper {
	public:
		static Math::Vector3 gravity;
	};

	Math::Vector3 gravity(0, 9.81f, 0);
}