#pragma once

#include <iostream>
#include "Vector3.h"

struct Vector4 {
	float x, y, z, w;
	static const Vector4 Zero, One, UnitX, UnitY, UnitZ, UnitW;

	Vector4();
	Vector4(float xyzw);
	Vector4(float x, float y, float z, float w);
	Vector3 Xyz() const;
	float Length() const;
	float LengthSquared() const;
	float LengthFast() const;
	Vector4 Normalized() const;
	Vector4 NormalizedFast() const;
	void Normalize();
	void NormalizeFast();
	float Dot(const Vector4& other) const;
	Vector4 operator+(const Vector4& other) const;
	Vector4 operator-(const Vector4& other) const;
	Vector4 operator*(const Vector4& other) const;
	Vector4 operator/(const Vector4& other) const;
	Vector4 operator+=(const Vector4& other);
	Vector4 operator-=(const Vector4& other);
	Vector4 operator*=(const Vector4& other);
	Vector4 operator/=(const Vector4& other);
	Vector4 operator+(const float other) const;
	Vector4 operator-(const float other) const;
	Vector4 operator*(const float other) const;
	Vector4 operator/(const float other) const;
	Vector4 operator+=(const float other);
	Vector4 operator-=(const float other);
	Vector4 operator*=(const float other);
	Vector4 operator/=(const float other);
	Vector4 operator-() const;
	bool operator==(const Vector4& other) const;
	bool operator!=(const Vector4& other) const;
	bool Equals(const Vector4& other) const;
};

std::ostream& operator<<(std::ostream &strm, const Vector4 &a);
Vector4 operator+(const float left, const Vector4& right);
Vector4 operator-(const float left, const Vector4& right);
Vector4 operator*(const float left, const Vector4& right);
Vector4 operator/(const float left, const Vector4& right);