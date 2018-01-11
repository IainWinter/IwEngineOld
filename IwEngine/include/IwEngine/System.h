#pragma once

#include "IwEngine\ComponentLookUp.h"
#include "IwEngine\Events\EventHandlerBase.h"
#include "IwEngine\CommonEvents.h"

class ISystem {

};

template<typename TComponent>
class System : public ISystem, public Events::EventHandlerBase<TComponent> {

};