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
		~BoundingMesh();
		Math::Vector3 GetSupport(const Math::Vector3& direction, const Math::Quaternion& rotation, const Math::Vector3& position) const;
		float GetVolume() const;
		std::vector<Math::Vector3> GetNormals() const;
		std::vector<Math::Vector3> GetVertices() const;
	};
}