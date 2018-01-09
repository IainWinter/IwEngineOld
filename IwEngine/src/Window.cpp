#include "IwEngine\Window.h"
#include "IwEngine\Utility\Logger.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"

Window::Window(int width, int height, const char* name) 
	:_width(width), _height(height), _name(name) {}

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
		Utility::Info("Window Open");
	}

	Utility::Info("Window Closed");
}
