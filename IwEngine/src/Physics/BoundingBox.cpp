#include "IwEngine\Physics\BoundingBox.h"
#include "IwEngine\Math\MathHelper.h"

using namespace Physics;

#define VERT_COUNT 8

BoundingBox::BoundingBox(const Math::Vector3& origin, const Math::Vector3& scale)
	: _scale(new Math::Vector3(scale)), _vertices(new Math::Vector3[VERT_COUNT]{
		Math::Vector3(origin),
		Math::Vector3(origin.x,			   origin.y + scale.y,  origin.z),
		Math::Vector3(origin.x,			   origin.y + scale.y,  origin.z + scale.z),
		Math::Vector3(origin.x,			   origin.y,			origin.z + scale.z),
		Math::Vector3(origin.x + scale.x,  origin.y,			origin.z + scale.z),
		Math::Vector3(origin.x + scale.x,  origin.y + scale.y,  origin.z + scale.z),
		Math::Vector3(origin.x + scale.x,  origin.y + scale.y,  origin.z),
		Math::Vector3(origin.x + scale.x,  origin.y,			origin.z)
}) {
}

BoundingBox::~BoundingBox() {
	delete[] _vertices;
}

Math::Vector3 BoundingBox::GetSupport(const Math::Vector3& direction, const Math::Quaternion& rotation, const Math::Vector3& position) const {
	Math::Vector3 maxVert;
	float max = -std::numeric_limits<float>::max(); //min gives e

	for (size_t i = 0; i < VERT_COUNT; i++) {
		Math::Vector3 vert = _vertices[i] * rotation + position;
		float d = vert.Dot(direction);
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
