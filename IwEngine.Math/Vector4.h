#pragma once

#ifdef _DLL
#define IWMATH_API __declspec(dllexport)
#else
#define IWMATH_API__declspec(dllimport)
#endif

#include <iostream>
#include "Vector3.h"

namespace IwMath {
	struct Vector4 {
		float x, y, z, w;
		IWMATH_API static const Vector4 Zero, One, UnitX, UnitY, UnitZ, UnitW;

		IWMATH_API Vector4();
		IWMATH_API Vector4(float xyzw);
		IWMATH_API Vector4(float x, float y, float z, float w);
		IWMATH_API float Length() const;
		IWMATH_API float LengthSquared() const;
		IWMATH_API float LengthFast() const;
		IWMATH_API Vector4 Normalized() const;
		IWMATH_API Vector4 NormalizedFast() const;
		IWMATH_API void Normalize();
		IWMATH_API void NormalizeFast();
		IWMATH_API float Dot(const Vector4& other) const;
		IWMATH_API Vector3 Xyz() const;
		IWMATH_API Vector4 operator+(const Vector4& other) const;
		IWMATH_API Vector4 operator-(const Vector4& other) const;
		IWMATH_API Vector4 operator*(const Vector4& other) const;
		IWMATH_API Vector4 operator/(const Vector4& other) const;
		IWMATH_API Vector4 operator+=(const Vector4& other);
		IWMATH_API Vector4 operator-=(const Vector4& other);
		IWMATH_API Vector4 operator*=(const Vector4& other);
		IWMATH_API Vector4 operator/=(const Vector4& other);
		IWMATH_API Vector4 operator+(const float other) const;
		IWMATH_API Vector4 operator-(const float other) const;
		IWMATH_API Vector4 operator*(const float other) const;
		IWMATH_API Vector4 operator/(const float other) const;
		IWMATH_API Vector4 operator+=(const float other);
		IWMATH_API Vector4 operator-=(const float other);
		IWMATH_API Vector4 operator*=(const float other);
		IWMATH_API Vector4 operator/=(const float other);
		IWMATH_API Vector4 operator-() const;
		IWMATH_API bool operator==(const Vector4& other) const;
		IWMATH_API bool operator!=(const Vector4& other) const;
		IWMATH_API bool Equals(const Vector4& other) const;
	};

	IWMATH_API std::ostream& operator<<(std::ostream &strm, const Vector4 &a);
	IWMATH_API Vector4 operator+(const float left, const Vector4& right);
	IWMATH_API Vector4 operator-(const float left, const Vector4& right);
	IWMATH_API Vector4 operator*(const float left, const Vector4& right);
	IWMATH_API Vector4 operator/(const float left, const Vector4& right);
}