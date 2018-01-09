#pragma once

#include "IwEngine\Scene.h"
#include "IwEngine\Events\EventBus.h"
#include "IwEngine\Memory\LinearAllocator.h"

class Engine {
private:
	Scene* _scene;
	Events::EventBus* _eventBus;
	//ResourceManager* _resourceManager
	Memory::LinearAllocator _tempMem; //tmp memory for each frame. Probly not going to put this here but it works for now

	//Don't allow copying
	Engine(const Engine&);
	Engine& operator=(const Engine&) {}
public:
	Engine();
	~Engine();
	inline Events::EventBus& GetEventBus() {
		return *_eventBus;
	}
};