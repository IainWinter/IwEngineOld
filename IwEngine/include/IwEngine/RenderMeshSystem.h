//#pragma once
//
//#include "IwEngine\System.h"
//#include "IwEngine\RenderMesh.h"
//#include "IwEngine\Utility\Logger.h"
//
//template<>
//class IWENGINE_API System<RenderMesh> : public ISystem, public Events::EventHandlerBase<UpdateEvent> {
//private:
//	ComponentLookUp& _componentLookUp;
//public:
//	System(Events::EventBus& eventBus, ComponentLookUp& componentLookUp)
//		: _componentLookUp(componentLookUp), Events::EventHandlerBase<UpdateEvent>(eventBus) {}
//
//	void ProcessEvent(const UpdateEvent& event);
//};