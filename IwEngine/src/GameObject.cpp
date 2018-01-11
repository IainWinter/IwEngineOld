#include "IwEngine\GameObject.h"

GameObject::GameObject(ComponentLookUp& componentLookUp)
	: _componentLookUp(componentLookUp)
{
	std::string name("Gameobject ");
	name.append(std::to_string(GetInstanceID()));
	SetName(name);
}

GameObject::GameObject(ComponentLookUp& componentLookUp, const char* name)
	: _componentLookUp(componentLookUp)
{
	SetName(name);

}

GameObject::~GameObject() {
	_componentLookUp.RemoveAllComponents(GetInstanceID());
}