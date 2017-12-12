#pragma once

#ifdef IWENGINE_EXPORTS
#define IWENGINE_API __declspec(dllexport)
#else
#define IWENGINE_API __declspec(dllimport)
#endif  

#include <iostream>

namespace Math {
	struct Vector3 {
		float x, y, z;
		IWENGINE_API static const Vector3 Zero, One, UnitX, UnitY, UnitZ;

		IWENGINE_API Vector3();
		IWENGINE_API Vector3(float xyz);
		IWENGINE_API Vector3(float x, float y, float z);
		IWENGINE_API float Length() const;
		IWENGINE_API float LengthSquared() const;
		IWENGINE_API float LengthFast() const;
		IWENGINE_API Vector3 Normalized() const;
		IWENGINE_API Vector3 NormalizedFast() const;
		IWENGINE_API void Normalize();
		IWENGINE_API void NormalizeFast();
		IWENGINE_API 	float Dot(const Vector3& other) const;
		IWENGINE_API 	Vector3 Cross(const Vector3& other) const;
		IWENGINE_API 	Vector3 operator+(const Vector3& other) const;
		IWENGINE_API 	Vector3 operator-(const Vector3& other) const;
		IWENGINE_API 	Vector3 operator*(const Vector3& other) const;
		IWENGINE_API 	Vector3 operator/(const Vector3& other) const;
		IWENGINE_API 	Vector3 operator+=(const Vector3& other);
		IWENGINE_API 	Vector3 operator-=(const Vector3& other);
		IWENGINE_API 	Vector3 operator*=(const Vector3& other);
		IWENGINE_API 	Vector3 operator/=(const Vector3& other);
		IWENGINE_API 	Vector3 operator+(const float other) const;
		IWENGINE_API 	Vector3 operator-(const float other) const;
		IWENGINE_API 	Vector3 operator*(const float other) const;
		IWENGINE_API 	Vector3 operator/(const float other) const;
		IWENGINE_API 	Vector3 operator+=(const float other);
		IWENGINE_API 	Vector3 operator-=(const float other);
		IWENGINE_API 	Vector3 operator*=(const float other);
		IWENGINE_API 	Vector3 operator/=(const float other);
		IWENGINE_API 	Vector3 operator-() const;
		IWENGINE_API 	bool operator==(const Vector3& other) const;
		IWENGINE_API 	bool operator!=(const Vector3& other) const;
		IWENGINE_API 		bool Equals(const Vector3& other) const;
	};

	IWENGINE_API std::ostream& operator<<(std::ostream &strm, const Vector3 &a);
	IWENGINE_API Vector3 operator+(const float left, const Vector3& right);
	IWENGINE_API 	Vector3 operator-(const float left, const Vector3& right);
	IWENGINE_API Vector3 operator*(const float left, const Vector3& right);
	IWENGINE_API Vector3 operator/(const float left, const Vector3& right);
}