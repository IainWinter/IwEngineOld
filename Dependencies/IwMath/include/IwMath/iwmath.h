#pragma once

#ifdef IWMATH_EXPORTS
#define IWMATH_API __declspec(dllexport)
#else
#define IWMATH_API __declspec(dllimport)
#endif

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062f

namespace iwmath {
	IWMATH_API float invSqrt(float x);
}