#include "IwEngine\SystemManager.h"

#include ".\ColliderSystem.cpp" //TODO: idk why we are getting linker errors.

void SystemManager::ProcessEvent(const UpdateEvent& eventArgs) {
	for (ISystem* s : _systems) {
		s->Update(_componentLookUp, eventArgs.deltaTime);
	}
}
