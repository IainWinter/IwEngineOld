#include "IwEngine\Window.h"
#include "IwEngine\Utility\Logger.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "IwEngine\CommonEvents.h"
#include <ctime>

//Temp
#include "IwEngine\Graphics\ShaderProgram.h"
#include "IwMath\vector3.h"
#include "IwMath\matrix4.h"

Window::Window(int width, int height, const char* name) 
	: _width(width), _height(height), _name(name), _tempMem(16777216, malloc(16777216))
{
	_eventBus = new Events::EventBus(_tempMem);
}

Window::~Window() {
	glfwTerminate();
	delete _eventBus;
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

	math::vector3 position = math::vector3(0, 0, 0);
	math::matrix4 projection = math::matrix4::createPerspectiveFieldOfView(1.744f, 16.0f / 9.0f, 0.01f, 100.0f);
	math::matrix4 view = math::matrix4::lookAt(position, position - math::vector3::unitZ, math::vector3::unitY);
	math::matrix4 world = math::matrix4::identity;

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
