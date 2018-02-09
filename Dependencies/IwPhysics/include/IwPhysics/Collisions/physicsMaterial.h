#pragma once

#include "IwPhysics\iwphysics.h"

namespace iwphysics {
	enum class frictionCombine {
		ADD,
		SUBTRACT,
		MULTIPLY,
		MAX,
		MIN
	};

	enum class bounceCombine {
		ADD,
		SUBTRACT,
		MULTIPLY,
		MAX,
		MIN
	};

	struct physicsMaterial {
		float friction;
		float bounce;
		frictionCombine frictionCombine;
		bounceCombine bounceCombine;
	};
}