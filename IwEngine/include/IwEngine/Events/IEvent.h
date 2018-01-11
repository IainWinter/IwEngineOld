#pragma once

#include "IwEngine\Events\IHandler.h"

namespace Events {
	class EventBus;
	class IEvent {
	private:
		friend class EventBus;
		virtual void Dispatch(IHandler* handler) = 0;
	public:
		virtual ~IEvent() {}
	};
}