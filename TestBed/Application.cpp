#include "IwEngine\Engine.h"

#include "IwEngine\ComponentLookUp.h"

int main() {
	Engine* engine = new Engine();
	engine->Run();
	delete engine;
}