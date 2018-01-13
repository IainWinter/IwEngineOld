#pragma once

#include "Common.h"
#include "Component.h"
#include "IwEngine\Graphics\Mesh.h"

class RenderMesh : public Component {
private:
	Graphics::Mesh* _mesh;
public:
	RenderMesh(GameObject& gameObject, Graphics::Mesh* mesh) : Component(gameObject), _mesh(mesh) { }
	~RenderMesh() {
		delete _mesh;
	}

	inline const Graphics::Mesh& GetMesh() const {
		return *_mesh;
	}

	//Methods for getting normals/verts/setting mesh 
};