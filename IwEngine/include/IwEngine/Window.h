#pragma once

#include "IwEngine\Common.h"

struct GLFWwindow;
class IWENGINE_API Window {
private:
	GLFWwindow* _glfwWindow;
	int _width;
	int _height;
	const char* _name;
public:
	Window(int width, int height, const char* name);
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	void Init();
	void Run();
};