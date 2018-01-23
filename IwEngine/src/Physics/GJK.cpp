#include "GJK.h"

Physics::CollisionData Physics::ColliderGJK(
	const Bounds& bounds1,
	const Bounds& bounds2,
	const Math::Vector3& pos1,
	const Math::Vector3& pos2,
	const Math::Quaternion& rot1,
	const Math::Quaternion& rot2) 
{
	std::vector<Math::Vector3> points(2);
	Math::Vector3 direction = Math::Vector3::UnitX;

	Math::Vector3 support = Support(bounds1, bounds2, direction);
	points.push_back(support);
	direction = -support;

	bool colliding = false;
	int count = 0;

	while (!colliding) {
		count++;
		Math::Vector3 a = Support(bounds1, bounds2, direction);

		if (a.Dot(direction) <= 0) {
			break;
		}

		points.push_back(a);

		//Simplex checks
		switch (points.size()) {
			case 2: direction = Simplex(a, points[0]); break;
			case 3: direction = Simplex(a, points[1], points[0]); break;
			case 4: {
				direction = Simplex(a, points[2], points[1], points[0]);
				if (direction == 0) {
					colliding = true;
				} else {
					points.erase(points.begin());
				}

				break;
			}
		}
	}
}

Math::Vector3 Physics::Support(const Bounds& bounds1, const Bounds& bounds2, const Math::Vector3& direction) {
	return Math::Vector3();
}

Math::Vector3 Physics::Simplex(const Math::Vector3& a, const Math::Vector3& b) {
	return Math::Vector3();
}

Math::Vector3 Physics::Simplex(const Math::Vector3& a, const Math::Vector3& b, const Math::Vector3& c) {
	return Math::Vector3();
}

Math::Vector3 Physics::Simplex(const Math::Vector3& a, const Math::Vector3& b, const Math::Vector3& c, const Math::Vector3& d) {
	return Math::Vector3();
}
