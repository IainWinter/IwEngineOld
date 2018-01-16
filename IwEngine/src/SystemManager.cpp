#include "IwEngine\SystemManager.h"

#include ".\ColliderSystem.cpp" //TODO: idk why we are getting linker errors.

SystemManager::SystemManager(Events::EventBus & eventBus, ComponentLookUp & componentLookUp)
	: Events::EventHandlerBase<UpdateEvent>(eventBus), _componentLookUp(componentLookUp) {}

SystemManager::~SystemManager() {
	for (std::vector<ISystem*>::iterator it = _systems.begin(); it != _systems.end(); ++it) {
		delete (*it);
	}
}

void SystemManager::ProcessEvent(const UpdateEvent& eventArgs) {
	for (ISystem* s : _systems) {
		s->Update(_componentLookUp, eventArgs.deltaTime);
	}
}
