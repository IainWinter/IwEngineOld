#pragma once

#include "IwEngine\Component.h"
#include "IwEngine\Physics\BoundingMesh.h"

class Collider : public Component {
private:
	Physics::Bounds* _mesh;
public:
	Collider(GameObject& gameObject, Physics::Bounds* mesh) 
		: Component(gameObject), _mesh(mesh) {}
	
	~Collider() {
		delete _mesh;
	}

	inline const Physics::Bounds& GetCollider() const {
		return *_mesh;
	}
};