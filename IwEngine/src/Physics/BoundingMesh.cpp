#include "IwEngine\Physics\BoundingMesh.h"
#include "IwEngine\Math\Quaternion.h"
#include <vector>

using namespace Physics;

BoundingMesh::BoundingMesh(Math::Vector3* collider, uint count)
	: _collider(collider), _count(count) {
}

BoundingMesh::~BoundingMesh() {
	delete[] _collider;
}

CollisionData BoundingMesh::Intersects(const BoundingMesh& other, const Transform* transform, const Transform* otherTransform) const {
	CollisionData collisionData = CollisionData(true, 0);


	//Find axies. If circle axis is from closest point to center of the circle
	//Remove similar ones
	//Project verticies on axis
	//Find if overlapping
	//Repeat for all axies
	return collisionData;
}