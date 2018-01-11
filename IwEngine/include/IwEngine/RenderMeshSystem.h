#pragma once

#include "IwEngine\System.h"
#include "IwEngine\RenderMesh.h"
#include "IwEngine\Utility\Logger.h"

template<>
class System<RenderMesh> : public ISystem, public Events::EventHandlerBase<UpdateEvent> {
public:
	System(Events::EventBus& eventBus) : Events::EventHandlerBase<UpdateEvent>(eventBus) {}

	void ProcessEvent(const UpdateEvent& event) {
		Utility::Info("Update!");
	}
};