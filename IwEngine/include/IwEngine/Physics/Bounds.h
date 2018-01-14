#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Math\Vector3.h"
#include "IwEngine\Math\Matrix4.h"
#include <vector>

namespace Physics {
	class IWENGINE_API Bounds {
	public:
		virtual ~Bounds() {}
		virtual std::vector<Math::Vector3> GetAxies(const Bounds& other) const = 0;
		virtual std::vector<Math::Vector3> GetNormals() const = 0;
		virtual std::vector<Math::Vector3> GetVertices() const = 0;
		virtual std::vector<float> ProjectOntoAxis(const Math::Vector3& axis) const = 0;
	};
}