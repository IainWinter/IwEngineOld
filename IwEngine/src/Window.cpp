#include "IwEngine\Window.h"
#include "IwEngine\Utility\Logger.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "IwEngine\CommonEvents.h"
#include <ctime>

//Temp
#include "IwEngine\Graphics\ShaderProgram.h"
#include "IwEngine\Math\Vector3.h"
#include "IwEngine\Math\Matrix4.h"

Window::Window(int width, int height, const char* name) 
	: _width(width), _height(height), _name(name), _tempMem(16777216, malloc(16777216))
{
	_eventBus = new Events::EventBus(_tempMem);
}

Window::~Window() {
	glfwTerminate();
	delete &_glfwWindow;
}

void Window::Init() {
	if (!glfwInit()) {
		Utility::Error("GLFW failed to initialize!!");
	}

	_glfwWindow = glfwCreateWindow(_width, _height, _name, NULL, NULL);
	if (!_glfwWindow) {
		glfwTerminate();
		Utility::Error("GLFW window failed to open!!");
	}

	glfwMakeContextCurrent(_glfwWindow);

	if (glewInit() != GLEW_OK) {
		Utility::Error("GLEW init is not ok!!");
	}
}

void Window::Run() {
	if (!_glfwWindow) {
		Utility::Error("Window was not initialized!!");
		return;
	}

	Graphics::ShaderProgram shader = Graphics::ShaderProgram("res/shaders/default.shader");

	Math::Vector3 position = Math::Vector3(0, 0, 0);
	Math::Matrix4 projection = Math::Matrix4::CreatePerspectiveFieldOfView(3.14f / 2, 4.0f / 3, 0.01f, 100.0f);
	Math::Matrix4 view = Math::Matrix4::LookAt(position, position - Math::Vector3::UnitZ, Math::Vector3::UnitY);
	Math::Matrix4 world = Math::Matrix4::Identity;

	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	clock_t startTime = clock();
	float deltaTime = 0;
	while (!glfwWindowShouldClose(_glfwWindow)) {
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();
		glUniform4f(1, 1, 1, 1, 1.0f);

		glUniformMatrix4fv(0, 1, GL_FALSE, projection.elements);
		glUniformMatrix4fv(4, 1, GL_FALSE, view.elements);
		glUniformMatrix4fv(8, 1, GL_FALSE, world.elements);

		_eventBus->SendEvent<UpdateEvent>(UpdateEvent(deltaTime));
		_eventBus->ProcessEvents();

		glfwSwapBuffers(_glfwWindow);

		glfwPollEvents();

		deltaTime = (clock() - startTime) / (float) CLOCKS_PER_SEC;
		startTime = clock();
	}

	shader.Delete();
	glfwTerminate();
}
