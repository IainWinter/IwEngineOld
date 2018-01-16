#pragma once

#include <vector>
#include "IwEngine\Events\EventBus.h"
#include "IwEngine\CommonEvents.h"
#include "IwEngine\RenderMeshSystem.h"
#include "IwEngine\RigidBodySystem.h"
#include "IwEngine\ColliderSystem.h"

class SystemManager : Events::EventHandlerBase<UpdateEvent> {
private:
	ComponentLookUp& _componentLookUp;
	std::vector<ISystem*> _systems;
public:
	IWENGINE_API SystemManager(Events::EventBus& eventBus, ComponentLookUp& componentLookUp);
	IWENGINE_API ~SystemManager();

	IWENGINE_API SystemManager(const SystemManager&) = delete;
	IWENGINE_API const SystemManager& operator=(const SystemManager&) = delete;

	IWENGINE_API void ProcessEvent(const UpdateEvent& eventArgs);

	template<typename ...TComponents>
	void MakeSystem();
};

template<typename ...TComponents>
void SystemManager::MakeSystem() {
	ISystem* system = new System<TComponents...>();
	_systems.push_back(system);
}
