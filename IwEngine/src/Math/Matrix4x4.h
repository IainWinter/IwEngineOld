#pragma once

#ifdef _DLL
#define IWENGINE_API __declspec(dllexport)
#else
#define IWMATH_API__declspec(dllimport)
#endif

#include "Vector3.h"
#include "Quaternion.h"

namespace Math {
	struct Matrix4x4 {
		Vector4 row0, row1, row2, row3;
		IWENGINE_API static const Matrix4x4 Zero, Identity;

		IWENGINE_API Matrix4x4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);
		IWENGINE_API Matrix4x4(Vector4 row0, Vector4 row1, Vector4 row2, Vector4 row3);
		IWENGINE_API float Determinant() const;
		IWENGINE_API float Trace() const;
		IWENGINE_API void Transpose();
		IWENGINE_API Matrix4x4 Transposed() const;
		IWENGINE_API void Invert();
		IWENGINE_API Matrix4x4 Inverted() const;
		IWENGINE_API void Normalize();
		IWENGINE_API Matrix4x4 Normalized() const;
		IWENGINE_API void ClearRotation();
		IWENGINE_API Matrix4x4 ClearedRotation() const;
		IWENGINE_API Vector3 ExtractTranslation() const;
		IWENGINE_API Vector4 ExtractScale() const;
		IWENGINE_API Vector4 ExtractProjection() const;
		IWENGINE_API Quaternion ExtractRotation() const;
		IWENGINE_API float& operator()(int row, int col);
		IWENGINE_API float& m00();
		IWENGINE_API float& m01();
		IWENGINE_API float& m02();
		IWENGINE_API float& m03();
		IWENGINE_API float& m10();
		IWENGINE_API float& m11();
		IWENGINE_API float& m12();
		IWENGINE_API float& m13();
		IWENGINE_API float& m20();
		IWENGINE_API float& m21();
		IWENGINE_API float& m22();
		IWENGINE_API float& m23();
		IWENGINE_API float& m30();
		IWENGINE_API float& m31();
		IWENGINE_API float& m32();
		IWENGINE_API float& m33();
		IWENGINE_API Matrix4x4 operator+(const Matrix4x4& other) const;
		IWENGINE_API 	Matrix4x4 operator-(const Matrix4x4& other) const;
		IWENGINE_API Matrix4x4 operator*(const Matrix4x4& other) const;
		IWENGINE_API Matrix4x4 operator+=(const Matrix4x4& other);
		IWENGINE_API Matrix4x4 operator-=(const Matrix4x4& other);
		IWENGINE_API Matrix4x4 operator*=(const Matrix4x4& other);
		IWENGINE_API Matrix4x4 operator+(const float other) const;
		IWENGINE_API Matrix4x4 operator-(const float other) const;
		IWENGINE_API Matrix4x4 operator*(const float other) const;
		IWENGINE_API Matrix4x4 operator/(const float other) const;
		IWENGINE_API Matrix4x4 operator+=(const float other);
		IWENGINE_API Matrix4x4 operator-=(const float other);
		IWENGINE_API Matrix4x4 operator*=(const float other);
		IWENGINE_API Matrix4x4 operator/=(const float other);
		IWENGINE_API Matrix4x4 operator-() const;
		IWENGINE_API bool operator==(const Matrix4x4& other) const;
		IWENGINE_API bool operator!=(const Matrix4x4& other) const;
		IWENGINE_API bool Equals(const Matrix4x4& other) const;
		IWENGINE_API static Matrix4x4 CreateFromAxisAngle(float x, float y, float z, float angle);
		IWENGINE_API static Matrix4x4 CreateFromAxisAngle(const Vector3& axis, float angle);
		IWENGINE_API static Matrix4x4 CreateFromQuaternion(const Quaternion& quaternion);
		IWENGINE_API static Matrix4x4 CreateRoatationX(float angle);
		IWENGINE_API static Matrix4x4 CreateRoatationY(float angle);
		IWENGINE_API static Matrix4x4 CreateRoatationZ(float angle);
		IWENGINE_API static Matrix4x4 CreateRoatation(const Vector3& angles);
		IWENGINE_API static Matrix4x4 CreateRoatation(float x, float y, float z);
		IWENGINE_API static Matrix4x4 CreateTranslation(const Vector3& translation);
		IWENGINE_API static Matrix4x4 CreateTranslation(float x, float y, float z);
		IWENGINE_API static Matrix4x4 CreateScale(float scale);
		IWENGINE_API static Matrix4x4 CreateScale(const Vector3& scale);
		IWENGINE_API static Matrix4x4 CreateScale(float x, float y, float z);
		IWENGINE_API static Matrix4x4 CreateOrthographic(float width, float height, float zNear, float zFar);
		IWENGINE_API static Matrix4x4 CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNear, float zFar);
		IWENGINE_API static Matrix4x4 CreatePerspectiveFieldOfView(float fov, float aspect, float zNear, float zFar);
		IWENGINE_API static Matrix4x4 CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float zNear, float zFar);
		IWENGINE_API static Matrix4x4 LookAt(Vector3 eye, Vector3 target, Vector3 up);
	};

	IWENGINE_API std::ostream& operator<<(std::ostream &strm, const Matrix4x4 &a);
	IWENGINE_API Matrix4x4 operator+(const float left, const Matrix4x4& right);
	IWENGINE_API Matrix4x4 operator-(const float left, const Matrix4x4& right);
	IWENGINE_API Matrix4x4 operator*(const float left, const Matrix4x4& right);
	IWENGINE_API Matrix4x4 operator/(const float left, const Matrix4x4& right);
}