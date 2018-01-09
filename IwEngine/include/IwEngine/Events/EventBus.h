#pragma once

#include <vector>
#include <queue>
#include "IwEngine\Common.h"
#include "IHandler.h"
#include "IEvent.h"
#include <memory>
#include "IwEngine\Memory\LinearAllocator.h"

namespace Events {
	class EventBus {
	private:
		std::vector<IHandler*> _eventHandlers;
		std::queue<IEvent*> _queuedEvents;
		Memory::LinearAllocator& _tempMem;

		EventBus(const EventBus&);
		EventBus& operator=(const EventBus&) {}
	public:
		EventBus(Memory::LinearAllocator& _tempMem);
		~EventBus();
		void ProcessEvents();
		void AddHandler(IHandler* handler);
		void RemoveHandler(const IHandler* handler);
		void SendEvent(IEvent& e);
		void SendInstantEvent(IEvent& e);
	};
}