#include "IwEngine\Window.h"
#include "IwEngine\Utility\Logger.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "IwEngine\CommonEvents.h"

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

	while (!glfwWindowShouldClose(_glfwWindow)) {
		_eventBus->SendEvent<UpdateEvent>(UpdateEvent(1.0f));
		_eventBus->ProcessEvents();

		glfwPollEvents();
	}
}
