#pragma once

#include "..\iwphysics.h"

namespace iwphysics {
	enum class friction_combine {
		ADD,
		SUBTRACT,
		MULTIPLY,
		MAX,
		MIN
	};

	enum class bounce_combine {
		ADD,
		SUBTRACT,
		MULTIPLY,
		MAX,
		MIN
	};

	struct physics_material {
		float friction;
		float bounce;
		friction_combine friction_combine;
		bounce_combine bounce_combine;
	};
}