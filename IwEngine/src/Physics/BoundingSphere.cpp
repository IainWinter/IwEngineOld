#include "IwEngine\Physics\BoundingSphere.h"
#include <limits>

using namespace Physics;

Physics::BoundingSphere::BoundingSphere(Math::Vector3& center, float radius)
	: _center(new Math::Vector3(center)), _radius(radius) {
}

Physics::BoundingSphere::~BoundingSphere() {
	delete _center;
}

Math::Vector3 Physics::BoundingSphere::GetSupport(const Math::Vector3& direction, const Math::Quaternion& rotation) const {
	return Math::Vector3();
}

float Physics::BoundingSphere::GetVolume() const {
	return 4.0f / 3.0f * 3.14f * _radius * _radius * _radius;
}
