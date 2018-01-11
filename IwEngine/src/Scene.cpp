#include "IwEngine\Scene.h"

Scene::Scene() {
	_componentLookUp = new ComponentLookUp();
}

Scene::~Scene() {
	delete _componentLookUp;
}

GameObject& Scene::MakeGameObject() {
	return MakeGameObject("");
}

GameObject& Scene::MakeGameObject(const char* name) {
	GameObject* go = new GameObject(*_componentLookUp, name);
	_gameObjects.push_back(go);
	return *go;
}

void Scene::AddSystem(ISystem* system) {
	_systems.push_back(system);
}
