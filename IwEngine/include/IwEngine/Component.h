#pragma once

#include "Object.h"

class GameObject;
class IWENGINE_API Component : public Object {
private:
	GameObject& gameObject;
public:
	Component(GameObject& gameObject) : gameObject(gameObject) { }

	inline const GameObject& GetGameObject() const {
		return gameObject;
	}
};