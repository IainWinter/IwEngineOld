#pragma once

#include "IwEngine\Component.h"
#include "IwEngine\Physics\BoundingMesh.h"
#include "IwEngine\Physics\CollisionData.h"
#include "IwEngine\Physics\PhysicsMaterial.h"

class Collider : public Component {
private:
	Physics::Bounds* _bounds;
	Physics::PhysicsMaterial* _material;
	Physics::CollisionData* _collisionData;
public:
	Collider(GameObject& gameObject, Physics::Bounds* mesh, Physics::PhysicsMaterial& material)
		: Component(gameObject), _bounds(mesh), _material(new Physics::PhysicsMaterial(material)) 
	{
		_collisionData = new Physics::CollisionData(math::vector3(), false, 0);
	}

	~Collider() {
		delete _bounds;
		delete _material;
		delete _collisionData;
	}

	inline const Physics::Bounds& GetCollider() const {
		return *_bounds;
	}

	inline float GetVolume() const {
		return _bounds->GetVolume();
	}

	inline const Physics::PhysicsMaterial GetMaterial() const {
		return *_material;
	}

	inline const Physics::CollisionData* GetCollisionData() const {
		return _collisionData;
	}

	inline void SetCollisionData(Collider* other, math::vector3& axis, bool intersecting, float distance) {
		_collisionData->axis = axis;
		_collisionData->intersects = intersecting;
		_collisionData->distance = distance;
	}
};