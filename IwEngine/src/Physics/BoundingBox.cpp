#include "IwEngine\Physics\BoundingBox.h"

Physics::BoundingBox::BoundingBox(const Math::Vector3& origin, const Math::Vector3& scale)
	:_min(new Math::Vector3(origin)), _max(new Math::Vector3(origin + scale)) {}

Physics::BoundingBox::~BoundingBox() {
	delete _min;
	delete _max;
}

std::vector<Math::Vector3> Physics::BoundingBox::GetAxies() const {
	return std::vector<Math::Vector3> {
		Math::Vector3::UnitX,
		Math::Vector3::UnitY,
		Math::Vector3::UnitZ
	};
}

std::vector<Math::Vector3> Physics::BoundingBox::GetVertices() const {
	return std::vector<Math::Vector3> {
		Math::Vector3(*_min),
		Math::Vector3(_min->x, _max->y,	_min->z),
		Math::Vector3(_min->x, _max->y, _max->z),
		Math::Vector3(_min->x, _min->y, _max->z),
		Math::Vector3(_max->x, _min->y,_max->z),
		Math::Vector3(_max->x, _max->y,_max->z),
		Math::Vector3(_max->x, _max->y,_min->z),
		Math::Vector3(_max->x, _min->y,_min->z)
	};
}

void Physics::BoundingBox::ProjectOntoAxis(const Math::Vector3& axis, const Math::Quaternion& rotation, const Math::Vector3 offset, float& min, float& max) const {
	std::vector<Math::Vector3> verts = GetVertices();
	size_t count = verts.size();

	min = std::numeric_limits<float>::max();
	max = -std::numeric_limits<float>::max();

	for (size_t i = 0; i < verts.size(); i++) {
		verts[i] = verts[i] * rotation + offset;
	}

	for (size_t i = 0; i < count; i++) {
		float projection = axis.Dot(verts[i]);
		if (min > projection) {
			min = projection;
		}

		if (max < projection) {
			max = projection;
		}
	}
}

float Physics::BoundingBox::GetVolume() const {
	return (*_max - *_min).x * (*_max - *_min).y * (*_max - *_min).z;
}
