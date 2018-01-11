#pragma once

#include "IwEngine\ColliderSystem.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"

void System</*SphereCollider, BoxCollider*/>::Update(ComponentLookUp& componentLookUp, float deltaTime) {
	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glEnd();
}
