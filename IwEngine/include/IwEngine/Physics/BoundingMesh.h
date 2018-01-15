#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Math\Vector3.h"
#include "IwEngine\Physics\Bounds.h"

namespace Physics {
	class IWENGINE_API BoundingMesh : Bounds {
		Math::Vector3* _collider;
		uint _count;
	public:
		BoundingMesh(Math::Vector3* collider, uint count);
		virtual ~BoundingMesh();
		virtual std::vector<Math::Vector3> GetAxies() const;
		virtual std::vector<Math::Vector3> GetVertices() const;
		virtual void ProjectOntoAxis(const Math::Vector3& axis, const Math::Quaternion& rotation, const Math::Vector3 offset, float& min, float& max) const;
		virtual float GetVolume() const;
	};
}