#pragma once
#include "IwEngine\Math\Math.h"

class BoundingSphere
{
private:
	const Math::Vector3 center;
	float radius;
public:
	BoundingSphere(float x, float y, float z, float rad) 
	{
		//center = Math::Vector3(x, y, z);
		radius = rad;
	};
};