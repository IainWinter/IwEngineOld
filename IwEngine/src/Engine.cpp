#include "IwEngine\Engine.h"

Engine::Engine() : _tempMem(16777216, malloc(16777216)) { // yak
	_scene = new Scene(); //Load this from resource manager
	_eventBus = new Events::EventBus(_tempMem);
	_glfwWindow = new Window(640, 480, "Physics Project!!");
}

Engine::~Engine() {
	_tempMem.Clear();
	delete &_eventBus;
	delete &_scene;
	delete &_tempMem;
}

void Engine::Run() {
	_glfwWindow->Run();
}