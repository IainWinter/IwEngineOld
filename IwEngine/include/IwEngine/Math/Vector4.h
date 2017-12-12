#pragma once

#ifdef IWENGINE_EXPORTS
#define IWENGINE_API __declspec(dllexport)
#else
#define IWENGINE_API __declspec(dllimport)
#endif

#include <iostream>
#include "Vector3.h"

namespace Math {
	struct Vector4 {
		float x, y, z, w;
		IWENGINE_API static const Vector4 Zero, One, UnitX, UnitY, UnitZ, UnitW;

		IWENGINE_API Vector4();
		IWENGINE_API Vector4(float xyzw);
		IWENGINE_API Vector4(float x, float y, float z, float w);
		IWENGINE_API float Length() const;
		IWENGINE_API float LengthSquared() const;
		IWENGINE_API float LengthFast() const;
		IWENGINE_API Vector4 Normalized() const;
		IWENGINE_API Vector4 NormalizedFast() const;
		IWENGINE_API void Normalize();
		IWENGINE_API void NormalizeFast();
		IWENGINE_API float Dot(const Vector4& other) const;
		IWENGINE_API Vector3 Xyz() const;
		IWENGINE_API Vector4 operator+(const Vector4& other) const;
		IWENGINE_API Vector4 operator-(const Vector4& other) const;
		IWENGINE_API Vector4 operator*(const Vector4& other) const;
		IWENGINE_API Vector4 operator/(const Vector4& other) const;
		IWENGINE_API Vector4 operator+=(const Vector4& other);
		IWENGINE_API Vector4 operator-=(const Vector4& other);
		IWENGINE_API Vector4 operator*=(const Vector4& other);
		IWENGINE_API Vector4 operator/=(const Vector4& other);
		IWENGINE_API Vector4 operator+(const float other) const;
		IWENGINE_API Vector4 operator-(const float other) const;
		IWENGINE_API Vector4 operator*(const float other) const;
		IWENGINE_API Vector4 operator/(const float other) const;
		IWENGINE_API Vector4 operator+=(const float other);
		IWENGINE_API Vector4 operator-=(const float other);
		IWENGINE_API Vector4 operator*=(const float other);
		IWENGINE_API Vector4 operator/=(const float other);
		IWENGINE_API Vector4 operator-() const;
		IWENGINE_API bool operator==(const Vector4& other) const;
		IWENGINE_API bool operator!=(const Vector4& other) const;
		IWENGINE_API bool Equals(const Vector4& other) const;
	};

	IWENGINE_API std::ostream& operator<<(std::ostream &strm, const Vector4 &a);
	IWENGINE_API Vector4 operator+(const float left, const Vector4& right);
	IWENGINE_API Vector4 operator-(const float left, const Vector4& right);
	IWENGINE_API Vector4 operator*(const float left, const Vector4& right);
	IWENGINE_API Vector4 operator/(const float left, const Vector4& right);
}