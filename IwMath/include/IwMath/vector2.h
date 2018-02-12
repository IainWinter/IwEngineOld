#pragma once

#include <ostream>
#include "iwmath.h"

namespace iwmath {
	struct IWMATH_API vector2 {
		static const vector2 zero;
		static const vector2 one;
		static const vector2 unitX;
		static const vector2 unitY;

		float x, y;

		vector2();
		vector2(float xy);
		vector2(float x, float y);

		float length() const;
		float length_squared() const;
		float lengthFast() const;
		vector2 normal_right() const;
		vector2 normal_left() const;
		vector2 normalized() const;
		vector2 normalized_fast() const;
		void normalize();
		void normalize_fast();
		float dot(const vector2& other) const;
		float cross_length(const vector2& other) const;

		float& operator[](std::size_t index);
		vector2 operator+(const vector2& other) const;
		vector2 operator-(const vector2& other) const;
		vector2 operator*(const vector2& other) const;
		vector2 operator/(const vector2& other) const;
		vector2 operator+=(const vector2& other);
		vector2 operator-=(const vector2& other);
		vector2 operator*=(const vector2& other);
		vector2 operator/=(const vector2& other);
		vector2 operator+(const float& other) const;
		vector2 operator-(const float& other) const;
		vector2 operator*(const float& other) const;
		vector2 operator/(const float& other) const;
		vector2 operator+=(const float& other);
		vector2 operator-=(const float& other);
		vector2 operator*=(const float& other);
		vector2 operator/=(const float& other);
		vector2 operator-() const;

		bool operator==(const vector2& other) const;
		bool operator!=(const vector2& other) const;
		bool equals(const vector2& other) const;

		friend IWMATH_API std::ostream& operator<<(std::ostream& ostream, const vector2& a);
		friend IWMATH_API vector2 operator+(const float& left, const vector2& right);
		friend IWMATH_API vector2 operator-(const float& left, const vector2& right);
		friend IWMATH_API vector2 operator*(const float& left, const vector2& right);
		friend IWMATH_API vector2 operator/(const float& left, const vector2& right);
	};
}