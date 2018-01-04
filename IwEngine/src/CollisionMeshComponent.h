#pragma once

#include "System.h"
#include "IwEngine\CollisionMesh.h"

template<>
class System<CollisionMesh> : public Events::Observer<float> {
private:
	std::vector<CollisionMesh> _transformComponents;
public:
	System() {
		_transformComponents = std::vector<CollisionMesh>();
	}

	void Update(const float& deltaTime) {
		Utility::Debug("Update all transforms");
	}
};
