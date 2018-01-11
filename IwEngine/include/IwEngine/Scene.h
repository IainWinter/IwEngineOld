#pragma once

#include <vector>
#include "IwEngine\Common.h"
#include "IwEngine\ComponentLookUp.h"
#include "IwEngine\GameObject.h"
#include "IwEngine\SystemManager.h"

class IWENGINE_API Scene {
private:
	std::vector<GameObject*> _gameObjects;
	ComponentLookUp* _componentLookUp;
	SystemManager* _systemManager;
public:
	Scene(Events::EventBus& eventBus);
	~Scene();

	GameObject& Scene::MakeGameObject();
	GameObject& Scene::MakeGameObject(const char* name);

	template<typename ...TComponents>
	void MakeSystem();
};

template<typename ...TComponents>
void Scene::MakeSystem() {
	_systemManager->MakeSystem<TComponents...>();
}