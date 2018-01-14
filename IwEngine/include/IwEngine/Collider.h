#pragma once

#include "IwEngine\Component.h"
#include "IwEngine\Physics\BoundingMesh.h"

class Collider : public Component {
private:
	Physics::BoundingMesh* _mesh;
public:
	Collider(GameObject& gameObject, Physics::BoundingMesh* mesh) 
		: Component(gameObject), _mesh(mesh) {}
	
	~Collider() {
		delete _mesh;
	}

	inline const Physics::BoundingMesh& GetCollider() const {
		return *_mesh;
	}
};