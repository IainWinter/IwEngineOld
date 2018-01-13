#include "IwEngine\RenderMeshSystem.h"
#include <vector>

void System<RenderMesh>::Update(ComponentLookUp& componentLookUp, float deltaTime) {
	std::vector<RenderMesh*>& components = componentLookUp.GetComponentTable<RenderMesh>()->GetComponents();

	for (RenderMesh* renderMesh : components) {
		const Graphics::Mesh& mesh = renderMesh->GetMesh();
		mesh.Draw();
	}
}
