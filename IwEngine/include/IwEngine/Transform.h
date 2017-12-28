#pragma once

#include "Component.h"
#include "Math\Vector3.h"
#include "Math\Quaternion.h"

class IWENGINE_API Transform : public Component {
private:
	Math::Vector3 position;
	Math::Quaternion rotation;
public:
	Transform(GameObject& gameObject) 
		: Component(gameObject) { }

	Transform(GameObject& gameObject, Math::Vector3 position) 
		: Component(gameObject), position(position) { }

	Transform(GameObject& gameObject, Math::Vector3 position, Math::Quaternion rotation) 
		: Component(gameObject), position(position), rotation(rotation) { }

	inline const Math::Vector3& GetPosition() const { return position; }
	inline Math::Vector3& GetPosition() { return position; }
	inline const Math::Quaternion& GetRotation() const { return rotation; }
	inline Math::Quaternion& GetRotation() { return rotation; }
	inline const Math::Vector3 GetEulerRotation() const { return rotation.ToEulerAngles(); }

	inline void SetPosition(const Math::Vector3& position) { this->position = position; }
	inline void SetRotation(const Math::Quaternion& rotation) { this->rotation = rotation; }
	inline void SetEulerRotation(const Math::Vector3& rotation) { this->rotation = Math::Quaternion::FromEulerAngles(rotation); }

	inline Math::Vector3 Forward() const {
		return Math::Vector3::UnitZ * rotation;
	}

	inline Math::Vector3 Right() const {
		return Math::Vector3::UnitX * rotation;
	}

	inline Math::Vector3 Up() const {
		return Math::Vector3::UnitY * rotation;
	}
};