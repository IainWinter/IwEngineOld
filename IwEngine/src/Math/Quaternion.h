#pragma once

#ifdef _DLL
#define IWENGINE_API __declspec(dllexport)
#else
#define IWMATH_API__declspec(dllimport)
#endif

#include "Vector3.h"
#include "Vector4.h"

namespace Math {
	struct Quaternion {
		float x, y, z, w;
		IWENGINE_API static const Quaternion Identity;

		IWENGINE_API Quaternion(float x, float y, float z, float w);
		IWENGINE_API Quaternion(Vector3 xyz, float w);
		IWENGINE_API Quaternion(Vector4 xyzw);
		IWENGINE_API Vector4 Xyzw() const;
		IWENGINE_API float Length() const;
		IWENGINE_API float LengthSquared() const;
		IWENGINE_API float LengthFast() const;
		IWENGINE_API Quaternion Normalized() const;
		IWENGINE_API Quaternion NormalizedFast() const;
		IWENGINE_API void Normalize();
		IWENGINE_API void NormalizeFast();
		IWENGINE_API Quaternion Inverted() const;
		IWENGINE_API void Invert();
		IWENGINE_API Quaternion Conjugated() const;
		IWENGINE_API void Conjugate();
		IWENGINE_API Vector4 ToAxisAngle() const;
		IWENGINE_API Vector3 ToEulerAngles() const;
		IWENGINE_API Quaternion operator+(const Quaternion& other) const;
		IWENGINE_API Quaternion operator-(const Quaternion& other) const;
		IWENGINE_API Quaternion operator*(const Quaternion& other) const;
		IWENGINE_API Quaternion operator+=(const Quaternion& other);
		IWENGINE_API Quaternion operator-=(const Quaternion& other);
		IWENGINE_API Quaternion operator*=(const Quaternion& other);
		IWENGINE_API Quaternion operator*(const float other) const;
		IWENGINE_API Quaternion operator*=(const float other);
		IWENGINE_API bool operator==(const Quaternion& other) const;
		IWENGINE_API bool operator!=(const Quaternion& other) const;
		IWENGINE_API bool Equals(const Quaternion& other) const;
		IWENGINE_API static Quaternion FromAxisAngle(const Vector3& axis, const float angle);
		IWENGINE_API static Quaternion FromAxisAngle(const Vector4& axisAngle);
		IWENGINE_API static Quaternion FromEulerAngles(const float pitch, const float yaw, const float roll);
		IWENGINE_API static Quaternion FromEulerAngles(const Vector3& eulerAngles);
	};

	IWENGINE_API std::ostream& operator<<(std::ostream &strm, const Quaternion &a);
	IWENGINE_API Quaternion operator*(const float left, const Quaternion& right);
}