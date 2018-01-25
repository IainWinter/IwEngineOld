#pragma once

#include <ostream>
#include "IwMath\vector3.h"
#include "IwMath\vector4.h"

namespace math {
	struct IWMATH_API vector3 {
		static const vector3 zero;
		static const vector3 one;
		static const vector3 unitX;
		static const vector3 unitY;
		static const vector3 unitZ;

		float x, y, z;

		vector3();
		vector3(float xyz);
		vector3(const vector4& xyzw);
		vector3(float x, float y, float z);

		float length() const;
		float lengthSquared() const;
		float lengthFast() const;
		vector3 normalized() const;
		vector3 normalizedFast() const;
		vector3 normalized();
		vector3 normalizedFast();
		void normalize();
		void normalizeFast();
		float dot(const vector3& other) const;
		vector3 cross(const vector3& other) const;

		float& operator[](std::size_t index);
		vector3 operator+(const vector3& other) const;
		vector3 operator-(const vector3& other) const;
		vector3 operator*(const vector3& other) const;
		vector3 operator/(const vector3& other) const;
		vector3 operator+=(const vector3& other);
		vector3 operator-=(const vector3& other);
		vector3 operator*=(const vector3& other);
		vector3 operator/=(const vector3& other);
		vector3 operator+(const float& other) const;
		vector3 operator-(const float& other) const;
		vector3 operator*(const float& other) const;
		vector3 operator/(const float& other) const;
		vector3 operator+=(const float& other);
		vector3 operator-=(const float& other);
		vector3 operator*=(const float& other);
		vector3 operator/=(const float& other);
		vector3 operator-() const;
		bool operator==(const vector3& other) const;
		bool operator!=(const vector3& other) const;
		bool equals(const vector3& other) const;

		friend IWMATH_API std::ostream& operator<<(std::ostream& ostream, const vector3& a);
		friend IWMATH_API vector3 operator+(const float& left, const vector3& right);
		friend IWMATH_API vector3 operator-(const float& left, const vector3& right);
		friend IWMATH_API vector3 operator*(const float& left, const vector3& right);
		friend IWMATH_API vector3 operator/(const float& left, const vector3& right);
	};
}