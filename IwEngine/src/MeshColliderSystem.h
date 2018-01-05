#pragma once

#include "System.h"
#include "IwEngine\MeshCollider.h"

template<>
class System<MeshCollider> : public Events::Observer<float> {
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
				float distance = meshcolliders.at(i).GetDistance;
			}
		 }
	}
};
