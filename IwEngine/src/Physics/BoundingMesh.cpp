#include "IwEngine\Physics\BoundingMesh.h"

using namespace Physics;

BoundingMesh::BoundingMesh(int count) {
}

BoundingMesh::~BoundingMesh() {
}

CollisionData BoundingMesh::Intersects(const BoundingMesh& other, const Math::Vector3& offset, const Math::Vector3& otherOffset) {
	return CollisionData(false, 0);
}
