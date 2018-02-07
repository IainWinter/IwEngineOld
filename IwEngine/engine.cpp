#include "include\IwEngine\engine.h"
#include "IwMath\vector3.h"
#include <iostream>

int test() {
	iwmath::vector3 v = iwmath::vector3::zero;

	std::cout << v;

	std::cin.get();

	return 0;
}