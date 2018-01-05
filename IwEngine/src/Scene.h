#pragma once

#include <vector>
#include "IwEngine\Object.h"
#include "IwEngine\GameObject.h"
#include "IwEngine\Events\Observable.h"
#include "System.h"
#include "TransformSystem.h"
#include "RenderMeshSystem.h"
#include "IwEngine\Events\EventHandlerBase.h"

class Scene : public Object, Events::Observable<float>, Events::EventHandlerBase<GameObjectEvent> {
public:
	Scene(Events::EventBus& eventBus) : Events::EventHandlerBase<GameObjectEvent>(eventBus) {
		System<Transform>* transformSystem = new System<Transform>();
		System<RenderMesh>* renderMeshSystem = new System<RenderMesh>();

		Attach(transformSystem);
		Attach(renderMeshSystem);

		Notify(5.0f);
	}

	void ProcessEvent(const GameObjectEvent& eventArgs) {
		Utility::Debug("Process GameObject Event!");
	}
};