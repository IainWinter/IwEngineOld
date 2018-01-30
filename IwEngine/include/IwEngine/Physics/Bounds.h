#pragma once

#include "IwEngine\Common.h"
#include "IwMath\vector3.h"
#include "IwMath\matrix4.h"
#include <vector>

namespace Physics {
	class IWENGINE_API Bounds {
	public:
		virtual ~Bounds() {}
		virtual math::vector3 GetSupport(const math::vector3& direction, const math::quaternion& rotation, const math::vector3& position) const = 0;
		virtual float GetVolume() const = 0;
	};
}