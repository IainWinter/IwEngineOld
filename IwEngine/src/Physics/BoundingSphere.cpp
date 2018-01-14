#include "IwEngine\Physics\BoundingSphere.h"

using namespace Physics;

BoundingSphere::BoundingSphere(Math::Vector3& center, float radius)
	: BoundingMesh(new Math::Vector3[2]{ center, center + radius }, 2) {}