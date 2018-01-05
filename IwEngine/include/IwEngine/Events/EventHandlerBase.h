#pragma once

#include "IHandler.h"
#include "EventBus.h"

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