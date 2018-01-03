#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "IwEngine\Graphics\Display.h"
#include "IwEngine\Utility\Logger.h"
#include "IwEngine\Utility\IO\File.h"
#include <sstream>

#include "IwEngine\Graphics\Display.h"
#include "IwEngine\Graphics\VertexArray.h"
#include "IwEngine\Graphics\IndexBuffer.h"
#include "IwEngine\Graphics\ShaderProgram.h"
#include "IwEngine\Math\Matrix4.h"

//TODO: Temp
#include "IwEngine\Graphics\Display.h"
#include "IwEngine\Transform.h"
#include "IwEngine\GameObject.h"
#include "IwEngine\Utility\Logger.h"
#include "IwEngine\MeshComponent.h"
#include "IwEngine\Scene.h"
//

void Graphics::Display::Init() {
	Scene* scene = new Scene();

	GameObject& go = scene->AddGameObject("GameObject Test Cube");

	go.AddComponent<Transform>();

	float pos[] = {
		//left
		-0.5f, -0.5f, -0.5f,
		-0.5f, +0.5f, -0.5f,
		-0.5f, +0.5f, +0.5f,
		-0.5f, -0.5f, +0.5f,
		//right
		+0.5f, -0.5f, -0.5f,
		+0.5f, +0.5f, -0.5f,
		+0.5f, +0.5f, +0.5f,
		+0.5f, -0.5f, +0.5f,
		//bottom
		-0.5f, -0.5f, -0.5f,
		+0.5f, -0.5f, -0.5f,
		+0.5f, -0.5f, +0.5f,
		-0.5f, -0.5f, +0.5f,
		//top
		-0.5f, +0.5f, -0.5f,
		+0.5f, +0.5f, -0.5f,
		+0.5f, +0.5f, +0.5f,
		-0.5f, +0.5f, +0.5f,
		//back
		-0.5f, -0.5f, -0.5f,
		+0.5f, -0.5f, -0.5f,
		+0.5f, +0.5f, -0.5f,
		-0.5f, +0.5f, -0.5f,
		//front
		-0.5f, -0.5f, +0.5f,
		+0.5f, -0.5f, +0.5f,
		+0.5f, +0.5f, +0.5f,
		-0.5f, +0.5f, +0.5f

	};

	uint indices[] = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		8, 9, 10,
		10, 11, 8,
		12, 13, 14,
		14, 15, 12,
		16, 17, 18,
		18, 19, 16,
		20, 21, 22,
		22, 23, 20
	};


	Graphics::VertexBufferLayout layout;
	layout.Push<float>(3);

	Mesh* mesh = new Mesh(pos, 72, layout, indices, 36);

	MeshComponent* meshComp = new MeshComponent(go, mesh);

	go.AddComponent(meshComp);
}

int Graphics::Display::Start() {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		Utility::Error("GLEW init not ok");
	}

	//TODO:: Temp
	Init();

	Graphics::ShaderProgram shader("res/shaders/default.shader");

	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	Math::Vector3 position = Math::Vector3(0, 0, 2);
	Math::Matrix4 projection = Math::Matrix4::CreatePerspectiveFieldOfView(3.14f/2, 4.0f/3, 0.01f, 100.0f);
	Math::Matrix4 view = Math::Matrix4::LookAt(position, position - Math::Vector3::UnitZ, Math::Vector3::UnitY);
	Math::Matrix4 world = Math::Matrix4::Identity;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		//shader.Use();
		//glUniform4f(1, .4f, 1.0f, .2f, 1.0f);

		//glUniformMatrix4fv(0, 1, GL_FALSE, projection.elements);
		//glUniformMatrix4fv(4, 1, GL_FALSE, view.elements);
		//glUniformMatrix4fv(8, 1, GL_FALSE, world.elements);

		////position.y += 0.005f;
		//position.x -= 0.005f;
		////position.z += 0.005f;
		//view = Math::Matrix4::LookAt(position, position - Math::Vector3::UnitZ, Math::Vector3::UnitY);

		//va.Bind();
		//ib.Bind();

		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	shader.Delete();
	glfwTerminate();
	return 0;
}