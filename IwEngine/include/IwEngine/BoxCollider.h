#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Physics\CollisionMesh.h"
#include "Physics\BoundingBox.h"

class BoxCollider : public Component {
private:
	Physics::BoundingBox _collider;
public:
	BoxCollider(GameObject& gameObject, Physics::BoundingBox _collider)
		: Component(gameObject), _collider(_collider) {}
};
