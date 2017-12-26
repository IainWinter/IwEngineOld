#pragma once
#include "IwEngine\Common.h"

namespace Physics {
	struct IWENGINE_API PhysicsMaterial {
	public:
		float coef_static_friction;
		float coef_kinetic_friction;
		float elasticity;
		enum FrictionCombine;
		enum BounceCombine;
	};
}