#pragma once

#include <vector>
#include "IwEngine\Component.h"
#include "IwEngine\Utility\Logger.h"
#include "IwEngine\Events\EventBus.h"
#include "IwEngine\Events\EventBase.h"

#include "IwEngine\Transform.h"

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
	void* returnArgs;

	GameObjectEvent(GameObjectEventType type, GameObject& gameObject,  void* otherArgs)
		: type(type), gameObject(gameObject),  otherArgs(otherArgs), returnArgs(nullptr) {
	}

	GameObjectEvent(GameObjectEventType type, GameObject& gameObject,  void* otherArgs, void* returnArgs)
		: type(type), gameObject(gameObject),  otherArgs(otherArgs), returnArgs(returnArgs)  {
	}
};


class IWENGINE_API GameObject : public Object {
private:
	Events::EventBus* _eventBus;
public:
	GameObject(Events::EventBus* eventBus);
	GameObject(Events::EventBus* eventBus, const char* name);
	~GameObject();

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	template<typename TComponent>
	TComponent& GetComponent() const;

	void SendEvent(Events::IEvent* event);
};

template<typename TComponent> // = std::enable_if<TComponent, Component>
TComponent& GameObject::GetComponent() const {
	TComponent& ref;
	SendEvent(GameObjectEvent(GameObjectEventType::GET_COMPONENT, *this, TComponent, ref));

	return ref;

	//for (Component* component : _components.vector) {
	//	TComponent* ptr = dynamic_cast<TComponent*>(component);
	//	if (ptr != nullptr) {
	//		return *ptr;
	//	}
	//}

	//Utility::ThrowRunTimeError("'" + GetName() + "' has no component of type '" + typeid(TComponent).name() + "'");
}