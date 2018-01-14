#pragma once

#include "Common.h"
#include "Component.h"
#include "IwEngine\Graphics\Mesh.h"

class RenderMesh : public Component {
private:
	Graphics::Mesh* _bounds;
public:
	RenderMesh(GameObject& gameObject, Graphics::Mesh* mesh) : Component(gameObject), _bounds(mesh) { }
	~RenderMesh() {
		delete _bounds;
	}

	inline const Graphics::Mesh& GetMesh() const {
		return *_bounds;
	}

	//Methods for getting normals/verts/setting mesh 
};