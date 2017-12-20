#include "IwEngine\Events\Observable.h"
#include "IwEngine\Events\Observer.h"
#include <iostream>

int main() {
	Observable obs = Observable();
	Observer* o = new Observer();

	obs.Hook(o);

	obs.Fire<int>(5);

	std::cin.get();
}

class ObserverTest : Observer {

};