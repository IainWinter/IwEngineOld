#pragma once

namespace Physics {
	class IWENGINE_API CollisionData
	{
	private:
		bool intersect;
		float distance;
	public:
		CollisionData(const bool does_intersect, const float dist)
		{
			intersect = does_intersect;
			distance = dist;
		}
		bool GetIntersect() {
			return intersect;
		}
		float GetDistance() {
			return distance;
		}
	};
}