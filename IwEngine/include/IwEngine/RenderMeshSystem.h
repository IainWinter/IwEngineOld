#pragma once

#include "IwEngine\System.h"
#include "IwEngine\RenderMesh.h"
#include "IwEngine\Transform.h"
#include "IwEngine\Utility\Logger.h"

template<>
class IWENGINE_API System<RenderMesh, Transform> : public ISystem {
	virtual void Update(ComponentLookUp& componentLookUp, float deltaTime);
};
