#pragma once

#include "IwEngine\ComponentLookUp.h"
#include "IwEngine\Events\EventHandlerBase.h"
#include "IwEngine\CommonEvents.h"
#include "IwEngine\RenderMesh.h"

class ISystem {

};

template<typename... TComponent>
class System : public ISystem, public Events::EventHandlerBase<UpdateEvent> {
private:
	ComponentLookUp& _componentLookUp;
public:
	System(Events::EventBus& eventBus, ComponentLookUp& componentLookUp)
		: _componentLookUp(componentLookUp), Events::EventHandlerBase<UpdateEvent>(eventBus) {}

	void ProcessEvent(const UpdateEvent& event);
};

void System<RenderMesh>::ProcessEvent(const UpdateEvent& event) {
	Utility::Info("1");
}

//
//template<>
//void System<RenderMesh, RenderMesh>::ProcessEvent(const UpdateEvent& event) {
//	Utility::Info("2");
//}