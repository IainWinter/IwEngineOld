#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Physics\FrictionCombine.h"
#include "IwEngine\Physics\BounceCombine.h"

namespace Physics {
	struct IWENGINE_API PhysicsMaterial {
	public:
		float coefStaticFriction;
		float coefKineticFriction;
		float elasticity;
		FrictionCombine frictionCombine;
		BounceCombine bounceCombine;

		PhysicsMaterial(float coefStaticFriction, float coefKineticFriction,
			float elasticity, FrictionCombine frictionCombine, BounceCombine bounceCombine)
			: coefStaticFriction(coefStaticFriction), 
			coefKineticFriction(coefKineticFriction), 
			elasticity(elasticity),
			frictionCombine(frictionCombine), 
			bounceCombine(bounceCombine) {}
	};
}