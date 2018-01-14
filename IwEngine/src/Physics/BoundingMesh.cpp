#include "IwEngine\Physics\BoundingMesh.h"
#include "IwEngine\Math\Quaternion.h"
#include <vector>

using namespace Physics;

BoundingMesh::BoundingMesh(Math::Vector3* collider, uint count)
	: _collider(collider), _count(count) {}

BoundingMesh::~BoundingMesh() {
	delete[] _collider;
}

std::vector<Math::Vector3> Physics::BoundingMesh::GetAxies(const Bounds & other) const {
	return std::vector<Math::Vector3>();
}

std::vector<Math::Vector3> Physics::BoundingMesh::GetNormals() const {
	return std::vector<Math::Vector3>();
}

std::vector<Math::Vector3> Physics::BoundingMesh::GetVertices() const {
	return std::vector<Math::Vector3>();
}

std::vector<float> Physics::BoundingMesh::ProjectOntoAxis(const Math::Vector3& axis) const {
	return std::vector<float>();
}
