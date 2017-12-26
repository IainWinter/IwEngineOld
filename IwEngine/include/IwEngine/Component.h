#pragma once

#include "GameObject.h"

class Component : public Object {
private:
	const GameObject& gameObject;
	//Transform& transform;
public:
	Component(const GameObject& gameObject) : gameObject(gameObject) {
	{
		//transform = gameObject.GetComponent<Transform>();
	}

	inline const GameObject& GetGameObject() const {
		return gameObject;
	}

	//Transform& GetTransform() const {
	//	return transform;
	//}
};