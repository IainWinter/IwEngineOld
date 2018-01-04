#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Physics\MeshCollider.h"

class CollisionMesh : public Component {
private:
	Physics::MeshCollider _collider;
public:
	CollisionMesh(GameObject& gameObject, Physics::MeshCollider _collider) : Component(gameObject), _collider(_collider) { }
};