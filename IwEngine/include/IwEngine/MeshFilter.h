#pragma once

#include "Common.h"
#include "Component.h"

class IWENGINE_API MeshFilter : public Component {
private:
	
public:
	MeshFilter(GameObject& gameObject) : Component(gameObject) { }


};