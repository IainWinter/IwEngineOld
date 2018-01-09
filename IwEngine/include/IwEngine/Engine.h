#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Window.h"
#include "IwEngine\Scene.h"
#include "IwEngine\Events\EventBus.h"
#include "IwEngine\Memory\LinearAllocator.h"

class IWENGINE_API Engine {
private:
	Window* _window;
	Scene* _scene;
	//ResourceManager* _resourceManager
public:
	Engine();
	~Engine();

	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	void Run();
};