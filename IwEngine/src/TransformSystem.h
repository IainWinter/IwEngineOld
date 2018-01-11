#pragma once

#include "System.h"
#include "IwEngine\Transform.h"

template<>
class System<Transform> {
public:
	System() {
		 _transformComponents = std::vector<Transform>();
	}

	void Update(const float& deltaTime) {
		Utility::Debug("Update all transforms");
	}
};
