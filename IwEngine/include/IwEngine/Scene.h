#pragma once

#include <vector>
#include "IwEngine\Common.h"
#include "IwEngine\ComponentLookUp.h"
#include "IwEngine\GameObject.h"
#include "IwEngine\System.h"

class IWENGINE_API Scene {
private:
	std::vector<GameObject*> _gameObjects;
	ComponentLookUp* _componentLookUp;
	std::vector<ISystem*> _systems;
public:
	Scene();
	~Scene();

	GameObject& Scene::MakeGameObject();
	GameObject& Scene::MakeGameObject(const char* name);
	void AddSystem(ISystem* system);

	inline ComponentLookUp& GetComponentLookUp() {
		return *_componentLookUp;
	}
};