#include "IwEngine\GameObject.h"
#include "Scene.h"

GameObject::GameObject(Events::EventBus* eventBus) : _eventBus(eventBus) {
	std::string name("Gameobject ");
	name.append(std::to_string(GetInstanceID()));
	SetName(name);
}

GameObject::GameObject(Events::EventBus* eventBus, const char* name) : _eventBus(eventBus) {
	SetName(name);
}

GameObject::~GameObject() {
	SendEvent(new GameObjectEvent(GameObjectEventType::GAMEOBJECT_DESTROYED, *this, nullptr));
}

void GameObject::AddComponent(Component* component) {
	SendEvent(new GameObjectEvent(GameObjectEventType::ADD_COMPONENT, *this, component));
	CasheComponent(component);
}

void GameObject::RemoveComponent(Component* component) {
	SendEvent(new GameObjectEvent(GameObjectEventType::REMOVE_COMPONENT, *this, component));
}

void GameObject::SendEvent(Events::IEvent* event) {
	_eventBus->SendEvent(event);
}

void GameObject::SendInstantEvent(Events::IEvent * event) {
	_eventBus->SendInstantEvent(event);
}

void GameObject::CasheComponent(Component* component) {
	cachedComponent = component;
}
