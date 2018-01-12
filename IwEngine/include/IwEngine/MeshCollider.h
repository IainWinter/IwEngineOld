#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Physics\BoundingMesh.h"

class MeshCollider : public Component {
private:
	Physics::BoundingMesh _collider;
public:
	MeshCollider(GameObject& gameObject, Physics::BoundingMesh _collider) 
		: Component(gameObject), _collider(_collider) {}
};