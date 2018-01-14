#include "IwEngine\Physics\BoundingBox.h"

Physics::BoundingBox::BoundingBox(const Math::Vector3& origin, const Math::Vector3& scale)
	: BoundingMesh(new Math::Vector3[36]{
	//left
	Math::Vector3(origin.x,				origin.y,			  origin.z),
	Math::Vector3(origin.x,				origin.y + scale.y,   origin.z),
	Math::Vector3(origin.x,				origin.y + scale.y,   origin.z + scale.z),
	Math::Vector3(origin.x,				origin.y + scale.y,   origin.z + scale.z),
	Math::Vector3(origin.x,				origin.y,			  origin.z + scale.z),
	Math::Vector3(origin.x,				origin.y,			  origin.z),

	//right
	Math::Vector3(origin.x + scale.x,	origin.y,			  origin.z),
	Math::Vector3(origin.x + scale.x,	origin.y + scale.y,   origin.z),
	Math::Vector3(origin.x + scale.x,	origin.y + scale.y,   origin.z + scale.z),
	Math::Vector3(origin.x + scale.x,	origin.y + scale.y,   origin.z + scale.z),
	Math::Vector3(origin.x + scale.x,	origin.y,			  origin.z + scale.z),
	Math::Vector3(origin.x + scale.x,	origin.y,			  origin.z),

	//bottom
	Math::Vector3(origin.x,				origin.y,			  origin.z),
	Math::Vector3(origin.x + scale.x,	origin.y,			  origin.z),
	Math::Vector3(origin.x + scale.x,	origin.y,			  origin.z + scale.z),
	Math::Vector3(origin.x + scale.x,	origin.y,			  origin.z + scale.z),
	Math::Vector3(origin.x,				origin.y,			  origin.z + scale.z),
	Math::Vector3(origin.x,				origin.y,			  origin.z),

	//top
	Math::Vector3(origin.x,				origin.y + scale.y,   origin.z),
	Math::Vector3(origin.x + scale.x,	origin.y + scale.y,   origin.z),
	Math::Vector3(origin.x + scale.x,	origin.y + scale.y,   origin.z + scale.z),
	Math::Vector3(origin.x + scale.x,	origin.y + scale.y,   origin.z + scale.z),
	Math::Vector3(origin.x,				origin.y + scale.y,   origin.z + scale.z),
	Math::Vector3(origin.x,				origin.y + scale.y,   origin.z),

	//back
	Math::Vector3(origin.x,				origin.y,			  origin.z),
	Math::Vector3(origin.x + scale.x,	origin.y,			  origin.z),
	Math::Vector3(origin.x + scale.x,	origin.y + scale.y,   origin.z),
	Math::Vector3(origin.x + scale.x,	origin.y + scale.y,   origin.z),
	Math::Vector3(origin.x,				origin.y + scale.y,   origin.z),
	Math::Vector3(origin.x,				origin.y,			  origin.z),

	//front
	Math::Vector3(origin.x,				origin.y,			  origin.z + scale.z),
	Math::Vector3(origin.x + scale.x,	origin.y,			  origin.z + scale.z),
	Math::Vector3(origin.x + scale.x,	origin.y + scale.y,   origin.z + scale.z),
	Math::Vector3(origin.x + scale.x,	origin.y + scale.y,   origin.z + scale.z),
	Math::Vector3(origin.x,				origin.y + scale.y,   origin.z + scale.z),
	Math::Vector3(origin.x,				origin.y,			  origin.z + scale.z)}, 36) {
}