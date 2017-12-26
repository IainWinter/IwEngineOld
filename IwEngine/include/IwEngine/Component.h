#pragma once

class GameObject; //monkeys

#include "GameObject.h"
#include "Transform.h"

class Component : public Object {
private:
	GameObject& gameObject;
	Transform& transform;
public:
	Component(GameObject& gameObject) 
		: gameObject(gameObject), 
		transform(gameObject.GetComponent<Transform>()) { }

	inline const GameObject& GetGameObject() const {
		return gameObject;
	}

	Transform& GetTransform() const {
		return transform;
	}
};