#pragma once

#ifdef IWENGINE_EXPORTS
#define IWENGINE_API __declspec(dllexport)
#else
#define IWENGINE_API __declspec(dllimport)
#endif

#include "Vector3.h"
#include "Quaternion.h"

namespace Math {
	struct Matrix3x3 {
		Vector3 row0, row1, row2;
		IWENGINE_API static const Matrix3x3 Zero, Identity;

		IWENGINE_API Matrix3x3(
			float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22);
		IWENGINE_API Matrix3x3(Vector3 row0, Vector3 row1, Vector3 row2);
		IWENGINE_API float Determinant() const;
		IWENGINE_API float Trace() const;
		IWENGINE_API void Transpose();
		IWENGINE_API Matrix3x3 Transposed() const;
		IWENGINE_API void Invert();
		IWENGINE_API Matrix3x3 Inverted() const;
		IWENGINE_API void Normalize();
		IWENGINE_API Matrix3x3 Normalized() const;
		IWENGINE_API void ClearRotation();
		IWENGINE_API Matrix3x3 ClearedRotation() const;
		IWENGINE_API Vector3 ExtractScale() const;
		IWENGINE_API Quaternion ExtractRotation() const;
		IWENGINE_API float& operator()(int row, int col);
		IWENGINE_API float& m00();
		IWENGINE_API float& m01();
		IWENGINE_API float& m02();
		IWENGINE_API float& m10();
		IWENGINE_API float& m11();
		IWENGINE_API float& m12();
		IWENGINE_API float& m20();
		IWENGINE_API float& m21();
		IWENGINE_API float& m22();
		IWENGINE_API Matrix3x3 operator+(const Matrix3x3& other) const;
		IWENGINE_API Matrix3x3 operator-(const Matrix3x3& other) const;
		IWENGINE_API Matrix3x3 operator*(const Matrix3x3& other) const;
		IWENGINE_API Matrix3x3 operator+=(const Matrix3x3& other);
		IWENGINE_API Matrix3x3 operator-=(const Matrix3x3& other);
		IWENGINE_API Matrix3x3 operator*=(const Matrix3x3& other);
		IWENGINE_API Matrix3x3 operator+(const float other) const;
		IWENGINE_API Matrix3x3 operator-(const float other) const;
		IWENGINE_API Matrix3x3 operator*(const float other) const;
		IWENGINE_API Matrix3x3 operator/(const float other) const;
		IWENGINE_API Matrix3x3 operator+=(const float other);
		IWENGINE_API Matrix3x3 operator-=(const float other);
		IWENGINE_API Matrix3x3 operator*=(const float other);
		IWENGINE_API Matrix3x3 operator/=(const float other);
		IWENGINE_API Matrix3x3 operator-() const;
		IWENGINE_API bool operator==(const Matrix3x3& other) const;
		IWENGINE_API bool operator!=(const Matrix3x3& other) const;
		IWENGINE_API bool Equals(const Matrix3x3& other) const;
		IWENGINE_API static Matrix3x3 CreateFromAxisAngle(float x, float y, float z, float angle);
		IWENGINE_API static Matrix3x3 CreateFromAxisAngle(const Vector3& axis, float angle);
		IWENGINE_API static Matrix3x3 CreateFromQuaternion(const Quaternion& quaternion);
		IWENGINE_API static Matrix3x3 CreateRoatationX(float angle);
		IWENGINE_API static Matrix3x3 CreateRoatationY(float angle);
		IWENGINE_API static Matrix3x3 CreateRoatationZ(float angle);
		IWENGINE_API static Matrix3x3 CreateRoatation(const Vector3& angles);
		IWENGINE_API static Matrix3x3 CreateRoatation(float x, float y, float z);
		IWENGINE_API static Matrix3x3 CreateScale(float scale);
		IWENGINE_API static Matrix3x3 CreateScale(const Vector3& scale);
		IWENGINE_API static Matrix3x3 CreateScale(float x, float y, float z);
	};

	IWENGINE_API std::ostream& operator<<(std::ostream &strm, const Matrix3x3 &a);
	IWENGINE_API Matrix3x3 operator+(const float left, const Matrix3x3& right);
	IWENGINE_API Matrix3x3 operator-(const float left, const Matrix3x3& right);
	IWENGINE_API Matrix3x3 operator*(const float left, const Matrix3x3& right);
	IWENGINE_API Matrix3x3 operator/(const float left, const Matrix3x3& right);
}