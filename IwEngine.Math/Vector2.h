#pragma once

#ifdef _DLL
#define IWMATH_API __declspec(dllexport)
#else
#define IWMATH_API__declspec(dllimport)
#endif

#include <iostream>

namespace IwMath {
	struct Vector2 {
		float x, y;
		IWMATH_API static const Vector2 Zero, One, UnitX, UnitY;

		IWMATH_API Vector2();
		IWMATH_API Vector2(float xy);
		IWMATH_API Vector2(float x, float y);
		IWMATH_API float Length() const;
		IWMATH_API float LengthSquared() const;
		IWMATH_API float LengthFast() const;
		IWMATH_API Vector2 NormalRight() const;
		IWMATH_API Vector2 NormalLeft() const;
		IWMATH_API Vector2 Normalized() const;
		IWMATH_API Vector2 NormalizedFast() const;
		IWMATH_API void Normalize();
		IWMATH_API void NormalizeFast();
		IWMATH_API float Dot(const Vector2& other) const;
		IWMATH_API float CrossLength(const Vector2& other) const;
		IWMATH_API Vector2 operator+(const Vector2& other) const;
		IWMATH_API Vector2 operator-(const Vector2& other) const;
		IWMATH_API Vector2 operator*(const Vector2& other) const;
		IWMATH_API Vector2 operator/(const Vector2& other) const;
		IWMATH_API Vector2 operator+=(const Vector2& other);
		IWMATH_API Vector2 operator-=(const Vector2& other);
		IWMATH_API Vector2 operator*=(const Vector2& other);
		IWMATH_API Vector2 operator/=(const Vector2& other);
		IWMATH_API Vector2 operator+(const float other) const;
		IWMATH_API Vector2 operator-(const float other) const;
		IWMATH_API Vector2 operator*(const float other) const;
		IWMATH_API Vector2 operator/(const float other) const;
		IWMATH_API Vector2 operator+=(const float other);
		IWMATH_API Vector2 operator-=(const float other);
		IWMATH_API Vector2 operator*=(const float other);
		IWMATH_API Vector2 operator/=(const float other);
		IWMATH_API Vector2 operator-() const;
		IWMATH_API bool operator==(const Vector2& other) const;
		IWMATH_API bool operator!=(const Vector2& other) const;
		IWMATH_API bool Equals(const Vector2& other) const;
	};

	IWMATH_API std::ostream& operator<<(std::ostream &strm, const Vector2 &a);
	IWMATH_API Vector2 operator+(const float left, const Vector2& right);
	IWMATH_API Vector2 operator-(const float left, const Vector2& right);
	IWMATH_API Vector2 operator*(const float left, const Vector2& right);
	IWMATH_API Vector2 operator/(const float left, const Vector2& right);
}