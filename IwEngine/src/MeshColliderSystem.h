#pragma once

#include "System.h"
#include "IwEngine\MeshCollider.h"

template<>
class System<MeshCollider> : public Events::Observer<float> {
private:
	std::vector<MeshCollider> _transformComponents;
public:
	System() {
		_transformComponents = std::vector<MeshCollider>();
	}

	void Update(const float& deltaTime) {
		Utility::Debug("Update all transforms");
	}
};
