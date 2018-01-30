#pragma once

#include "IwEngine\Common.h"
#include "IwMath\vector3.h"
#include "IwEngine\Physics\Bounds.h"

namespace Physics {
	struct IWENGINE_API BoundingBox : public Bounds {
	private:
		math::vector3* _vertices;
		math::vector3* _scale;
	public:
		BoundingBox(const math::vector3& origin, const math::vector3& scale);
		~BoundingBox();
		math::vector3 GetSupport(const math::vector3& direction, const math::quaternion& rotation, const math::vector3& position) const;
		float GetVolume() const;

		inline const math::vector3& GetMin() const {
			return _vertices[0];
		}

		inline const math::vector3& GetMax() const {
			return _vertices[5];
		}
	};
}