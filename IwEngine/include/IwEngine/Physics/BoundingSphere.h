#pragma once

#include "IwEngine\Math\Vector3.h"
#include "IwEngine\Physics\Bounds.h"

namespace Physics {
	struct IWENGINE_API BoundingSphere : public Bounds {
	private:
		Math::Vector3* _center;
		float _radius;
	public:
		BoundingSphere(Math::Vector3& center, float radius);
		virtual ~BoundingSphere();
		virtual std::vector<Math::Vector3> GetAxies() const;
		virtual std::vector<Math::Vector3> GetVertices() const;
		virtual void ProjectOntoAxis(const Math::Vector3& axis, const Math::Quaternion& rotation, const Math::Vector3 offset, float& min, float& max) const;
		virtual float GetVolume() const;
	};
}