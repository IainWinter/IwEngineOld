#pragma once

#include "IwEngine\Component.h"
#include "IwEngine\Physics\BoundingMesh.h"

class Collider : public Component {
private:
	Physics::Bounds* _bounds;
public:
	Collider(GameObject& gameObject, Physics::Bounds* mesh) 
		: Component(gameObject), _bounds(mesh) {}
	
	~Collider() {
		delete _bounds;
	}

	inline const Physics::Bounds& GetCollider() const {
		return *_bounds;
	}

	inline float GetVolume() const {
		return _bounds->GetVolume();
	}
};