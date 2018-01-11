#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Memory\LinearAllocator.h"
#include "IwEngine\Events\EventBus.h"

struct GLFWwindow;
class IWENGINE_API Window {
private:
	GLFWwindow* _glfwWindow;
	Events::EventBus* _eventBus;
	Memory::LinearAllocator _tempMem;
	int _width;
	int _height;
	const char* _name;
public:
	Window(int width, int height, const char* name);
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	inline Events::EventBus& GetEventBus() {
		return *_eventBus;
	}

	void Init();
	void Run();
};