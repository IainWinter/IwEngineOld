#include "IwEngine\Physics\BoundingSphere.h"
#include <limits>

using namespace Physics;

Physics::BoundingSphere::BoundingSphere(math::vector3& center, float radius)
	: _center(new math::vector3(center)), _radius(radius) {
}

Physics::BoundingSphere::~BoundingSphere() {
	delete _center;
}

math::vector3 Physics::BoundingSphere::GetSupport(const math::vector3& direction, const math::quaternion& rotation, const math::vector3& position) const {
	return math::vector3();
}

float Physics::BoundingSphere::GetVolume() const {
	return 4.0f / 3.0f * 3.14f * _radius * _radius * _radius;
}