#include "IwEngine\Engine.h"

Engine::Engine() {
	_window = new Window(1280, 720, "Physics Project!!");
	_scene = new Scene(_window->GetEventBus()); //Load this from resource manager
}

Engine::~Engine() {
	delete _scene;
	delete _window;
}

void Engine::Init() {
	_window->Init();
}


void Engine::Run() {
	_window->Run();
}