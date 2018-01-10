#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Physics\CollisionMesh.h"

class MeshCollider : public Component {
private:
	Physics::CollisionMesh _collider;
public:
	MeshCollider(GameObject& gameObject, Physics::CollisionMesh _collider) 
		: Component(gameObject), _collider(_collider) {}
};