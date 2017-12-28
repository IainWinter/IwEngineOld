#pragma once

#include <vector>
#include "Object.h"
#include "Component.h"

class Component;
class IWENGINE_API GameObject : public Object {
private:
	//Wrapper for __dllspec C4251
	struct VectorConstComponent { std::vector<const Component*> vector; };

	VectorConstComponent _components;
public:
	GameObject();
	//should we pass the physics material in the game object constructor?
	GameObject(const char* name);
	~GameObject();
	
	template<typename TComponent>
	void AddComponent() {
		TComponent component(this);
		_components.vector.push_back(component);
	}

	void AddComponent(const Component* component);
	void RemoveComponent(const Component& component);

	template<typename TComponent>
	TComponent& GetComponent() const {
		return GetComponents<TComponent>()[0];
	}

	template<typename TComponent>
	std::vector<TComponent&> GetComponents() {
		std::vector<TComponent&> outComps;
		for (Component* component : _components.vector) {
			if (std::is_same(TComponent, component)) {
				outComps.push_back(component);
			}
		}

		return outComps;
	}

	//Messaging stuff
};