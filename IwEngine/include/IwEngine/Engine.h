#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Window.h"
#include "IwEngine\Scene.h"

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

	inline Scene& GetScene() {
		return *_scene;
	}

	inline Events::EventBus& GetEventBus() {
		return _window->GetEventBus();
	}
};