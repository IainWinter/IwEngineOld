#pragma once

#ifdef IWENGINE_EXPORTS
#define IWENGINE_API __declspec(dllexport)
#else
#define IWENGINE_API __declspec(dllimport)
#endif

namespace Math {
	#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062f

	IWENGINE_API float InvSqrt(float x);
}