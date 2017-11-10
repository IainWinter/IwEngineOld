#pragma once

#include <iostream>

namespace IwMath {
	struct Vector2 {
		float x, y;
		static const Vector2 Zero, One, UnitX, UnitY;

		Vector2();
		Vector2(float xy);
		Vector2(float x, float y);
		float Length() const;
		float LengthSquared() const;
		float LengthFast() const;
		Vector2 NormalRight() const;
		Vector2 NormalLeft() const;
		Vector2 Normalized() const;
		Vector2 NormalizedFast() const;
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
		Vector2 operator+(const float other) const;
		Vector2 operator-(const float other) const;
		Vector2 operator*(const float other) const;
		Vector2 operator/(const float other) const;
		Vector2 operator+=(const float other);
		Vector2 operator-=(const float other);
		Vector2 operator*=(const float other);
		Vector2 operator/=(const float other);
		Vector2 operator-() const;
		bool operator==(const Vector2& other) const;
		bool operator!=(const Vector2& other) const;
		bool Equals(const Vector2& other) const;
	};

	std::ostream& operator<<(std::ostream &strm, const Vector2 &a);
	Vector2 operator+(const float left, const Vector2& right);
	Vector2 operator-(const float left, const Vector2& right);
	Vector2 operator*(const float left, const Vector2& right);
	Vector2 operator/(const float left, const Vector2& right);
}