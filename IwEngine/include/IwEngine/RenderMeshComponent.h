#pragma once

#include "Common.h"
#include "Component.h"
#include "IwEngine\Graphics\Mesh.h"

class IWENGINE_API RenderMeshComponent : public Component {
private:
	Graphics::Mesh* mesh;
public:
	RenderMeshComponent(GameObject& gameObject) : Component(gameObject) { }
	RenderMeshComponent(GameObject& gameObject, Graphics::Mesh* mesh) : Component(gameObject), mesh(mesh) { }

	inline const Graphics::Mesh& GetMesh() const {
		return *mesh;
	}

	//Methods for getting normals/verts/setting mesh 
};