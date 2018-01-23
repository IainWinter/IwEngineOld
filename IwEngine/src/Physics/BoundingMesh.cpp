#include "IwEngine\Physics\BoundingMesh.h"
#include "IwEngine\Math\Quaternion.h"
#include <vector>

using namespace Physics;

BoundingMesh::BoundingMesh(Math::Vector3* collider, uint count)
	: _collider(collider), _count(count) {}

BoundingMesh::~BoundingMesh() {
	delete[] _collider;
}

std::vector<Math::Vector3> Physics::BoundingMesh::GetNormals() const {
	return std::vector<Math::Vector3>();
}

std::vector<Math::Vector3> Physics::BoundingMesh::GetVertices() const {
	return std::vector<Math::Vector3>();
}

Math::Vector3 Physics::BoundingMesh::GetSupport(const Math::Vector3& direction, const Math::Quaternion& rotation, const Math::Vector3& position) const {
	return Math::Vector3();
}

float Physics::BoundingMesh::GetVolume() const {
	return 0.0f;
}