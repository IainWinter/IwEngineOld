#include "IwEngine\GameObject.h"

GameObject::GameObject() {
	std::string name("Gameobject ");
	name.append(std::to_string(GetInstanceID()));
	SetName(name);
}

GameObject::GameObject(const char* name) {
	SetName(name);
}

GameObject::~GameObject() {
	size_t size = _components.vector.size();
	for (size_t i = 0; i < size; i++) {
		delete _components.vector[i];
	}
}

void GameObject::AddComponent(Component* component) {
	_components.vector.push_back(component);
}

void GameObject::RemoveComponent(const Component& component) {
	size_t size = _components.vector.size();
	for (size_t i = 0; i < size; i++) {
		if (_components.vector[i] == &component) {
			_components.vector.erase(_components.vector.begin() + i);
			break;
		}
	}
}
