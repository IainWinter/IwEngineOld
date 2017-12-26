#pragma once
#include "Component.h"
#include "Math\Math.h"

class Transform : public Component {
	Math::Vector3 position;
	Math::Quaternion rotation;
};