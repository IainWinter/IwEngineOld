#include "IwEngine\Physics\BoundingBox.h"
#include "IwMath\mathf.h"

using namespace Physics;

#define VERT_COUNT 8

BoundingBox::BoundingBox(const math::vector3& origin, const math::vector3& scale)
	: _scale(new math::vector3(scale)), _vertices(new math::vector3[VERT_COUNT]{
		math::vector3(origin),
		math::vector3(origin.x,			   origin.y + scale.y,  origin.z),
		math::vector3(origin.x,			   origin.y + scale.y,  origin.z + scale.z),
		math::vector3(origin.x,			   origin.y,			origin.z + scale.z),
		math::vector3(origin.x + scale.x,  origin.y,			origin.z + scale.z),
		math::vector3(origin.x + scale.x,  origin.y + scale.y,  origin.z + scale.z),
		math::vector3(origin.x + scale.x,  origin.y + scale.y,  origin.z),
		math::vector3(origin.x + scale.x,  origin.y,			origin.z)
}) {
}

BoundingBox::~BoundingBox() {
	delete[] _vertices;
}

math::vector3 BoundingBox::GetSupport(const math::vector3& direction, const math::quaternion& rotation, const math::vector3& position) const {
	math::vector3 maxVert;
	float max = -std::numeric_limits<float>::max(); //min gives e

	for (size_t i = 0; i < VERT_COUNT; i++) {
		math::vector3 vert = _vertices[i] * rotation + position;
		float d = vert.dot(direction);
		if (d > max) {
			max = d;
			maxVert = vert;
		}
	}

	return maxVert;
}

float BoundingBox::GetVolume() const {
	return abs(_scale->x) * abs(_scale->y) * abs(_scale->z);
}
