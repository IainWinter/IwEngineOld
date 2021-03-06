#pragma once

#include "collider.h"

namespace iwphysics {
	class IWPHYSICS_API boxCollider : public collider {
	private:
		iwmath::vector3 m_min;
		iwmath::vector3 m_max;
	public:
		boxCollider(const iwmath::vector3 center, const iwmath::vector3 scale);

		iwmath::vector3 support(const iwmath::vector3& direction, const iwmath::vector3& position, const iwmath::quaternion& rotation);
		float volume();
	};
}