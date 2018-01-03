#pragma once

#include <vector>
#include "IwEngine\Object.h"
#include "IwEngine\GameObject.h"
#include "IwEngine\Events\EventHandler.h"

class IWENGINE_API Scene : public Object {
private:
	struct SceneData {
		std::vector<GameObject*> gameObjects;
	};

	SceneData sceneData;
public:
	GameObject& AddGameObject(const char* name) {
		GameObject* go = new GameObject(name);
		sceneData.gameObjects.push_back(go);
		return *go;
	}
};