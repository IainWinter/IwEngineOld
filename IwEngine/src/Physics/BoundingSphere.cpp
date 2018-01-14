#include "IwEngine\Physics\BoundingSphere.h"
#include <limits>

using namespace Physics;

Physics::BoundingSphere::BoundingSphere(Math::Vector3* center, float radius)
	: _center(center), _radius(radius) {
}

Physics::BoundingSphere::~BoundingSphere() {
	delete _center;
}

std::vector<Math::Vector3> Physics::BoundingSphere::GetAxies(const Bounds& other) const {
	std::vector<Math::Vector3> otherVerts = other.GetVertices();
	size_t count = otherVerts.size();

	Math::Vector3 closestVert;
	float closestVertDistance = std::numeric_limits<float>::max();
	for (size_t i = 0; i < count; i++) {
		float distance = abs((otherVerts[i] - *_center).LengthSquared());
		if (distance < closestVertDistance) {
			closestVert = otherVerts[i];
			closestVertDistance = distance;
		}
	}

	Math::Vector3 axis = closestVert - *_center;

	return std::vector<Math::Vector3>{ axis };
}

std::vector<Math::Vector3> Physics::BoundingSphere::GetNormals() const {
	return std::vector<Math::Vector3>();
}

std::vector<Math::Vector3> Physics::BoundingSphere::GetVertices() const {
	return std::vector<Math::Vector3> { *_center };
}

std::vector<float> Physics::BoundingSphere::ProjectOntoAxis(const Math::Vector3& axis) const {
	return std::vector<float>(-_radius, _radius);
}

float Physics::BoundingSphere::GetVolume() const {
	return 4.0f / 3.0f * 3.14f * _radius * _radius * _radius;
}
