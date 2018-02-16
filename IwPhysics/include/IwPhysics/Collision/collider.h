#pragma once

#include "IwPhysics\iwphysics.h"
#include "AABB.h"
#include "physics_material.h"
#include "IwMath\vector3.h"
#include "IwMath\quaternion.h"

namespace iwphysics {
	class IWPHYSICS_API collider {
	protected:
		AABB m_bounds;
		//physicsMaterial m_material;
		//bool m_isEnabled;
		//bool m_isTrigger;
	public:
		virtual iwmath::vector3 support(const iwmath::vector3& direction, const iwmath::vector3& position, const iwmath::quaternion& rotation) const = 0;
		virtual float volume() const = 0;

		inline const AABB& bounds() const {
			return m_bounds;
		}
	};
}
