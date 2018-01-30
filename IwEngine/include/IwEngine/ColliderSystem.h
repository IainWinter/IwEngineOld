#pragma once

#include "IwEngine\System.h"
#include "IwEngine\Collider.h"
#include "IwEngine\Transform.h"

template<>
class IWENGINE_API System<Collider, Transform> : public ISystem {
	void Update(ComponentLookUp& componentLookUp, float deltaTime);
	math::vector3 SimplexDirection(const math::vector3& a, const math::vector3& b);
	math::vector3 SimplexDirection(const math::vector3& a, const math::vector3& b, const math::vector3& c);
	math::vector3 SimplexDirection(const math::vector3& a, const math::vector3& b, const math::vector3& c, const math::vector3& d);
	bool SameDirection(const math::vector3& direction, const math::vector3& ao);
};