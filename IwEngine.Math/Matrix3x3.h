#pragma once

#ifdef _DLL
#define IWMATH_API __declspec(dllexport)
#else
#define IWMATH_API__declspec(dllimport)
#endif

#include "Vector3.h"
#include "Quaternion.h"

namespace IwMath {
	struct Matrix3x3 {
		Vector3 row0, row1, row2;
		IWMATH_API static const Matrix3x3 Zero, Identity;

		IWMATH_API Matrix3x3(
			float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22);
		IWMATH_API Matrix3x3(Vector3 row0, Vector3 row1, Vector3 row2);
		IWMATH_API float Determinant() const;
		IWMATH_API float Trace() const;
		IWMATH_API void Transpose();
		IWMATH_API Matrix3x3 Transposed() const;
		IWMATH_API void Invert();
		IWMATH_API Matrix3x3 Inverted() const;
		IWMATH_API void Normalize();
		IWMATH_API Matrix3x3 Normalized() const;
		IWMATH_API void ClearRotation();
		IWMATH_API Matrix3x3 ClearedRotation() const;
		IWMATH_API Vector3 ExtractScale() const;
		IWMATH_API Quaternion ExtractRotation() const;
		IWMATH_API float& operator()(int row, int col);
		IWMATH_API float& m00();
		IWMATH_API float& m01();
		IWMATH_API float& m02();
		IWMATH_API float& m10();
		IWMATH_API float& m11();
		IWMATH_API float& m12();
		IWMATH_API float& m20();
		IWMATH_API float& m21();
		IWMATH_API float& m22();
		IWMATH_API Matrix3x3 operator+(const Matrix3x3& other) const;
		IWMATH_API Matrix3x3 operator-(const Matrix3x3& other) const;
		IWMATH_API Matrix3x3 operator*(const Matrix3x3& other) const;
		IWMATH_API Matrix3x3 operator+=(const Matrix3x3& other);
		IWMATH_API Matrix3x3 operator-=(const Matrix3x3& other);
		IWMATH_API Matrix3x3 operator*=(const Matrix3x3& other);
		IWMATH_API Matrix3x3 operator+(const float other) const;
		IWMATH_API Matrix3x3 operator-(const float other) const;
		IWMATH_API Matrix3x3 operator*(const float other) const;
		IWMATH_API Matrix3x3 operator/(const float other) const;
		IWMATH_API Matrix3x3 operator+=(const float other);
		IWMATH_API Matrix3x3 operator-=(const float other);
		IWMATH_API Matrix3x3 operator*=(const float other);
		IWMATH_API Matrix3x3 operator/=(const float other);
		IWMATH_API Matrix3x3 operator-() const;
		IWMATH_API bool operator==(const Matrix3x3& other) const;
		IWMATH_API bool operator!=(const Matrix3x3& other) const;
		IWMATH_API bool Equals(const Matrix3x3& other) const;
		IWMATH_API static Matrix3x3 CreateFromAxisAngle(float x, float y, float z, float angle);
		IWMATH_API static Matrix3x3 CreateFromAxisAngle(const Vector3& axis, float angle);
		IWMATH_API static Matrix3x3 CreateFromQuaternion(const Quaternion& quaternion);
		IWMATH_API static Matrix3x3 CreateRoatationX(float angle);
		IWMATH_API static Matrix3x3 CreateRoatationY(float angle);
		IWMATH_API static Matrix3x3 CreateRoatationZ(float angle);
		IWMATH_API static Matrix3x3 CreateRoatation(const Vector3& angles);
		IWMATH_API static Matrix3x3 CreateRoatation(float x, float y, float z);
		IWMATH_API static Matrix3x3 CreateScale(float scale);
		IWMATH_API static Matrix3x3 CreateScale(const Vector3& scale);
		IWMATH_API static Matrix3x3 CreateScale(float x, float y, float z);
	};

	IWMATH_API std::ostream& operator<<(std::ostream &strm, const Matrix3x3 &a);
	IWMATH_API Matrix3x3 operator+(const float left, const Matrix3x3& right);
	IWMATH_API Matrix3x3 operator-(const float left, const Matrix3x3& right);
	IWMATH_API Matrix3x3 operator*(const float left, const Matrix3x3& right);
	IWMATH_API Matrix3x3 operator/(const float left, const Matrix3x3& right);
}