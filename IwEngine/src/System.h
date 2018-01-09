#pragma once

#include <vector>

template<typename TComponent>
class System{
private:
	std::vector<TComponent*> _components;
};