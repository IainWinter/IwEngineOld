#pragma once

#include "IwEngine\Common.h"

namespace Math {
	#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062f

	IWENGINE_API float InvSqrt(float x);
	IWENGINE_API float Max(float a, float b);
	IWENGINE_API float Min(float a, float b);
}