#pragma once
#include "IwEngine\Common.h"
#include "IwEngine\Math\Math.h"

namespace Physics {
	struct IWENGINE_API AABB {
		Math::Vector3 max;
		Math::Vector3 min; 
	};
}