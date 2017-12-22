#include "IwEngine\Events\Observable.h"
#include "IwEngine\Events\Observer.h"
#include "IwEngine\Utility\Logger.h"

class ObserverTest : public Observer<int> {
	void Update(const int& i) {
		Utility::Debug(i + "");
	}
};


class ObservableTest : public Observable<int> {
public:
	void Test() {
		int t = 10;
		int& i = t;
		Notify(i);
	}
};

int main() {
	ObserverTest observer = ObserverTest();
	ObservableTest obl = ObservableTest();
	obl.Attach(&observer);
	obl.Test();
}
