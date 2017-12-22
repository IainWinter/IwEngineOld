#pragma once
#include <vector>
#include "Observer.h"

template<typename TEventArg>
class Observable {
private:
	std::vector<Observer<TEventArg>*> _observers;
protected:
	void Notify(TEventArg& eventArgs);
public:
	Observable() {};
	virtual ~Observable() {};
	void Attach(Observer<TEventArg>* observer);
	void Detach(Observer<TEventArg>* observer);
};

