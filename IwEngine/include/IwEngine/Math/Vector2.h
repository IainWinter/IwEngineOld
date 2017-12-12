#pragma once

#ifdef IWENGINE_EXPORTS
#define IWENGINE_API __declspec(dllexport)
#else
#define IWENGINE_API __declspec(dllimport)
#endif

#include <iostream>

namespace Math {
	struct Vector2 {
		float x, y;
		IWENGINE_API static const Vector2 Zero, One, UnitX, UnitY;

		IWENGINE_API Vector2();
		IWENGINE_API Vector2(float xy);
		IWENGINE_API Vector2(float x, float y);
		IWENGINE_API float Length() const;
		IWENGINE_API float LengthSquared() const;
		IWENGINE_API float LengthFast() const;
		IWENGINE_API Vector2 NormalRight() const;
		IWENGINE_API Vector2 NormalLeft() const;
		IWENGINE_API Vector2 Normalized() const;
		IWENGINE_API Vector2 NormalizedFast() const;
		IWENGINE_API void Normalize();
		IWENGINE_API void NormalizeFast();
		IWENGINE_API float Dot(const Vector2& other) const;
		IWENGINE_API float CrossLength(const Vector2& other) const;
		IWENGINE_API Vector2 operator+(const Vector2& other) const;
		IWENGINE_API Vector2 operator-(const Vector2& other) const;
		IWENGINE_API Vector2 operator*(const Vector2& other) const;
		IWENGINE_API Vector2 operator/(const Vector2& other) const;
		IWENGINE_API Vector2 operator+=(const Vector2& other);
		IWENGINE_API Vector2 operator-=(const Vector2& other);
		IWENGINE_API Vector2 operator*=(const Vector2& other);
		IWENGINE_API Vector2 operator/=(const Vector2& other);
		IWENGINE_API Vector2 operator+(const float other) const;
		IWENGINE_API Vector2 operator-(const float other) const;
		IWENGINE_API Vector2 operator*(const float other) const;
		IWENGINE_API Vector2 operator/(const float other) const;
		IWENGINE_API Vector2 operator+=(const float other);
		IWENGINE_API Vector2 operator-=(const float other);
		IWENGINE_API Vector2 operator*=(const float other);
		IWENGINE_API Vector2 operator/=(const float other);
		IWENGINE_API Vector2 operator-() const;
		IWENGINE_API bool operator==(const Vector2& other) const;
		IWENGINE_API bool operator!=(const Vector2& other) const;
		IWENGINE_API bool Equals(const Vector2& other) const;
	};

	IWENGINE_API std::ostream& operator<<(std::ostream &strm, const Vector2 &a);
	IWENGINE_API Vector2 operator+(const float left, const Vector2& right);
	IWENGINE_API Vector2 operator-(const float left, const Vector2& right);
	IWENGINE_API Vector2 operator*(const float left, const Vector2& right);
	IWENGINE_API Vector2 operator/(const float left, const Vector2& right);
}