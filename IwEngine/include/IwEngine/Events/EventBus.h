#pragma once

#include <vector>
#include <queue>
#include <memory>
#include "IwEngine\Common.h"
#include "IwEngine\Events\IHandler.h"
#include "IwEngine\Events\IEvent.h"
#include "IwEngine\Memory\LinearAllocator.h"

namespace Events {
	class EventBus {
	private:
		std::vector<IHandler*> _eventHandlers;
		std::queue<IEvent*> _queuedEvents;
		Memory::LinearAllocator& _tempMem;
	public:
		IWENGINE_API EventBus(Memory::LinearAllocator& _tempMem);
		IWENGINE_API EventBus(const EventBus&) = delete;
		IWENGINE_API EventBus& operator=(const EventBus&) = delete;

		IWENGINE_API ~EventBus();
		IWENGINE_API void ProcessEvents();
		IWENGINE_API void AddHandler(IHandler* handler);
		IWENGINE_API void RemoveHandler(const IHandler* handler);

		template<typename TEventType>
		void SendEvent(TEventType& e);
	};

	template<typename TEventType>
	void EventBus::SendEvent(TEventType& e) {
		IEvent* event = Memory::AllocateNew(_tempMem, e); //Event gets truncated
		_queuedEvents.push(event);
	}
}