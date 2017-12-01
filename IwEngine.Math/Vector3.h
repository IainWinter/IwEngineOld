#pragma once

#ifdef _DLL
#define IWMATH_API __declspec(dllexport)
#else
#define IWMATH_API__declspec(dllimport)
#endif  

#include <iostream>

namespace IwMath {
	struct Vector3 {
		float x, y, z;
		IWMATH_API static const Vector3 Zero, One, UnitX, UnitY, UnitZ;

		IWMATH_API Vector3();
		IWMATH_API Vector3(float xyz);
		IWMATH_API Vector3(float x, float y, float z);
		IWMATH_API float Length() const;
		IWMATH_API float LengthSquared() const;
		IWMATH_API float LengthFast() const;
		IWMATH_API Vector3 Normalized() const;
		IWMATH_API Vector3 NormalizedFast() const;
		IWMATH_API void Normalize();
		IWMATH_API void NormalizeFast();
		IWMATH_API 	float Dot(const Vector3& other) const;
		IWMATH_API 	Vector3 Cross(const Vector3& other) const;
		IWMATH_API 	Vector3 operator+(const Vector3& other) const;
		IWMATH_API 	Vector3 operator-(const Vector3& other) const;
		IWMATH_API 	Vector3 operator*(const Vector3& other) const;
		IWMATH_API 	Vector3 operator/(const Vector3& other) const;
		IWMATH_API 	Vector3 operator+=(const Vector3& other);
		IWMATH_API 	Vector3 operator-=(const Vector3& other);
		IWMATH_API 	Vector3 operator*=(const Vector3& other);
		IWMATH_API 	Vector3 operator/=(const Vector3& other);
		IWMATH_API 	Vector3 operator+(const float other) const;
		IWMATH_API 	Vector3 operator-(const float other) const;
		IWMATH_API 	Vector3 operator*(const float other) const;
		IWMATH_API 	Vector3 operator/(const float other) const;
		IWMATH_API 	Vector3 operator+=(const float other);
		IWMATH_API 	Vector3 operator-=(const float other);
		IWMATH_API 	Vector3 operator*=(const float other);
		IWMATH_API 	Vector3 operator/=(const float other);
		IWMATH_API 	Vector3 operator-() const;
		IWMATH_API 	bool operator==(const Vector3& other) const;
		IWMATH_API 	bool operator!=(const Vector3& other) const;
		IWMATH_API 		bool Equals(const Vector3& other) const;
	};

	IWMATH_API std::ostream& operator<<(std::ostream &strm, const Vector3 &a);
	IWMATH_API Vector3 operator+(const float left, const Vector3& right);
	IWMATH_API 	Vector3 operator-(const float left, const Vector3& right);
	IWMATH_API Vector3 operator*(const float left, const Vector3& right);
	IWMATH_API Vector3 operator/(const float left, const Vector3& right);
}