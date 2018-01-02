#pragma once

#include "Common.h"
#include "Component.h"
#include "IwEngine\Graphics\Mesh.h"

class IWENGINE_API MeshFilter : public Component {
private:
	Graphics::Mesh mesh;
public:
	MeshFilter(GameObject& gameObject) : Component(gameObject) { }


};