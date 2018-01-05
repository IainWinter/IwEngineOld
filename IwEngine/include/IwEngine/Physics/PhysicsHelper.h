#pragma once

#include "IwEngine\Common.h"

namespace Physics {
	class IWENGINE_API Physics {
	public:
		static float gravity;
	};

	float Physics::gravity = 9.81f;
}