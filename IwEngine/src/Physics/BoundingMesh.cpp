#include "IwEngine\Physics\BoundingMesh.h"
#include "IwMath\quaternion.h"
#include <vector>

using namespace Physics;

BoundingMesh::BoundingMesh(math::vector3* collider, uint count)
	: _collider(collider), _count(count) {}

BoundingMesh::~BoundingMesh() {
	delete[] _collider;
}

std::vector<math::vector3> Physics::BoundingMesh::GetNormals() const {
	return std::vector<math::vector3>();
}

std::vector<math::vector3> Physics::BoundingMesh::GetVertices() const {
	return std::vector<math::vector3>();
}

math::vector3 Physics::BoundingMesh::GetSupport(const math::vector3& direction, const math::quaternion& rotation, const math::vector3& position) const {
	return math::vector3();
}

float Physics::BoundingMesh::GetVolume() const {
	return 0.0f;
}