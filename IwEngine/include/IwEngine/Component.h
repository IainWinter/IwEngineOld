#pragma once

#include "Object.h"
#include "Utility\Logger.h"

class GameObject;
class IWENGINE_API Component : public Object {
private:
	GameObject& gameObject;
public:
	Component(GameObject& gameObject) : gameObject(gameObject) { }
	virtual ~Component() = default;

	inline const GameObject& GetGameObject() const { //Prolly not going to be constant idk
		return gameObject;
	}
};