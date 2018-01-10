#pragma once

#include <vector>
#include "IwEngine\Component.h"
#include "IwEngine\Utility\Logger.h"
#include "IwEngine\ComponentLookUp.h"

class IWENGINE_API GameObject : public Object {
private:
	ComponentLookUp& _componentLookUp;
public:
	GameObject(ComponentLookUp& componentLookUp);
	GameObject(ComponentLookUp& componentLookUp, const char* name);
	~GameObject();

	template<typename TComponent>
	void AddComponent(TComponent* component);
	template<typename TComponent>
	void RemoveComponent(TComponent* component);

	template<typename TComponent>
	TComponent* GetComponent();
};

template<typename TComponent>
void GameObject::AddComponent(TComponent* component) {
	_componentLookUp.AddComponent<TComponent>(GetInstanceID(), component);
}

template<typename TComponent>
void GameObject::RemoveComponent(TComponent* component) {
	_componentLookUp.RemoveComponent<TComponent>(GetInstanceID(), component);
}

template<typename TComponent>
TComponent* GameObject::GetComponent() {
	return _componentLookUp.GetComponent<TComponent>(GetInstanceID());
}