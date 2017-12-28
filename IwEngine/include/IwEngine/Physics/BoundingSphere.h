#pragma once
#include "IwEngine\Math\Math.h"

class BoundingSphere
{
private:
	const Math::Vector3 center;
	float radius;
public:
	BoundingSphere(Math::Vector3& cen, float rad) 
	{
		//center = cen;
		radius = rad;
	};
	void IntersectBS(const BoundingSphere& other); 
};