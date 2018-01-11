#include "IwEngine\Engine.h"

Engine::Engine() {
	_window = new Window(640, 480, "Physics Project!!");
	_scene = new Scene(_window->GetEventBus()); //Load this from resource manager
}

Engine::~Engine() {
	delete _window;
	delete _scene;
}

void Engine::Run() {
	_window->Init();
	_window->Run();
}