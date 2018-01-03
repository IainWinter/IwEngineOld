#pragma once

#include "EventQueue.h"

namespace Events {
	class IWENGINE_API EventHandler {
	protected:
		EventQueue* eventQueue;

		inline void FireEvent(std::string name, void* data) {
			eventQueue->FireEvent({name, data});
		}

		virtual void Notify(Event event) = 0;
	public:
		EventHandler(EventQueue* eventQueue) : eventQueue(eventQueue) {
			eventQueue->AddReceiver(
				[=](Event event) -> void { this->Notify(event); }
			);
		}
	};
}