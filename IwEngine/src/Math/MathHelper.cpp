#include "IwEngine\Math\MathHelper.h"

float Math::InvSqrt(float x) {
	float xhalf = 0.5f * x;
	int i = *(int*)&x;
	i = 0x5f375a86 - (i >> 1);
	x = *(float*)&i;
	x = x * (1.5f - xhalf * x * x);
	return x;
}

float Math::Max(float a, float b) {
	if (a > b) return a;
	return b;
}

float Math::Min(float a, float b) {
	if (a < b) return a;
	return b;
}
