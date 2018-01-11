#pragma once

#include "IwEngine\System.h"
//#include "IwEngine\SphereCollider.h"
//#include "IwEngine\BoxCollider.h"
#include "IwEngine\Utility\Logger.h"

template<>
class IWENGINE_API System</*SphereCollider, BoxCollider*/> : public ISystem {
	virtual void Update(ComponentLookUp& componentLookUp, float deltaTime);
};
