#pragma once

#include <vector>
#include "IwEngine\Transform.h"
#include "IwEngine\Events\Observer.h"

template<typename TComponent>
class System;

template<>
class System<Transform> : public Events::Observer<float> {
private:
	std::vector<Transform> _transformComponents;
public:
	System() {
		_transformComponents = std::vector<Transform>();
	}

	void Update(const float& deltaTime) {
		Utility::Debug("Update all transforms");
	}
};
