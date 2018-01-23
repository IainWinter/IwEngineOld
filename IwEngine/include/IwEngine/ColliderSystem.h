#pragma once

#include "IwEngine\System.h"
#include "IwEngine\Collider.h"
#include "IwEngine\Transform.h"

template<>
class IWENGINE_API System<Collider, Transform> : public ISystem {
	void Update(ComponentLookUp& componentLookUp, float deltaTime);
	Math::Vector3 SimplexDirection(const Math::Vector3& a, const Math::Vector3& b);
	Math::Vector3 SimplexDirection(const Math::Vector3& a, const Math::Vector3& b, const Math::Vector3& c);
	Math::Vector3 SimplexDirection(const Math::Vector3& a, const Math::Vector3& b, const Math::Vector3& c, const Math::Vector3& d);
	bool SameDirection(const Math::Vector3& direction, const Math::Vector3& ao);
};