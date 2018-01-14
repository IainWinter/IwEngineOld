#include "IwEngine\Physics\BoundingMesh.h"
#include "IwEngine\Math\Quaternion.h"

using namespace Physics;

BoundingMesh::BoundingMesh(Math::Vector3* collider) 
	: _collider(collider) { }

BoundingMesh::~BoundingMesh() {
	delete _collider;
}

CollisionData BoundingMesh::Intersects(const BoundingMesh& other, const Transform* transform, const Transform* otherTransform) const {
	CollisionData collisionData = CollisionData(true, 0);

	const Math::Vector3* verts1 = GetCollider();

	const Math::Vector3& a = verts1[0];
	const Math::Vector3& b = verts1[1];

	Math::Vector3 line = b - a;
	Math::Vector3 axis = line * Math::Quaternion::FromAxisAngle(line, 90);


	//Find axies. If circle axis is from closest point to center of the circle
	//Remove similar ones
	//Project verticies on axis
	//Find if overlapping
	//Repeat for all axies
	return collisionData;
}