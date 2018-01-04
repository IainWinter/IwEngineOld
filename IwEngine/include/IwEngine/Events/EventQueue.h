#pragma once

//#include <queue>
//#include <vector>
//#include <functional>
//#include <string>
//
//namespace Events {
//	struct IWENGINE_API Event {
//		std::string name;
//		void* data;
//	};
//
//	class IWENGINE_API EventQueue {
//	private:
//		struct Queue { std::queue<Event> queue; };
//		struct EventVector { std::vector<std::function<void(Event)>> vector; };
//
//		Queue _events;
//		EventVector _receivers;
//	public:
//		void AddReceiver(std::function<void(Event)> eventReceivers) {
//			_receivers.vector.push_back(eventReceivers);
//		}
//
//		void FireEvent(const Event& message) {
//			_events.queue.push(message);
//		}
//
//		void ProcessEvents() {
//			while (!_events.queue.empty()) {
//				for (auto iter = _receivers.vector.begin(); iter != _receivers.vector.end(); iter++) {
//					(*iter)(_events.queue.front());
//				}
//
//				_events.queue.pop();
//			}
//		}
//	};
//}