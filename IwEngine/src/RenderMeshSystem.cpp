#include "IwEngine\RenderMeshSystem.h"
#include <vector>

void System<RenderMesh, Transform>::Update(ComponentLookUp& componentLookUp, float deltaTime) {
	Utility::Info(std::to_string(deltaTime));

	std::vector<int> transformGOIDs = componentLookUp.GetComponentTable<Transform>()->GetGameObjectIDs();
	std::vector<int> renderMeshGOIDs = componentLookUp.GetComponentTable<RenderMesh>()->GetGameObjectIDs();

	std::vector<int> gameObjectIDs = std::vector<int>();

	uint tCount = transformGOIDs.size();
	uint rCount = renderMeshGOIDs.size();
	for (uint i = 0; i < tCount; i++) {
		for (uint j = 0; j < rCount; j++) {
			if (transformGOIDs[i] == renderMeshGOIDs[j]) {
				gameObjectIDs.push_back(i);
				i++;
			}
		}
	}

	uint gCount = gameObjectIDs.size();
	for (size_t i = 0; i < gCount; i++) {
		Transform* transform = componentLookUp.GetComponentTable<Transform>()->GetComponent(gameObjectIDs[i]);
		RenderMesh* renderMesh = componentLookUp.GetComponentTable<RenderMesh>()->GetComponent(gameObjectIDs[i]);

		const Graphics::Mesh& mesh = renderMesh->GetMesh();
		mesh.Draw(transform->GetPosition(), transform->GetEulerRotation());
	}
}
