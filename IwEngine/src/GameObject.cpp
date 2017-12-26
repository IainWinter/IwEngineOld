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
	size_t size = _components.size();
	for (size_t i = 0; i < size; i++) {
		delete & _components[i];
	}
}

void GameObject::AddComponent(const Component* component) {
	_components.push_back(component);
}

void GameObject::RemoveComponent(const Component& component) {
	size_t size = _components.size();
	for (size_t i = 0; i < size; i++) {
		if (_components[i] == &component) {
			_components.erase(_components.begin() + i);
			break;
		}
	}
}
