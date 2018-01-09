#pragma once

#include "System.h"
#include "IwEngine\Physics\PhysicsHelper.h"
#include "IwEngine\RigidBody.h"

template<>
class System<RigidBody> : public Events::Observer<float> {
private:
	std::vector<RigidBody> _transformComponents;
public:
	System() {
		_transformComponents = std::vector<RigidBody>();
	}

	void Update(const float& deltaTime) {
		
	}

	void UpdatePosition(RigidBody object, float deltaTime)
	{
		
	}
};
