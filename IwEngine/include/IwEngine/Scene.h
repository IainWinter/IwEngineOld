#pragma once

#include <vector>
#include "IwEngine\Common.h"
#include "IwEngine\ComponentLookUp.h"
#include "IwEngine\GameObject.h"
#include "IwEngine\SystemManager.h"

class Scene {
private:
	std::vector<GameObject*> _gameObjects;
	ComponentLookUp* _componentLookUp;
	SystemManager* _systemManager;
public:
	IWENGINE_API Scene(Events::EventBus& eventBus);
	IWENGINE_API ~Scene();

	IWENGINE_API GameObject& Scene::MakeGameObject();
	IWENGINE_API GameObject& Scene::MakeGameObject(const char* name);

	template<typename ...TComponents>
	void MakeSystem();
};

template<typename ...TComponents>
void Scene::MakeSystem() {
	_systemManager->MakeSystem<TComponents...>();
}