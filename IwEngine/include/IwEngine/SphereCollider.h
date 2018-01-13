#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Physics\BoundingSphere.h"
#include "Collider.h"


class SphereCollider : public Component {
private:
	Physics::BoundingSphere _collider;
	std::vector <Math::Vector3> points;
	float radius;

public:
	SphereCollider(GameObject& gameObject, Physics::BoundingSphere _collider)
		: Component(gameObject), _collider(_collider) {
		points.push_back(_collider.GetCenter());
		radius = _collider.GetRadius();
	}

	Physics::BoundingSphere GetCollider() {
		return _collider;
	}
};