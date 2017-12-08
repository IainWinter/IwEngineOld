#include "Math\Vector2.h"

int main() {
	Math::Vector2 v = Math::Vector2(1, 2);
	Math::Vector2 v2 = v + 1;
	float d = v.Dot(v2);
}