#include "IwEngine\Physics\BoundingSphere.h"
#include <limits>

using namespace Physics;

Physics::BoundingSphere::BoundingSphere(Math::Vector3& center, float radius)
	: _center(new Math::Vector3(center)), _radius(radius) {
}

Physics::BoundingSphere::~BoundingSphere() {
	delete _center;
}

std::vector<Math::Vector3> Physics::BoundingSphere::GetAxies() const {
	return std::vector<Math::Vector3>();
}

std::vector<Math::Vector3> Physics::BoundingSphere::GetVertices() const {
	return std::vector<Math::Vector3> { *_center };
}

void Physics::BoundingSphere::ProjectOntoAxis(const Math::Vector3& axis, const Math::Quaternion& rotation, const Math::Vector3 offset, float& min, float& max) const {
	min = 0;
	max = 0;
}

float Physics::BoundingSphere::GetVolume() const {
	return 4.0f / 3.0f * 3.14f * _radius * _radius * _radius;
}
