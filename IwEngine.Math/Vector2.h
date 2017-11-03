#pragma once

#include <iostream>

struct Vector2 {
	float x, y;
	static const Vector2 Zero, One, UnitX, UnitY;

	Vector2();
	Vector2(float xy);
	Vector2(float x, float y);
	float Length();
	float LengthSquared();
	float LengthFast();
	Vector2 NormalRight();
	Vector2 NormalLeft();
	Vector2 Normalized();
	Vector2 NormalizedFast();
	void Normalize();
	void NormalizeFast();
	float Dot(const Vector2& other) const;
	float CrossLength(const Vector2& other) const;
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(const Vector2& other) const;
	Vector2 operator/(const Vector2& other) const;
	Vector2 operator+=(const Vector2& other);
	Vector2 operator-=(const Vector2& other);
	Vector2 operator*=(const Vector2& other);
	Vector2 operator/=(const Vector2& other);
	Vector2 Add(const Vector2& other) const;
	Vector2 Subtact(const Vector2& other) const;
	Vector2 Multiply(const Vector2& other) const;
	Vector2 Divide(const Vector2& other) const;
	Vector2 operator+(const float other) const;
	Vector2 operator-(const float other) const;
	Vector2 operator*(const float other) const;
	Vector2 operator/(const float other) const;
	Vector2 operator+=(const float other);
	Vector2 operator-=(const float other);
	Vector2 operator*=(const float other);
	Vector2 operator/=(const float other);
	Vector2 Add(const float other) const;
	Vector2 Subtact(const float other) const;
	Vector2 Multiply(const float other) const;
	Vector2 Divide(const float other) const;
	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;
	bool Equals(const Vector2& other) const;
};

std::ostream& operator<<(std::ostream &strm, const Vector2 &a);