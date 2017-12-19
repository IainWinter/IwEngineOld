#pragma once

#include "IwEngine\Common.h"

#include <iostream>

namespace Math {
	struct IWENGINE_API Vector2 {
		float x, y;
		static const Vector2 Zero;
		static const Vector2 One;
		static const Vector2 UnitX;
		static const Vector2 UnitY;

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

		friend IWENGINE_API std::ostream& operator<<(std::ostream &strm, const Vector2 &a);
		friend IWENGINE_API Vector2 operator+(const float left, const Vector2& right);
		friend IWENGINE_API Vector2 operator-(const float left, const Vector2& right);
		friend IWENGINE_API Vector2 operator*(const float left, const Vector2& right);
		friend IWENGINE_API Vector2 operator/(const float left, const Vector2& right);
	};

	const Vector2 Vector2::Zero = Vector2(0, 0);
	const Vector2 Vector2::One = Vector2(1, 1);
	const Vector2 Vector2::UnitX = Vector2(1, 0);
	const Vector2 Vector2::UnitY = Vector2(0, 1);
}