#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Physics\CollisionMesh.h"
#include "Physics\BoundingSphere.h"

class SphereCollider : public Component {
private:
	Physics::BoundingSphere _collider;
public:
	SphereCollider(GameObject& gameObject, Physics::BoundingSphere _collider)
		: Component(gameObject), _collider(_collider) {}
};