#pragma once

#include <vector>
#include <queue>
#include <memory>
#include "IwEngine\Common.h"
#include "IwEngine\Events\IHandler.h"
#include "IwEngine\Events\IEvent.h"
#include "IwEngine\Memory\LinearAllocator.h"

namespace Events {
	class IWENGINE_API EventBus {
	private:
		std::vector<IHandler*> _eventHandlers;
		std::queue<IEvent*> _queuedEvents;
		Memory::LinearAllocator& _tempMem;
	public:
		EventBus(Memory::LinearAllocator& _tempMem);
		EventBus(const EventBus&) = delete;
		EventBus& operator=(const EventBus&) = delete;

		~EventBus();
		void ProcessEvents();
		void AddHandler(IHandler* handler);
		void RemoveHandler(const IHandler* handler);

		template<typename TEventType>
		void SendEvent(TEventType& e);
	};

	template<typename TEventType>
	void EventBus::SendEvent(TEventType& e) {
		IEvent* event = Memory::AllocateNew(_tempMem, e); //Event gets truncated
		_queuedEvents.push(event);
	}
}