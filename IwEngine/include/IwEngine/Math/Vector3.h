#pragma once

#include "IwEngine\Common.h"
#include <iostream>

//like this well commented code
namespace Math {
	struct IWENGINE_API Vector3 {
		float x, y, z;
		static const Vector3 Zero;
		static const Vector3 One;
		static const Vector3 UnitX;
		static const Vector3 UnitY;
		static const Vector3 UnitZ;

		Vector3();
		Vector3(float xyz);
		Vector3(float x, float y, float z);
		float Length() const;
		float LengthSquared() const;
		float LengthFast() const;
		Vector3 Normalized() const;
		Vector3 NormalizedFast() const;
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

		friend IWENGINE_API std::ostream& operator<<(std::ostream &strm, const Vector3 &a);
		friend IWENGINE_API Vector3 operator+(const float left, const Vector3& right);
		friend IWENGINE_API Vector3 operator-(const float left, const Vector3& right);
		friend IWENGINE_API Vector3 operator*(const float left, const Vector3& right);
		friend IWENGINE_API Vector3 operator/(const float left, const Vector3& right);
	};
}