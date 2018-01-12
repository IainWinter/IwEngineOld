#include "IwEngine\RenderMeshSystem.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include <vector>

void System<RenderMesh>::Update(ComponentLookUp& componentLookUp, float deltaTime) {
	std::vector<RenderMesh*>& components = componentLookUp.GetComponentTable<RenderMesh>()->GetComponents();

	for (RenderMesh* renderMesh : components) {
		const Graphics::Mesh& mesh = renderMesh->GetMesh();
		mesh.Bind();
	}
}
