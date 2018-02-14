#pragma once

#include "IwPhysics\iwphysics.h"
#include "collider.h"
#include "IwMath\vector3.h"

namespace iwphysics {
	class IWPHYSICS_API sphere_collider : public collider {
	private:
		iwmath::vector3 m_center;
		float m_radius;
	public:
		sphere_collider(iwmath::vector3 center, float radius);
		float volume() const;
		iwmath::vector3 support(
			const iwmath::vector3& direction,
			const iwmath::vector3& position,
			const iwmath::quaternion& rotation) const;
	};
}