#pragma once
#include <vector>
#include "Observer.h"

class Observable {
private:
	std::vector<Observer*> m_hookedObservers;
public:
	void Hook(Observer* observer);
	void DeHook(Observer* observer);
	template<typename TEventType> void Fire(TEventType event);
};