#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Physics\CollisionMesh.h"

class CollisionMesh : public Component {
private:
	Physics::CollisionMesh _collider;
public:
	CollisionMesh(GameObject& gameObject, Physics::CollisionMesh _collider) : Component(gameObject), _collider(_collider) { }
};