#pragma once

#include "IwEngine\Object.h"
#include "IwEngine\Utility\Logger.h"

class GameObject;
class Component : public Object {
private:
	GameObject& gameObject;
public:
	Component(GameObject& gameObject) : gameObject(gameObject) { }
	virtual ~Component() = default;

	inline GameObject& GetGameObject() { 
		return gameObject;
	}
};