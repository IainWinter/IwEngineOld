#include "GJK.h"

void Physics::ColliderGJK(const Bounds& bounds1, const Bounds& bounds2, 
	const CollisionTransformation& collisionTrans) 
{
	std::vector<math::vector3> points(2);
	math::vector3 direction = math::vector3::unitX;

	math::vector3 support = Support(bounds1, bounds2, direction, collisionTrans);
	points.push_back(support);
	direction = -support;

	bool colliding = false;
	int count = 0;

	while (!colliding) {
		count++;
		math::vector3 a = Support(bounds1, bounds2, direction, collisionTrans);

		if (a.dot(direction) <= 0) {
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

math::vector3 Physics::Support(const Bounds& bounds1, const Bounds& bounds2, 
	const math::vector3& direction, const CollisionTransformation& collisionTrans) 
{
	return bounds1.GetSupport(direction, collisionTrans.rot1, collisionTrans.pos1) 
		- bounds2.GetSupport(direction, collisionTrans.rot2, collisionTrans.pos2);
}

math::vector3 Physics::Simplex(const math::vector3& a, const math::vector3& b) {
	return math::vector3();
}

math::vector3 Physics::Simplex(const math::vector3& a, const math::vector3& b, const math::vector3& c) {
	return math::vector3();
}

math::vector3 Physics::Simplex(const math::vector3& a, const math::vector3& b, const math::vector3& c, const math::vector3& d) {
	return math::vector3();
}
