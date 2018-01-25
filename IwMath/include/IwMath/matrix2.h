#pragma once

#include <ostream>
#include "IwMath\mathf.h"
#include "IwMath\vector2.h"

namespace math {
	struct IWMATH_API matrix2 {
		static const matrix2 identity;

		union {
			float elements[2 * 2];
			vector2 rows[2];
		};

		matrix2();
		matrix2(float diagonal);
		matrix2(float* elements);
		matrix2(vector2& row0, vector2& row1);
		matrix2(
			float m00, float m01,
			float m10, float m11
		);

		float determinant() const;
		float trace() const;
		void transpose();
		matrix2 transposed() const;
		void invert();
		matrix2 inverted() const;
		void normalize();
		matrix2 normalized() const;

		float& operator()(int x, int y);
		matrix2 operator+(const matrix2& other) const;
		matrix2 operator-(const matrix2& other) const;
		matrix2 operator*(const matrix2& other) const;
		matrix2 operator+=(const matrix2& other);
		matrix2 operator-=(const matrix2& other);
		matrix2 operator*=(const matrix2& other);
		matrix2 operator+(const float& other) const;
		matrix2 operator-(const float& other) const;
		matrix2 operator*(const float& other) const;
		matrix2 operator/(const float& other) const;
		matrix2 operator+=(const float& other);
		matrix2 operator-=(const float& other);
		matrix2 operator*=(const float& other);
		matrix2 operator/=(const float& other);
		matrix2 operator-() const;
		bool operator==(const matrix2& other) const;
		bool operator!=(const matrix2& other) const;
		bool Equals(const matrix2& other) const;

		static matrix2 createRoatation(float angle);
		static matrix2 createScale(float scale);
		static matrix2 createScale(const vector2& scale);
		static matrix2 createScale(float x, float y);

		friend IWMATH_API std::ostream& operator<<(std::ostream& stream, const matrix2& a);
		friend IWMATH_API matrix2 operator+(const float& left, const matrix2& right);
		friend IWMATH_API matrix2 operator-(const float& left, const matrix2& right);
		friend IWMATH_API matrix2 operator*(const float& left, const matrix2& right);
		friend IWMATH_API matrix2 operator/(const float& left, const matrix2& right);
	};
}