#pragma once

#include "IwEngine\Common.h"
#include "IwMath\vector3.h"
#include "IwEngine\Physics\Bounds.h"

namespace Physics {
	class IWENGINE_API BoundingMesh : Bounds {
		math::vector3* _collider;
		uint _count;
	public:
		BoundingMesh(math::vector3* collider, uint count);
		~BoundingMesh();
		math::vector3 GetSupport(const math::vector3& direction, const math::quaternion& rotation, const math::vector3& position) const;
		float GetVolume() const;
		std::vector<math::vector3> GetNormals() const;
		std::vector<math::vector3> GetVertices() const;
	};
}