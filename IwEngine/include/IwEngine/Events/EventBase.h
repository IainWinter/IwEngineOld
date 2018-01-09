#pragma once

#include "IEvent.h"
#include "EventHandlerBase.h"

namespace Events {
	template<typename TEventType>
	class EventBase : public IEvent {
	private:
		virtual void Dispatch(IHandler* handler) override {
			TEventType* self = dynamic_cast<TEventType*>(this);
			if (self) {
				DynamicDispatch(handler, *self);
			}
		}

		void DynamicDispatch(IHandler* handler, const TEventType& self) {
			EventHandlerBase<TEventType>* handlerTarget = dynamic_cast<EventHandlerBase<TEventType>*>(handler);
			if (handlerTarget) {
				handlerTarget->ProcessEvent(self);
			}
		}
	};
}