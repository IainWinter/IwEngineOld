#pragma once
#include "IwEngine\Common.h"
#include "IwEngine\Math\Math.h"

namespace Physics {
	struct IWENGINE_API AABB {
		Math::Vector2 max;
		Math::Vector2 min; 
	};
}