#pragma once

#include <iostream>

struct Vector3 {
	float x, y, z;
	static const Vector3 Zero, One, UnitX, UnitY, UnitZ;

	Vector3();
	Vector3(float xyz);
	Vector3(float x, float y, float z);
	float Length() const;
	float LengthSquared() const;
	float LengthFast() const;
	Vector3 Normalized() const;
	Vector3 NormalizedFast() const;
	void Normalize();
	void NormalizeFast();
	float Dot(const Vector3& other) const;
	Vector3 Cross(const Vector3& other) const;
	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator*(const Vector3& other) const;
	Vector3 operator/(const Vector3& other) const;
	Vector3 operator+=(const Vector3& other);
	Vector3 operator-=(const Vector3& other);
	Vector3 operator*=(const Vector3& other);
	Vector3 operator/=(const Vector3& other);
	Vector3 operator+(const float other) const;
	Vector3 operator-(const float other) const;
	Vector3 operator*(const float other) const;
	Vector3 operator/(const float other) const;
	Vector3 operator+=(const float other);
	Vector3 operator-=(const float other);
	Vector3 operator*=(const float other);
	Vector3 operator/=(const float other);
	Vector3 operator-() const;
	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;
	bool Equals(const Vector3& other) const;
};

std::ostream& operator<<(std::ostream &strm, const Vector3 &a);
Vector3 operator+(const float left, const Vector3& right);
Vector3 operator-(const float left, const Vector3& right);
Vector3 operator*(const float left, const Vector3& right);
Vector3 operator/(const float left, const Vector3& right);