#include "IwEngine\Engine.h"

int main() {
	Engine* engine = new Engine();
	engine->Run();
	delete engine;
}
