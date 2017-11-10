#pragma once

#include "Vector3.h"
#include "Quaternion.h"

struct Matrix3x3 {
	Vector3 row0, row1, row2;
	static const Matrix3x3 Zero, Identity;

	Matrix3x3(
		float m00, float m01, float m02,
		float m10, float m11, float m12,
		float m20, float m21, float m22);
	Matrix3x3(Vector3 row0, Vector3 row1, Vector3 row2);
	float Determinant() const;
	float Trace() const;
	void Transpose();
	Matrix3x3 Transposed() const;
	void Invert();
	Matrix3x3 Inverted() const;
	void Normalize();
	Matrix3x3 Normalized() const;
	void ClearRotation();
	Matrix3x3 ClearedRotation() const;
	Vector3 ExtractScale() const;
	Quaternion ExtractRotation() const;
	float& operator()(int row, int col);
	float& m00();
	float& m01();
	float& m02();
	float& m10();
	float& m11();
	float& m12();
	float& m20();
	float& m21();
	float& m22();
	Matrix3x3 operator+(const Matrix3x3& other) const;
	Matrix3x3 operator-(const Matrix3x3& other) const;
	Matrix3x3 operator*(const Matrix3x3& other) const;
	Matrix3x3 operator+=(const Matrix3x3& other);
	Matrix3x3 operator-=(const Matrix3x3& other);
	Matrix3x3 operator*=(const Matrix3x3& other);
	Matrix3x3 operator+(const float other) const;
	Matrix3x3 operator-(const float other) const;
	Matrix3x3 operator*(const float other) const;
	Matrix3x3 operator/(const float other) const;
	Matrix3x3 operator+=(const float other);
	Matrix3x3 operator-=(const float other);
	Matrix3x3 operator*=(const float other);
	Matrix3x3 operator/=(const float other);
	Matrix3x3 operator-() const;
	bool operator==(const Matrix3x3& other) const;
	bool operator!=(const Matrix3x3& other) const;
	bool Equals(const Matrix3x3& other) const;
	static Matrix3x3 CreateFromAxisAngle(float x, float y, float z, float angle);
	static Matrix3x3 CreateFromAxisAngle(const Vector3& axis, float angle);
	static Matrix3x3 CreateFromQuaternion(const Quaternion& quaternion);
	static Matrix3x3 CreateRoatationX(float angle);
	static Matrix3x3 CreateRoatationY(float angle);
	static Matrix3x3 CreateRoatationZ(float angle);
	static Matrix3x3 CreateRoatation(const Vector3& angles);
	static Matrix3x3 CreateRoatation(float x, float y, float z);
	static Matrix3x3 CreateScale(float scale);
	static Matrix3x3 CreateScale(const Vector3& scale);
	static Matrix3x3 CreateScale(float x, float y, float z);
};

std::ostream& operator<<(std::ostream &strm, const Matrix3x3 &a);
Matrix3x3 operator+(const float left, const Matrix3x3& right);
Matrix3x3 operator-(const float left, const Matrix3x3& right);
Matrix3x3 operator*(const float left, const Matrix3x3& right);
Matrix3x3 operator/(const float left, const Matrix3x3& right);
