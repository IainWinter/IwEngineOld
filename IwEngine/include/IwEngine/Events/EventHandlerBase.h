#pragma once

#include "IwEngine\Events\IHandler.h"
#include "IwEngine\Events\EventBus.h"

namespace Events {
	template<typename TEventType>
	class EventHandlerBase : public IHandler {
	public:
		EventHandlerBase(EventBus& eventBus) {
			eventBus.AddHandler(this);
		}

		virtual void ProcessEvent(const TEventType& eventArgs) = 0;
		virtual ~EventHandlerBase() {}
	};
}