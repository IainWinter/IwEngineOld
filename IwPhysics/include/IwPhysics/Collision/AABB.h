#pragma once

#include "..\iwphysics.h"
#include "IwMath\vector3.h"

namespace iwphysics {
	struct IWPHYSICS_API AABB {
		iwmath::vector3 min;
		iwmath::vector3 max;

		AABB();
		AABB(iwmath::vector3 center, iwmath::vector3 scale);

		bool intersects(const AABB& other) const;
		bool fits(const AABB& other) const;
		iwmath::vector3 mid() const;
	};
}
