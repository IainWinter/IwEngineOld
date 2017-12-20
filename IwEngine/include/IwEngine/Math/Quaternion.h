#pragma once

#include "IwEngine\Common.h"
#include "Vector3.h"
#include "Vector4.h"

namespace Math {
	struct IWENGINE_API Quaternion {
		float x, y, z, w;
		static const Quaternion Identity;

		Quaternion();
		Quaternion(float x, float y, float z, float w);
		Quaternion(const Vector3& xyz, float w);
		Quaternion(const Vector4& xyzw);

		Quaternion& SetXYZ(const Vector3& xyz);
		const Vector3 GetXYZ() const;
		float Length() const;
		float LengthSquared() const;
		float LengthFast() const;
		Quaternion Normalized() const;
		Quaternion NormalizedFast() const;
		void Normalize();
		void NormalizeFast();
		Quaternion Inverted() const;
		void Invert();
		Quaternion Conjugated() const;
		void Conjugate();
		Vector3 GetAxis() const;
		Vector4 ToAxisAngle() const;
		Vector3 ToEulerAngles() const;

		Quaternion operator+(const Quaternion& other) const;
		Quaternion operator-(const Quaternion& other) const;
		Quaternion operator*(const Quaternion& other) const;
		Quaternion operator+=(const Quaternion& other);
		Quaternion operator-=(const Quaternion& other);
		Quaternion operator*=(const Quaternion& other);
		Quaternion operator*(const float other) const;
		Quaternion operator*=(const float other);
		bool operator==(const Quaternion& other) const;
		bool operator!=(const Quaternion& other) const;
		bool Equals(const Quaternion& other) const;

		static Quaternion FromAxisAngle(const Vector3& axis, const float angle);
		static Quaternion FromAxisAngle(const Vector4& axisAngle);
		static Quaternion FromEulerAngles(const float pitch, const float yaw, const float roll);
		static Quaternion FromEulerAngles(const Vector3& eulerAngles);

		friend IWENGINE_API std::ostream& operator<<(std::ostream &strm, const Quaternion &a);
		friend IWENGINE_API Quaternion operator*(const float left, const Quaternion& right);
	};
}