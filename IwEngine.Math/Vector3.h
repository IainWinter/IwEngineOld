#pragma once

#include <iostream>

struct Vector3 {
	float x, y, z;
	static const Vector3 Zero, One, UnitX, UnitY, UnitZ;

	Vector3();
	Vector3(float xyz);
	Vector3(float x, float y, float z);
	float Length();
	float LengthSquared();
	float LengthFast();
	Vector3 Normalized();
	Vector3 NormalizedFast();
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
	Vector3 Add(const Vector3& other) const;
	Vector3 Subtact(const Vector3& other) const;
	Vector3 Multiply(const Vector3& other) const;
	Vector3 Divide(const Vector3& other) const;
	Vector3 operator+(const float other) const;
	Vector3 operator-(const float other) const;
	Vector3 operator*(const float other) const;
	Vector3 operator/(const float other) const;
	Vector3 operator+=(const float other);
	Vector3 operator-=(const float other);
	Vector3 operator*=(const float other);
	Vector3 operator/=(const float other);
	Vector3 Add(const float other) const;
	Vector3 Subtact(const float other) const;
	Vector3 Multiply(const float other) const;
	Vector3 Divide(const float other) const;
	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;
	bool Equals(const Vector3& other) const;
};

std::ostream& operator<<(std::ostream &strm, const Vector3 &a);