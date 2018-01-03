#pragma once

#include "Common.h"
#include "Component.h"
#include "IwEngine\Graphics\Mesh.h"

class IWENGINE_API MeshComponent : public Component {
private:
	Graphics::Mesh* mesh;
public:
	MeshComponent(GameObject& gameObject) : Component(gameObject) { }
	MeshComponent(GameObject& gameObject, Graphics::Mesh* mesh) : Component(gameObject), mesh(mesh) { }

	inline const Graphics::Mesh& GetMesh() const {
		return *mesh;
	}

	//Methods for getting normals/verts/setting mesh 
};