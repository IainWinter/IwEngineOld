#pragma once

#include "Collider.h"
#include "GameObject.h"
#include "Physics\BoundingBox.h"

class BoxCollider : public Collider {
private:
	Physics::BoundingBox _collider;
	std::vector <Math::Vector3> position;
public:
	BoxCollider(GameObject& gameObject, Physics::BoundingBox _collider)
		: Collider(gameObject), _collider(_collider) {}
};
