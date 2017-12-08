#pragma once

#ifdef _DLL
#define IWMATH_API __declspec(dllexport)
#else
#define IWMATH_API__declspec(dllimport)
#endif

#include "Vector2.h"

namespace Math {
	struct Matrix2x2 {
		Vector2 row0, row1;
		IWMATH_API static const Matrix2x2 Zero, Identity;

		IWMATH_API Matrix2x2(
			float m00, float m01,
			float m10, float m11);
		IWMATH_API Matrix2x2(Vector2 row0, Vector2 row1);
		IWMATH_API float Determinant() const;
		IWMATH_API float Trace() const;
		IWMATH_API void Transpose();
		IWMATH_API Matrix2x2 Transposed() const;
		IWMATH_API void Invert();
		IWMATH_API Matrix2x2 Inverted() const;
		IWMATH_API void Normalize();
		IWMATH_API Matrix2x2 Normalized() const;
		IWMATH_API float& operator()(int row, int col);
		IWMATH_API float& m00();
		IWMATH_API float& m01();
		IWMATH_API float& m10();
		IWMATH_API float& m11();
		IWMATH_API Matrix2x2 operator+(const Matrix2x2& other) const;
		IWMATH_API Matrix2x2 operator-(const Matrix2x2& other) const;
		IWMATH_API Matrix2x2 operator*(const Matrix2x2& other) const;
		IWMATH_API Matrix2x2 operator+=(const Matrix2x2& other);
		IWMATH_API Matrix2x2 operator-=(const Matrix2x2& other);
		IWMATH_API Matrix2x2 operator*=(const Matrix2x2& other);
		IWMATH_API Matrix2x2 operator+(const float other) const;
		IWMATH_API Matrix2x2 operator-(const float other) const;
		IWMATH_API Matrix2x2 operator*(const float other) const;
		IWMATH_API Matrix2x2 operator/(const float other) const;
		IWMATH_API Matrix2x2 operator+=(const float other);
		IWMATH_API Matrix2x2 operator-=(const float other);
		IWMATH_API Matrix2x2 operator*=(const float other);
		IWMATH_API Matrix2x2 operator/=(const float other);
		IWMATH_API Matrix2x2 operator-() const;
		IWMATH_API bool operator==(const Matrix2x2& other) const;
		IWMATH_API bool operator!=(const Matrix2x2& other) const;
		IWMATH_API bool Equals(const Matrix2x2& other) const;
		IWMATH_API static Matrix2x2 CreateRoatation(float angle);
		IWMATH_API static Matrix2x2 CreateScale(float scale);
		IWMATH_API static Matrix2x2 CreateScale(const Vector2& scale);
		IWMATH_API static Matrix2x2 CreateScale(float x, float y);
	};

	IWMATH_API std::ostream& operator<<(std::ostream &strm, const Matrix2x2 &a);
	IWMATH_API Matrix2x2 operator+(const float left, const Matrix2x2& right);
	IWMATH_API Matrix2x2 operator-(const float left, const Matrix2x2& right);
	IWMATH_API Matrix2x2 operator*(const float left, const Matrix2x2& right);
	IWMATH_API Matrix2x2 operator/(const float left, const Matrix2x2& right);
}