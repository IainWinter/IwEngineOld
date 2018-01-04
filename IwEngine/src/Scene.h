#pragma once

#include <vector>
#include "IwEngine\Object.h"
#include "IwEngine\GameObject.h"
#include "IwEngine\Events\EventHandler.h"
#include "IwEngine\Events\Observable.h"
#include "System.h"
#include "TransformSystem.h"
#include "RenderMeshComponentSystem.h"

class Scene : public Object, Events::Observable<float> {
public:
	Scene() {
		System<Transform>* transformSystem = new System<Transform>();
		System<RenderMeshComponent>* renderMeshComponentSystem = new System<RenderMeshComponent>();

		Attach(transformSystem);
		Attach(renderMeshComponentSystem);

		Notify(5.0f);
	}
};