#pragma once

#include "IwEngine\System.h"
#include "IwEngine\RenderMesh.h"
#include "IwEngine\Utility\Logger.h"

template<>
class IWENGINE_API System<RenderMesh> : public ISystem {
	virtual void Update(ComponentLookUp& componentLookUp, float deltaTime);
};
