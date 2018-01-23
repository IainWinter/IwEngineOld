#include "IwEngine\Scene.h"

Scene::Scene(Events::EventBus& eventBus) {
	_componentLookUp = new ComponentLookUp();
	_systemManager = new SystemManager(eventBus, *_componentLookUp);
}

Scene::~Scene() {
	for (std::vector<GameObject*>::iterator it = _gameObjects.begin(); it != _gameObjects.end(); ++it) {
		delete (*it);
	}

	delete _componentLookUp;
	delete _systemManager;
}

GameObject& Scene::MakeGameObject() {
	return MakeGameObject("");
}

GameObject& Scene::MakeGameObject(const char* name) {
	GameObject* go = new GameObject(*_componentLookUp, name);
	_gameObjects.push_back(go);
	return *go;
}