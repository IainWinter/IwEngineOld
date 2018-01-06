#pragma once

#include <vector>
#include <queue>
#include "IwEngine\Common.h"
#include "IHandler.h"
#include "IEvent.h"
#include <memory>

namespace Events {
	class EventBus {
	private:
		std::vector<IHandler*> _eventHandlers;
		std::queue<IEvent*> _queuedEvents;
	public:
		~EventBus();
		void ProcessEvents();
		void AddHandler(IHandler* handler);
		void RemoveHandler(const IHandler* handler);
		void SendEvent(IEvent* e);
		void SendInstantEvent(IEvent* e);
	};
}