#pragma once

#include "System.h"
#include "IwEngine\RenderMeshComponent.h"

template<>
class System<RenderMeshComponent> : public Events::Observer<float> {
private:
	std::vector<RenderMeshComponent> _transformComponents;
public:
	System() {
		_transformComponents = std::vector<RenderMeshComponent>();
	}

	void Update(const float& deltaTime) {
		Utility::Debug("Update all RenderMeshComponents");
	}
};
