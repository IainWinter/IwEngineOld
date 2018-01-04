#pragma once

#include "System.h"
#include "IwEngine\RenderMesh.h"

template<>
class System<RenderMesh> : public Events::Observer<float> {
private:
	std::vector<RenderMesh> _transformComponents;
public:
	System() {
		_transformComponents = std::vector<RenderMesh>();
	}

	void Update(const float& deltaTime) {
		Utility::Debug("Update all RenderMeshComponents");
	}
};
