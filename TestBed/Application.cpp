#include <iostream>
#include <vector>
#include "IwEngine\Graphics\Display.h"
#include "IwEngine\Transform.h"
#include "IwEngine\GameObject.h"
#include "IwEngine\Utility\Logger.h"

class CustomComponent : public Component {
public:
	CustomComponent(GameObject& gameObject) : Component(gameObject) {
		Utility::Info(gameObject.GetName());
	}

	void FunctionTest() {
		Utility::Info("Function test!!");
	}
};



int main() {
	GameObject go = GameObject();
	go.AddComponent<CustomComponent>();
	go.AddComponent<Transform>();

	std::vector<CustomComponent*> components = go.GetComponents<CustomComponent>();
	components[0]->FunctionTest();

	Graphics::Display d = Graphics::Display();
	d.Start();
}
