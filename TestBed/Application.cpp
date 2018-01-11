#include "IwEngine\Engine.h"
#include "IwEngine\Scene.h"
#include "IwEngine\RenderMesh.h"
#include "IwEngine\GameObject.h"

int main() {
	Engine* engine = new Engine();

	Scene& scene = engine->GetScene();

	GameObject& gameObject = scene.MakeGameObject();

	gameObject.AddComponent<RenderMesh>(new RenderMesh(gameObject));

	scene.MakeSystem<RenderMesh>();

	engine->Run();

	delete engine;
}