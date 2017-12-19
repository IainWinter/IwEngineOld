#pragma once

#include "IwEngine\Common.h"

#include <iostream>
#include "Vector3.h"

namespace Math {
	struct IWENGINE_API Vector4 {
		float x, y, z, w;
		static const Vector4 Zero;
		static const Vector4 One;
		static const Vector4 UnitX;
		static const Vector4 UnitY;
		static const Vector4 UnitZ;
		static const Vector4 UnitW;

		Vector4();
		Vector4(float xyzw);
		Vector4(const Vector3& xyz, float w);
		Vector4(float x, float y, float z, float w);
		float Length() const;
		float LengthSquared() const;
		float LengthFast() const;
		Vector4 Normalized() const;
		Vector4 NormalizedFast() const;
		void Normalize();
		void NormalizeFast();
		float Dot(const Vector4& other) const;
		Vector3 Xyz() const;
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

		friend IWENGINE_API std::ostream& operator<<(std::ostream &strm, const Vector4 &a);
		friend IWENGINE_API Vector4 operator+(const float left, const Vector4& right);
		friend IWENGINE_API Vector4 operator-(const float left, const Vector4& right);
		friend IWENGINE_API Vector4 operator*(const float left, const Vector4& right);
		friend IWENGINE_API Vector4 operator/(const float left, const Vector4& right);
	};

	const Vector4 Vector4::Zero = Vector4(0, 0, 0, 0);
	const Vector4 Vector4::One = Vector4(1, 1, 1, 1);
	const Vector4 Vector4::UnitX = Vector4(1, 0, 0, 0);
	const Vector4 Vector4::UnitY = Vector4(0, 1, 0, 0);
	const Vector4 Vector4::UnitZ = Vector4(0, 0, 1, 0);
	const Vector4 Vector4::UnitW = Vector4(0, 0, 0, 1);
}