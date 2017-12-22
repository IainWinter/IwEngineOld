#include "IwEngine\Events\Observable.h"

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

template<typename TEventArg>
void Observable<TEventArg>::Notify(const TEventArg& eventArgs) {
	int size = _observers.size();
	for (size_t i = 0; i < size; i++) {
		_observer[i]->Update(eventArgs);
	}
}
