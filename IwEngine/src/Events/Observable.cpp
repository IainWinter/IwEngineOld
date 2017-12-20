#include "IwEngine\Events\Observable.h"

void Observable::Hook(Observer* observer) {
	m_hookedObservers.push_back(observer);
}

void Observable::DeHook(Observer* observer) {
	m_hookedObservers.push_back(observer);
}

template<typename TEventType>
void Observable::Fire(TEventType event) {
	for (Observer& o : m_hookedObservers) {
		o.On<TEventType>(event);
	}
}
