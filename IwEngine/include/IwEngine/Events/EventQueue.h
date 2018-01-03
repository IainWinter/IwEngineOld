#pragma once

#include <queue>
#include <vector>
#include <functional>
#include <string>

namespace Events {
	struct IWENGINE_API Event {
		std::string name;
		void* data;
	};

	class IWENGINE_API EventQueue {
	private:
		std::queue<Event> _events;
		std::vector<std::function<void(Event)>> _receivers;
	public:
		void AddReceiver(std::function<void(Event)> eventReceivers) {
			_receivers.push_back(eventReceivers);
		}

		void FireEvent(const Event& message) {
			_events.push(message);
		}

		void ProcessEvents() {
			while (!_events.empty()) {
				for (auto iter = _receivers.begin(); iter != _receivers.end(); iter++) {
					(*iter)(_events.front());
				}

				_events.pop();
			}
		}
	};
}