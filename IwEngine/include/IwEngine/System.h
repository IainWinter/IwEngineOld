#pragma once

#include "IwEngine\ComponentLookUp.h"
#include "IwEngine\Utility\Logger.h"

class ISystem {
public:
	virtual void Update(ComponentLookUp& componentLookUp, float deltaTime) = 0;
};

template<typename ...TComponent>
class System : public ISystem {
public:
	void Update(ComponentLookUp& componentLookUp, float deltaTime);
};