#pragma once

#include "System.h"
#include "IwEngine\CollisionMeshComponent.h"

template<>
class System<CollisionMeshComponent> : public Events::Observer<float> {
private:
	std::vector<CollisionMeshComponent> _transformComponents;
public:
	System() {
		_transformComponents = std::vector<CollisionMeshComponent>();
	}

	void Update(const float& deltaTime) {
		Utility::Debug("Update all transforms");
	}
};
