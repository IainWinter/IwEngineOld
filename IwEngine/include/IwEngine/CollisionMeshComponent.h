#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Physics\MeshCollider.h"

class CollisionMeshComponent : public Component {
private:
	Physics::MeshCollider _collider;
public:
	CollisionMeshComponent(GameObject& gameObject, Physics::MeshCollider _collider) : Component(gameObject), _collider(_collider) { }
};