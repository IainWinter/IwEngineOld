#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Math\Vector3.h"
#include "IwEngine\Physics\Bounds.h"

namespace Physics {
	struct IWENGINE_API BoundingBox : public Bounds {
	private:
		Math::Vector3* _vertices;
		Math::Vector3* _scale;
	public:
		BoundingBox(const Math::Vector3& origin, const Math::Vector3& scale);
		~BoundingBox();
		Math::Vector3 GetSupport(const Math::Vector3& direction, const Math::Quaternion& rotation) const;
		float GetVolume() const;

		inline const Math::Vector3& GetMin() const {
			return _vertices[0];
		}

		inline const Math::Vector3& GetMax() const {
			return _vertices[5];
		}
	};
}