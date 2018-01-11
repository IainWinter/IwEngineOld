#include "IwEngine\Engine.h"
#include "IwEngine\Scene.h"
#include "IwEngine\RenderMesh.h"
#include "IwEngine\GameObject.h"
#include "IwEngine\RenderMeshSystem.h"

int main() {
	Engine* engine = new Engine();

	Scene& scene = engine->GetScene();
	Events::EventBus& eventBus = engine->GetEventBus();

	GameObject& gameObject = scene.MakeGameObject();

	gameObject.AddComponent<RenderMesh>(new RenderMesh(gameObject));

	scene.AddSystem(new System<RenderMesh>(eventBus));

	engine->Run();

	delete engine;
}