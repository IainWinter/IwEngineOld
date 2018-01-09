#include "IwEngine\Engine.h"

Engine::Engine() {
	_scene = new Scene(); //Load this from resource manager
	_window = new Window(640, 480, "Physics Project!!");
}

Engine::~Engine() {
	delete _window;
	delete _scene;
}

void Engine::Run() {
	_window->Init();
	_window->Run();
}