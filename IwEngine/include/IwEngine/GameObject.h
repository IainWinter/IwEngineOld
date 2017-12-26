#pragma once

#include <vector>
#include "Object.h"
#include "Component.h"

class GameObject : public Object {
private:
	std::vector<const Component*> _components;
public:
	GameObject();
	GameObject(const char* name);
	~GameObject();
	
	template<typename TComponent>
	void AddComponent();
	void AddComponent(const Component* component);
	void RemoveComponent(const Component& component);

	template<typename TComponent>
	inline TComponent& GetComponent();
	template<typename TComponent>
	std::vector<TComponent&> GetComponents();

	//Messaging stuff
};

template<typename TComponent>
void GameObject::AddComponent() {
	TComponent component(this);
	_components.push_back(component);
}

template<typename TComponent>
inline TComponent& GameObject::GetComponent() {
	return GetComponents<TComponent>()[0];
}

template<typename TComponent>
std::vector<TComponent&> GameObject::GetComponents() {
	std::vector<TComponent&> components;
	for (Component* component : _components) {
		if (std::is_same(TComponent, component)) {
			components.push_back(component);
		}
	}

	return components;
}