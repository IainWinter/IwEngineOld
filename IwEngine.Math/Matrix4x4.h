#pragma once

#ifdef _DLL
#define IWMATH_API __declspec(dllexport)
#else
#define IWMATH_API__declspec(dllimport)
#endif

#include "Vector3.h"
#include "Quaternion.h"

namespace IwMath {
	struct Matrix4x4 {
		Vector4 row0, row1, row2, row3;
		IWMATH_API static const Matrix4x4 Zero, Identity;

		IWMATH_API Matrix4x4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);
		IWMATH_API Matrix4x4(Vector4 row0, Vector4 row1, Vector4 row2, Vector4 row3);
		IWMATH_API float Determinant() const;
		IWMATH_API float Trace() const;
		IWMATH_API void Transpose();
		IWMATH_API Matrix4x4 Transposed() const;
		IWMATH_API void Invert();
		IWMATH_API Matrix4x4 Inverted() const;
		IWMATH_API void Normalize();
		IWMATH_API Matrix4x4 Normalized() const;
		IWMATH_API void ClearRotation();
		IWMATH_API Matrix4x4 ClearedRotation() const;
		IWMATH_API Vector3 ExtractTranslation() const;
		IWMATH_API Vector4 ExtractScale() const;
		IWMATH_API Vector4 ExtractProjection() const;
		IWMATH_API Quaternion ExtractRotation() const;
		IWMATH_API float& operator()(int row, int col);
		IWMATH_API float& m00();
		IWMATH_API float& m01();
		IWMATH_API float& m02();
		IWMATH_API float& m03();
		IWMATH_API float& m10();
		IWMATH_API float& m11();
		IWMATH_API float& m12();
		IWMATH_API float& m13();
		IWMATH_API float& m20();
		IWMATH_API float& m21();
		IWMATH_API float& m22();
		IWMATH_API float& m23();
		IWMATH_API float& m30();
		IWMATH_API float& m31();
		IWMATH_API float& m32();
		IWMATH_API float& m33();
		IWMATH_API Matrix4x4 operator+(const Matrix4x4& other) const;
		IWMATH_API 	Matrix4x4 operator-(const Matrix4x4& other) const;
		IWMATH_API Matrix4x4 operator*(const Matrix4x4& other) const;
		IWMATH_API Matrix4x4 operator+=(const Matrix4x4& other);
		IWMATH_API Matrix4x4 operator-=(const Matrix4x4& other);
		IWMATH_API Matrix4x4 operator*=(const Matrix4x4& other);
		IWMATH_API Matrix4x4 operator+(const float other) const;
		IWMATH_API Matrix4x4 operator-(const float other) const;
		IWMATH_API Matrix4x4 operator*(const float other) const;
		IWMATH_API Matrix4x4 operator/(const float other) const;
		IWMATH_API Matrix4x4 operator+=(const float other);
		IWMATH_API Matrix4x4 operator-=(const float other);
		IWMATH_API Matrix4x4 operator*=(const float other);
		IWMATH_API Matrix4x4 operator/=(const float other);
		IWMATH_API Matrix4x4 operator-() const;
		IWMATH_API bool operator==(const Matrix4x4& other) const;
		IWMATH_API bool operator!=(const Matrix4x4& other) const;
		IWMATH_API bool Equals(const Matrix4x4& other) const;
		IWMATH_API static Matrix4x4 CreateFromAxisAngle(float x, float y, float z, float angle);
		IWMATH_API static Matrix4x4 CreateFromAxisAngle(const Vector3& axis, float angle);
		IWMATH_API static Matrix4x4 CreateFromQuaternion(const Quaternion& quaternion);
		IWMATH_API static Matrix4x4 CreateRoatationX(float angle);
		IWMATH_API static Matrix4x4 CreateRoatationY(float angle);
		IWMATH_API static Matrix4x4 CreateRoatationZ(float angle);
		IWMATH_API static Matrix4x4 CreateRoatation(const Vector3& angles);
		IWMATH_API static Matrix4x4 CreateRoatation(float x, float y, float z);
		IWMATH_API static Matrix4x4 CreateTranslation(const Vector3& translation);
		IWMATH_API static Matrix4x4 CreateTranslation(float x, float y, float z);
		IWMATH_API static Matrix4x4 CreateScale(float scale);
		IWMATH_API static Matrix4x4 CreateScale(const Vector3& scale);
		IWMATH_API static Matrix4x4 CreateScale(float x, float y, float z);
		IWMATH_API static Matrix4x4 CreateOrthographic(float width, float height, float zNear, float zFar);
		IWMATH_API static Matrix4x4 CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNear, float zFar);
		IWMATH_API static Matrix4x4 CreatePerspectiveFieldOfView(float fov, float aspect, float zNear, float zFar);
		IWMATH_API static Matrix4x4 CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float zNear, float zFar);
		IWMATH_API static Matrix4x4 LookAt(Vector3 eye, Vector3 target, Vector3 up);
	};

	IWMATH_API std::ostream& operator<<(std::ostream &strm, const Matrix4x4 &a);
	IWMATH_API Matrix4x4 operator+(const float left, const Matrix4x4& right);
	IWMATH_API Matrix4x4 operator-(const float left, const Matrix4x4& right);
	IWMATH_API Matrix4x4 operator*(const float left, const Matrix4x4& right);
	IWMATH_API Matrix4x4 operator/(const float left, const Matrix4x4& right);
}