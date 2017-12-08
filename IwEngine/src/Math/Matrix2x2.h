#pragma once

#ifdef _DLL
#define IWENGINE_API __declspec(dllexport)
#else
#define IWMATH_API__declspec(dllimport)
#endif

#include "Vector2.h"

namespace Math {
	struct Matrix2x2 {
		Vector2 row0, row1;
		IWENGINE_API static const Matrix2x2 Zero, Identity;

		IWENGINE_API Matrix2x2(
			float m00, float m01,
			float m10, float m11);
		IWENGINE_API Matrix2x2(Vector2 row0, Vector2 row1);
		IWENGINE_API float Determinant() const;
		IWENGINE_API float Trace() const;
		IWENGINE_API void Transpose();
		IWENGINE_API Matrix2x2 Transposed() const;
		IWENGINE_API void Invert();
		IWENGINE_API Matrix2x2 Inverted() const;
		IWENGINE_API void Normalize();
		IWENGINE_API Matrix2x2 Normalized() const;
		IWENGINE_API float& operator()(int row, int col);
		IWENGINE_API float& m00();
		IWENGINE_API float& m01();
		IWENGINE_API float& m10();
		IWENGINE_API float& m11();
		IWENGINE_API Matrix2x2 operator+(const Matrix2x2& other) const;
		IWENGINE_API Matrix2x2 operator-(const Matrix2x2& other) const;
		IWENGINE_API Matrix2x2 operator*(const Matrix2x2& other) const;
		IWENGINE_API Matrix2x2 operator+=(const Matrix2x2& other);
		IWENGINE_API Matrix2x2 operator-=(const Matrix2x2& other);
		IWENGINE_API Matrix2x2 operator*=(const Matrix2x2& other);
		IWENGINE_API Matrix2x2 operator+(const float other) const;
		IWENGINE_API Matrix2x2 operator-(const float other) const;
		IWENGINE_API Matrix2x2 operator*(const float other) const;
		IWENGINE_API Matrix2x2 operator/(const float other) const;
		IWENGINE_API Matrix2x2 operator+=(const float other);
		IWENGINE_API Matrix2x2 operator-=(const float other);
		IWENGINE_API Matrix2x2 operator*=(const float other);
		IWENGINE_API Matrix2x2 operator/=(const float other);
		IWENGINE_API Matrix2x2 operator-() const;
		IWENGINE_API bool operator==(const Matrix2x2& other) const;
		IWENGINE_API bool operator!=(const Matrix2x2& other) const;
		IWENGINE_API bool Equals(const Matrix2x2& other) const;
		IWENGINE_API static Matrix2x2 CreateRoatation(float angle);
		IWENGINE_API static Matrix2x2 CreateScale(float scale);
		IWENGINE_API static Matrix2x2 CreateScale(const Vector2& scale);
		IWENGINE_API static Matrix2x2 CreateScale(float x, float y);
	};

	IWENGINE_API std::ostream& operator<<(std::ostream &strm, const Matrix2x2 &a);
	IWENGINE_API Matrix2x2 operator+(const float left, const Matrix2x2& right);
	IWENGINE_API Matrix2x2 operator-(const float left, const Matrix2x2& right);
	IWENGINE_API Matrix2x2 operator*(const float left, const Matrix2x2& right);
	IWENGINE_API Matrix2x2 operator/(const float left, const Matrix2x2& right);
}