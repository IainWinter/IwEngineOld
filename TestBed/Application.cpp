#include "IwEngine\Engine.h"
#include "IwEngine\Scene.h"
#include "IwEngine\RenderMesh.h"
#include "IwEngine\GameObject.h"

int main() {
	Engine* engine = new Engine();

	Scene& scene = engine->GetScene();
	Events::EventBus& eventBus = engine->GetEventBus();
	ComponentLookUp& componentLookUp = engine->GetComponentLookUp();

	GameObject& gameObject = scene.MakeGameObject();

	gameObject.AddComponent<RenderMesh>(new RenderMesh(gameObject));

	scene.AddSystem(new System<RenderMesh>(eventBus, componentLookUp));

	engine->Run();

	delete engine;
}