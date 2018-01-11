#pragma once

#include "IwEngine\Events\EventBase.h"

class UpdateEvent : public Events::EventBase<UpdateEvent> {
public:
	float deltaTime;

	UpdateEvent(float deltaTime) : deltaTime(deltaTime) {}
};