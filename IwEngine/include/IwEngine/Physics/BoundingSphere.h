#pragma once
#include "IwEngine\Math\Math.h"
#include "Physics.h"

namespace Physics {
	class IWENGINE_API BoundingSphere
	{
	private:
		const Math::Vector3 center;
		float radius;
	public:
		BoundingSphere(Math::Vector3& cen, float rad)
		{
			center.Equals(cen);
			radius = rad;
		};
		CollisionData IntersectBS(const BoundingSphere& other);
	
		Math::Vector3 Get_center()
		{
			return center;
		}

		float Get_radius()
		{
			return radius; 
		}
	};
}