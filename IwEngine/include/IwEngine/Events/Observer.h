#pragma once

#include "IwEngine\Common.h"

template<typename TEventArg>
class Observer {
public:
	virtual void Update(const TEventArg& args) = 0;
};