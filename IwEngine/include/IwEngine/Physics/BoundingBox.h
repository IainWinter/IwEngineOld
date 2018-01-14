#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Math\Vector3.h"
#include "IwEngine\Physics\Bounds.h"

namespace Physics {
	struct IWENGINE_API BoundingBox : public Bounds {
	private:
		Math::Vector3* _min;
		Math::Vector3* _max;
	public:
		BoundingBox(const Math::Vector3& origin, const Math::Vector3& scale);
		~BoundingBox();
		virtual std::vector<Math::Vector3> GetAxies(const Bounds& other) const;
		virtual std::vector<Math::Vector3> GetNormals() const;
		virtual std::vector<Math::Vector3> GetVertices() const;
		virtual std::vector<float> ProjectOntoAxis(const Math::Vector3& axis) const;
	};
}