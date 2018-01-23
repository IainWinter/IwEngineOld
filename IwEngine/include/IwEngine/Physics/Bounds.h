#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Math\Vector3.h"
#include "IwEngine\Math\Matrix4.h"
#include <vector>

namespace Physics {
	class IWENGINE_API Bounds {
	public:
		virtual ~Bounds() {}
		virtual Math::Vector3 GetSupport(const Math::Vector3& direction, const Math::Quaternion& rotation) const = 0;
		virtual float GetVolume() const = 0;
	};
}