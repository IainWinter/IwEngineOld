#include "IwEngine\Physics\BoundingBox.h"

Physics::BoundingBox::BoundingBox(const Math::Vector3& origin, const Math::Vector3& scale)
	:_min(new Math::Vector3(origin)), _max(new Math::Vector3(origin + scale)) {}

Physics::BoundingBox::~BoundingBox() {
	delete _min;
	delete _max;
}

std::vector<Math::Vector3> Physics::BoundingBox::GetAxies(const Bounds& other) const {
	return GetNormals();
}

std::vector<Math::Vector3> Physics::BoundingBox::GetNormals() const {
	return std::vector<Math::Vector3> {
		Math::Vector3::UnitX,
		Math::Vector3::UnitY,
		Math::Vector3::UnitZ
	};
}

std::vector<Math::Vector3> Physics::BoundingBox::GetVertices() const {
	return std::vector<Math::Vector3> {
		*_min, 
		Math::Vector3(_min->x, _max->y,	_min->z),
		Math::Vector3(_min->x, _max->y, _max->z),
		Math::Vector3(_min->x, _min->y, _max->z),
		Math::Vector3(_max->x, _min->y,_max->z),
		Math::Vector3(_max->x, _max->y,_max->z),
		Math::Vector3(_max->x, _max->y,_min->z),
		Math::Vector3(_max->x, _min->y,_min->z)
	};
}

std::vector<float> Physics::BoundingBox::ProjectOntoAxis(const Math::Vector3& axis) const {
	return std::vector<float>();
}

float Physics::BoundingBox::GetVolume() {
	return (*_max - *_min).x *(*_max - *_min).y * (*_max - *_min).z;
}
