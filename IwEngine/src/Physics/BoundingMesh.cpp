#include "IwEngine\Physics\BoundingMesh.h"
#include "IwEngine\Math\Quaternion.h"
#include <vector>

using namespace Physics;

BoundingMesh::BoundingMesh(Math::Vector3* collider, uint count)
	: _collider(collider), _count(count) {}

BoundingMesh::~BoundingMesh() {
	delete[] _collider;
}

std::vector<Math::Vector3> Physics::BoundingMesh::GetAxies() const {
	return std::vector<Math::Vector3>();
}

std::vector<Math::Vector3> Physics::BoundingMesh::GetVertices() const {
	return std::vector<Math::Vector3>();
}

void Physics::BoundingMesh::ProjectOntoAxis(const Math::Vector3& axis, const Math::Quaternion& rotation, const Math::Vector3 offset, float& min, float& max) const {
	min = 0;
	max = 0;
}

float Physics::BoundingMesh::GetVolume() const {
	return 0.0f;
}
