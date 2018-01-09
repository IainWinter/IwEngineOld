#pragma once

#include "System.h"
#include "IwEngine\MeshCollider.h"

template<>
class System<MeshCollider> : public Events::EventHandlerBase<float> {
private:
	std::vector<MeshCollider> meshcolliders;
public:
	System() {
		meshcolliders = std::vector<MeshCollider>();
	}

	void Update(const float& deltaTime) {
		Utility::Debug("Update all transforms");
		for (int i = 0; i < meshcolliders.size(); i++) {
			bool is_colliding = meshcolliders.at(i).GetIntersect;
			if (is_colliding)
			{
				//send collision data to event bus
			}
		 }
	}
};
