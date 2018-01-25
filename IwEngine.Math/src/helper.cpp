#include "IwEngine\math\helper.h"

using namespace math;

float invSqrt(float x) {
	float xhalf = 0.5f * x;
	int i = *(int*)&x;
	i = 0x5f375a86 - (i >> 1);
	x = *(float*)&i;
	x = x * (1.5f - xhalf * x * x);
	return x;
}

float max(float a, float b) {
	if (a > b) return a;
	return b;
}

float min(float a, float b) {
	if (a < b) return a;
	return b;
}
