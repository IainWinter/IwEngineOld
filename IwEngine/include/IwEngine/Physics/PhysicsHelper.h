#pragma once

#include "IwEngine\Common.h"
#include "IwMath\vector3.h"

namespace Physics {
	class IWENGINE_API PhysicsHelper {
	public:
		static math::vector3 gravity;
	};

	math::vector3 gravity(0, -9.81f, 0);
}