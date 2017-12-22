#pragma once

template<typename TEventArg>
class Observer {
public:
	Observer() {};
	virtual ~Observable() {};
	virtual void Update(const TEventArg& args) = 0;
};