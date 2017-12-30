#pragma once

#include <vector>
#include "Component.h"
#include "Transform.h" //Make this in a header of indluded components
#include "Utility\Logger.h"

class IWENGINE_API GameObject : public Object {
private:
	//Wrapper for __dllspec C4251
	struct VectorConstComponent { std::vector<Component*> vector; };

	VectorConstComponent _components;
public:
	GameObject();
	//should we pass the physics material in the game object constructor?
	GameObject(const char* name);
	~GameObject();

	template<typename TComponent>
	void AddComponent();

	void AddComponent(Component* component);
	void RemoveComponent(const Component& component);

	template<typename TComponent>
	TComponent& GetComponent() const;

	template<typename TComponent>
	std::vector<TComponent*> GetComponents() const;

	//Messaging stuff
};

template<typename TComponent>
void GameObject::AddComponent() {
	Component* component = new TComponent(*this);
	_components.vector.push_back(component);
}

template<typename TComponent> // = std::enable_if<TComponent, Component>
TComponent& GameObject::GetComponent() const {
	for (Component* component : _components.vector) {
		TComponent* ptr = dynamic_cast<TComponent*>(component);
		if (ptr != nullptr) {
			return *ptr;
		}
	} 

	Utility::ThrowRunTimeError("'" + GetName() + "' has no component of type '" + typeid(TComponent).name() + "'");
}

template<typename TComponent>
std::vector<TComponent*> GameObject::GetComponents() const {
	std::vector<TComponent*> outComps;
	for (Component* component : _components.vector) {
		TComponent* ptr = dynamic_cast<TComponent*>(component);
		if (ptr != nullptr) {
			outComps.push_back(ptr);
		}
	}

	return outComps;
}