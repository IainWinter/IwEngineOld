#include "IwPhysics\Collision\sphere_collider.h"
#include "IwMath\iwmath.h"

iwphysics::sphere_collider::sphere_collider(iwmath::vector3 center, float radius)
	: m_center(center), m_radius(radius) {}

float iwphysics::sphere_collider::volume() const {
	return 4.0f / 3.0f * PI * m_radius*m_radius;
}

iwmath::vector3 iwphysics::sphere_collider::support(
	const iwmath::vector3& direction, 
	const iwmath::vector3& position, 
	const iwmath::quaternion& rotation) const
{
	return direction.normalized_fast() * m_radius + m_center + position;
}
