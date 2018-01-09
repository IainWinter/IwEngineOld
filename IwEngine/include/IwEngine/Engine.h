#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Window.h"
#include "IwEngine\Scene.h"
#include "IwEngine\Events\EventBus.h"
#include "IwEngine\Memory\LinearAllocator.h"

class IWENGINE_API Engine {
private:
	Window* _glfwWindow;
	Scene* _scene;
	Events::EventBus* _eventBus;
	//ResourceManager* _resourceManager
	Memory::LinearAllocator _tempMem; //tmp memory for each frame. Not going to put this here but it works for now
	bool _running;
public:
	Engine();
	~Engine();

	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	void Run();
};