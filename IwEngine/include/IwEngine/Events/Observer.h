#pragma once

#include "IwEngine\Common.h"

namespace Events {
	template<typename TEventArg>
	class Observer {
	public:
		virtual void Update(const TEventArg& args) = 0;
	};
}