#pragma once

#include <ostream>
#include "IwMath\mathf.h"
#include "IwMath\vector3.h"

namespace math {
	struct IWMATH_API vector4 {
		static const vector4 zero;
		static const vector4 one;
		static const vector4 unitX;
		static const vector4 unitY;
		static const vector4 unitZ;
		static const vector4 unitW;

		float x, y, z, w;

		vector4();
		vector4(float xyzw);
		vector4(const vector3& xyz);
		vector4(const vector3& xyz, float w);
		vector4(float x, float y, float z, float w);

		float length() const;
		float lengthSquared() const;
		float lengthFast() const;
		vector4 normalized() const;
		vector4 normalizedFast() const;
		void normalize();
		void normalizeFast();
		float dot(const vector4& other) const;
		float& operator[](std::size_t index);
		vector4 operator+(const vector4& other) const;
		vector4 operator-(const vector4& other) const;
		vector4 operator*(const vector4& other) const;
		vector4 operator/(const vector4& other) const;
		vector4 operator+=(const vector4& other);
		vector4 operator-=(const vector4& other);
		vector4 operator*=(const vector4& other);
		vector4 operator/=(const vector4& other);
		vector4 operator+(const float& other) const;
		vector4 operator-(const float& other) const;
		vector4 operator*(const float& other) const;
		vector4 operator/(const float& other) const;
		vector4 operator+=(const float& other);
		vector4 operator-=(const float& other);
		vector4 operator*=(const float& other);
		vector4 operator/=(const float& other);
		vector4 operator-() const;
		bool operator==(const vector4& other) const;
		bool operator!=(const vector4& other) const;
		bool equals(const vector4& other) const;

		friend IWMATH_API std::ostream& operator<<(std::ostream& ostream, const vector4& a);
		friend IWMATH_API vector4 operator+(const float& left, const vector4& right);
		friend IWMATH_API vector4 operator-(const float& left, const vector4& right);
		friend IWMATH_API vector4 operator*(const float& left, const vector4& right);
		friend IWMATH_API vector4 operator/(const float& left, const vector4& right);
	};
}