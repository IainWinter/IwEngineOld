#pragma once

#include <vector>
#include "IwEngine\System.h"
#include "IwEngine\Events\EventBus.h"
#include "IwEngine\CommonEvents.h"
#include "IwEngine\RenderMeshSystem.h"

class SystemManager : Events::EventHandlerBase<UpdateEvent> {
private:
	ComponentLookUp& _componentLookUp;
	std::vector<ISystem*> _systems;
public:
	SystemManager(Events::EventBus& eventBus, ComponentLookUp& componentLookUp)
		: Events::EventHandlerBase<UpdateEvent>(eventBus), _componentLookUp(componentLookUp) {}

	SystemManager(const SystemManager&) = delete;
	const SystemManager& operator=(const SystemManager&) = delete;

	void ProcessEvent(const UpdateEvent& eventArgs);

	template<typename ...TComponents>
	void MakeSystem();
};

template<typename ...TComponents>
void SystemManager::MakeSystem() {
	ISystem* system = new System<TComponents...>();
	_systems.push_back(system);
}
