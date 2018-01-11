#include "IwEngine\SystemManager.h"

void SystemManager::ProcessEvent(const UpdateEvent& eventArgs) {
	for (ISystem* s : _systems) {
		s->Update(_componentLookUp, eventArgs.deltaTime);
	}
}
