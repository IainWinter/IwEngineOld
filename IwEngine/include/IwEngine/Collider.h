#pragma once

#include "IwEngine\Component.h"
#include "IwEngine\Physics\BoundingMesh.h"

class IWENGINE_API Collider : public Component {
private:
	Physics::BoundingMesh _mesh;
public:
	Collider(GameObject& gameObject, Physics::BoundingMesh mesh) : Component(gameObject), _mesh(mesh) {}

	inline const Physics::BoundingMesh& GetCollider() const {
		return _mesh;
	}
};