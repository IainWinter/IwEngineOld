#pragma once

#ifdef _DLL
#define IWMATH_API __declspec(dllexport)
#else
#define IWMATH_API__declspec(dllimport)
#endif

#include "Vector3.h"
#include "Vector4.h"

namespace IwMath {
	struct Quaternion {
		float x, y, z, w;
		IWMATH_API static const Quaternion Identity;

		IWMATH_API Quaternion(float x, float y, float z, float w);
		IWMATH_API Quaternion(Vector3 xyz, float w);
		IWMATH_API Quaternion(Vector4 xyzw);
		IWMATH_API Vector4 Xyzw() const;
		IWMATH_API float Length() const;
		IWMATH_API float LengthSquared() const;
		IWMATH_API float LengthFast() const;
		IWMATH_API Quaternion Normalized() const;
		IWMATH_API Quaternion NormalizedFast() const;
		IWMATH_API void Normalize();
		IWMATH_API void NormalizeFast();
		IWMATH_API Quaternion Inverted() const;
		IWMATH_API void Invert();
		IWMATH_API Quaternion Conjugated() const;
		IWMATH_API void Conjugate();
		IWMATH_API Vector4 ToAxisAngle() const;
		IWMATH_API Vector3 ToEulerAngles() const;
		IWMATH_API Quaternion operator+(const Quaternion& other) const;
		IWMATH_API Quaternion operator-(const Quaternion& other) const;
		IWMATH_API Quaternion operator*(const Quaternion& other) const;
		IWMATH_API Quaternion operator+=(const Quaternion& other);
		IWMATH_API Quaternion operator-=(const Quaternion& other);
		IWMATH_API Quaternion operator*=(const Quaternion& other);
		IWMATH_API Quaternion operator*(const float other) const;
		IWMATH_API Quaternion operator*=(const float other);
		IWMATH_API bool operator==(const Quaternion& other) const;
		IWMATH_API bool operator!=(const Quaternion& other) const;
		IWMATH_API bool Equals(const Quaternion& other) const;
		IWMATH_API static Quaternion FromAxisAngle(const Vector3& axis, const float angle);
		IWMATH_API static Quaternion FromAxisAngle(const Vector4& axisAngle);
		IWMATH_API static Quaternion FromEulerAngles(const float pitch, const float yaw, const float roll);
		IWMATH_API static Quaternion FromEulerAngles(const Vector3& eulerAngles);
	};

	IWMATH_API std::ostream& operator<<(std::ostream &strm, const Quaternion &a);
	IWMATH_API Quaternion operator*(const float left, const Quaternion& right);
}