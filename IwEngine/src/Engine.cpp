#include "IwEngine\Engine.h"

Engine::Engine() : _tempMem(16777216, malloc(16777216)) { // yak
	_scene = new Scene(); //Load this from resource manager
	_eventBus = new Events::EventBus(_tempMem);
}

Engine::~Engine() {
}
