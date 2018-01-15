#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Math\Vector3.h"
#include "IwEngine\Math\Matrix4.h"
#include <vector>

namespace Physics {
	class IWENGINE_API Bounds {
	public:
		virtual ~Bounds() {}
		virtual std::vector<Math::Vector3> GetAxies() const = 0;
		virtual std::vector<Math::Vector3> GetVertices() const = 0;
		virtual void ProjectOntoAxis(const Math::Vector3& axis, const Math::Quaternion& rotation, const Math::Vector3 offset, float& min, float& max) const = 0;
		virtual float GetVolume() const = 0;
	};
}