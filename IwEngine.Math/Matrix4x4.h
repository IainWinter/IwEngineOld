#pragma once

#include "Vector3.h"
#include "Quaternion.h"

struct Matrix4x4 {
	Vector4 row0, row1, row2, row3;
	static const Matrix4x4 Zero, Identity;

	Matrix4x4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);
	Matrix4x4(Vector4 row0, Vector4 row1, Vector4 row2, Vector4 row3);
	float Determinant() const;
	float Trace() const;
	void Transpose();
	Matrix4x4 Transposed() const;
	void Invert();
	Matrix4x4 Inverted() const;
	void Normalize();
	Matrix4x4 Normalized() const;
	void ClearRotation();
	Matrix4x4 ClearedRotation() const;
	Vector3 ExtractTranslation() const;
	Vector4 ExtractScale() const;
	Vector4 ExtractProjection() const;
	Quaternion ExtractRotation() const;
	float& operator()(int row, int col);
	float& m00();
	float& m01();
	float& m02();
	float& m03();
	float& m10();
	float& m11();
	float& m12();
	float& m13();
	float& m20();
	float& m21();
	float& m22();
	float& m23();
	float& m30();
	float& m31();
	float& m32();
	float& m33();
	Matrix4x4 operator+(const Matrix4x4& other) const;
	Matrix4x4 operator-(const Matrix4x4& other) const;
	Matrix4x4 operator*(const Matrix4x4& other) const;
	Matrix4x4 operator+=(const Matrix4x4& other);
	Matrix4x4 operator-=(const Matrix4x4& other);
	Matrix4x4 operator*=(const Matrix4x4& other);
	Matrix4x4 operator+(const float other) const;
	Matrix4x4 operator-(const float other) const;
	Matrix4x4 operator*(const float other) const;
	Matrix4x4 operator/(const float other) const;
	Matrix4x4 operator+=(const float other);
	Matrix4x4 operator-=(const float other);
	Matrix4x4 operator*=(const float other);
	Matrix4x4 operator/=(const float other);
	Matrix4x4 operator-() const;
	bool operator==(const Matrix4x4& other) const;
	bool operator!=(const Matrix4x4& other) const;
	bool Equals(const Matrix4x4& other) const;
	static Matrix4x4 CreateFromAxisAngle(float x, float y, float z, float angle);
	static Matrix4x4 CreateFromAxisAngle(const Vector3& axis, float angle);
	static Matrix4x4 CreateFromQuaternion(const Quaternion& quaternion);
	static Matrix4x4 CreateRoatationX(float angle);
	static Matrix4x4 CreateRoatationY(float angle);
	static Matrix4x4 CreateRoatationZ(float angle);
	static Matrix4x4 CreateRoatation(const Vector3& angles);
	static Matrix4x4 CreateRoatation(float x, float y, float z);
	static Matrix4x4 CreateTranslation(const Vector3& translation);
	static Matrix4x4 CreateTranslation(float x, float y, float z);
	static Matrix4x4 CreateScale(float scale);
	static Matrix4x4 CreateScale(const Vector3& scale);
	static Matrix4x4 CreateScale(float x, float y, float z);
	static Matrix4x4 CreateOrthographic(float width, float height, float zNear, float zFar);
	static Matrix4x4 CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNear, float zFar);
	static Matrix4x4 CreatePerspectiveFieldOfView(float fov, float aspect, float zNear, float zFar);
	static Matrix4x4 CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float zNear, float zFar);
	static Matrix4x4 LookAt(Vector3 eye, Vector3 target, Vector3 up);
};

std::ostream& operator<<(std::ostream &strm, const Matrix4x4 &a);
Matrix4x4 operator+(const float left, const Matrix4x4& right);
Matrix4x4 operator-(const float left, const Matrix4x4& right);
Matrix4x4 operator*(const float left, const Matrix4x4& right);
Matrix4x4 operator/(const float left, const Matrix4x4& right);