#pragma once

#include <vector>
#include "IwEngine\Events\EventHandlerBase.h"

template<typename TComponent>
class System{
private:
	std::vector<TComponent*> _components;
};