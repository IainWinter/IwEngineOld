#pragma once

#include "IwEngine\Component.h"
#include "IwMath\Vector3.h"
#include "IwMath\Quaternion.h"

class Transform : public Component {
private:
	math::vector3 position;
	math::quaternion rotation;
public:
	Transform(GameObject& gameObject)
		: Component(gameObject) {}

	Transform(GameObject& gameObject, math::vector3& position)
		: Component(gameObject), position(position) {}

	Transform(GameObject& gameObject, math::vector3& position, math::quaternion& rotation)
		: Component(gameObject), position(position), rotation(rotation) {}

	inline const math::vector3& GetPosition() const { return position; }
	inline math::vector3& GetPosition() { return position; }
	inline const math::quaternion& GetRotation() const { return rotation; }
	inline math::quaternion& GetRotation() { return rotation; }
	inline const math::vector3 GetEulerRotation() const { return rotation.toEulerAngles(); }

	inline void SetPosition(const math::vector3& position) { this->position = position; }
	inline void SetRotation(const math::quaternion& rotation) { this->rotation = rotation; }
	inline void SetEulerRotation(const math::vector3& rotation) { this->rotation = math::quaternion::fromEulerAngles(rotation); }

	inline math::vector3 Forward() const {
		return math::vector3::unitZ * rotation;
	}

	inline math::vector3 Right() const {
		return math::vector3::unitX * rotation;
	}

	inline math::vector3 Up() const {
		return math::vector3::unitY * rotation;
	}
};