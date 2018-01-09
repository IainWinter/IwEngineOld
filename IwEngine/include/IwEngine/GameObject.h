#pragma once

#include <vector>
#include "IwEngine\Component.h"
#include "IwEngine\Utility\Logger.h"
#include "IwEngine\Events\EventBus.h"
#include "IwEngine\Events\EventBase.h"

enum class GameObjectEventType {
	ADD_COMPONENT,
	REMOVE_COMPONENT,
	GET_COMPONENT,
	GAMEOBJECT_DESTROYED
};

struct GameObjectEvent : Events::EventBase<GameObjectEvent> {
	GameObjectEventType type;
	GameObject& gameObject;
	void* otherArgs;

	GameObjectEvent(GameObjectEventType type, GameObject& gameObject,  void* otherArgs)
		: type(type), gameObject(gameObject),  otherArgs(otherArgs) {}
};


class IWENGINE_API GameObject : public Object {
private:
	Events::EventBus& _eventBus;
	Component* cachedComponent;
public:
	GameObject(Events::EventBus& eventBus);
	GameObject(Events::EventBus& eventBus, const char* name);
	~GameObject();

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	template<typename TComponent>
	TComponent& GetComponent();

	void SendEvent(Events::IEvent& event);
	void SendInstantEvent(Events::IEvent& event);

	friend class Scene;
	void CasheComponent(Component* component); //TODO: Could have function pass in lambda but this works for now
};

template<typename TComponent>
TComponent& GameObject::GetComponent() {
	std::size_t requestedTypeID = typeid(TComponent).hash_code();
	std::size_t cashedTypeID = typeid(cachedComponent).hash_code();

	if (requestedTypeID != cashedTypeID) {
		SendInstantEvent(GameObjectEvent(GameObjectEventType::GET_COMPONENT, *this, &requestedTypeID));
	}

	return *dynamic_cast<TComponent*>(cachedComponent);
}