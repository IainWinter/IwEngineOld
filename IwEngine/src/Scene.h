#pragma once

#include <vector>
#include "IwEngine\Object.h"
#include "IwEngine\GameObject.h"
#include "IwEngine\Events\EventHandler.h"
#include "System.h"
#include "IwEngine\Events\Observable.h"

class Scene : public Object, Events::Observable<float> {
public:
	Scene() {
		System<Transform>* transformSystem = new System<Transform>();
		
		Attach(transformSystem);

		Notify(5.0f);
	}
};