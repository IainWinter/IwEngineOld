#pragma once

#ifdef _DLL
#define IWENGINE_API __declspec(dllexport)
#else
#define IWMATH_API__declspec(dllimport)
#endif

namespace Math {
	#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062f

	IWENGINE_API float InvSqrt(float x);
}