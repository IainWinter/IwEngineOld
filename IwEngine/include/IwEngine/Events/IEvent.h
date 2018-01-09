#pragma once

#include "IHandler.h"

namespace Events {
	class EventBus;
	class IEvent {
	private:
		friend class EventBus;
		virtual void Dispatch(IHandler* handler) {}
	public:
		virtual ~IEvent() {}
	};
}