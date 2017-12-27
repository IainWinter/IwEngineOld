#include <iostream>
#include "IwEngine\Graphics\Display.h"

#include "IwEngine\Transform.h"

int main() {
	GameObject go = GameObject();
	//go.AddComponent<Transform>();

	Display d = Display();
	d.Start();

	std::cin.get();
}
