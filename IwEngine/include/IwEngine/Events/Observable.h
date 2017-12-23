#pragma once

#include "IwEngine\Common.h"
#include "Observer.h"
#include <vector>

template<typename TEventArg>
class Observable {
private:
	std::vector<Observer<TEventArg>*> _observers;
protected:
	void Notify(const TEventArg& eventArgs);
public:
	void Attach(Observer<TEventArg>* observer);
	void Detach(Observer<TEventArg>* observer);
};

template<typename TEventArg>
void Observable<TEventArg>::Notify(const TEventArg& eventArgs) {
	for (Observer<TEventArg>* observer : _observers) {
		observer->Update(eventArgs);
	}
}

template<typename TEventArg>
void Observable<TEventArg>::Attach(Observer<TEventArg>* observer) {
	_observers.push_back(observer);
}

template<typename TEventArg>
void Observable<TEventArg>::Detach(Observer<TEventArg>* observer) {
	int size = _observers.size();
	for (size_t i = 0; i < size; i++) {
		if (_observers[i] == observer) {
			_observers.erase(_observers.begin(), i);
			break;
		}
	}
}
