#pragma once

#include "Collider.h"
#include "GameObject.h"
#include "Physics\BoundingBox.h"

class BoxCollider : public Collider {
private:
	Physics::BoundingBox _collider;
	std::vector <Math::Vector3> points;
public:
	BoxCollider(GameObject& gameObject, Physics::BoundingBox _collider)
		: Collider(gameObject), _collider(_collider) {
		points.push_back(_collider.GetMax);
		points.push_back(_collider.GetMin);
	}

	std::vector <Math::Vector3> getPosition() {
		return points; 
	}
	void changePosition(Math::Vector3 translation) {
		points.push_back(points.at(0).operator+=(translation));
		points.push_back(points.at(1).operator+= (translation));
		points.erase(points.at(0));
		points.erase(points.at(1));
	}
};
