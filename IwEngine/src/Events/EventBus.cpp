#include "IwEngine\Events\EventBus.h"
#include "IwEngine\Events\EventBase.h"

using namespace Events;

Events::EventBus::EventBus(Memory::LinearAllocator& tempMem) : _tempMem(tempMem) {
	_queuedEvents = std::queue<IEvent*>();
}

void EventBus::ProcessEvents() {
	while (!_queuedEvents.empty()) {
		IEvent*& e = _queuedEvents.front();
		uint count = _eventHandlers.size();
		for (size_t i = 0; i < count; i++) {
			e->Dispatch(_eventHandlers[i]);
		}

		_queuedEvents.pop();
	}

	_tempMem.Clear();
}

Events::EventBus::~EventBus() {
	while (!_queuedEvents.empty()) {
		delete _queuedEvents.front();
		_queuedEvents.pop();
	}
}

void EventBus::AddHandler(IHandler* handler) {
	_eventHandlers.push_back(handler);
}

void EventBus::RemoveHandler(const IHandler* handler) {
	auto itr = std::find_if(_eventHandlers.begin(), _eventHandlers.end(), [&](IHandler* h) { return h == handler; });
	if (itr != _eventHandlers.end()) _eventHandlers.erase(itr);
}