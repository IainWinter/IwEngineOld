#pragma once

#include "Vector2.h"

struct Matrix2x2 {
	Vector2 row0, row1;
	static const Matrix2x2 Zero, Identity;

	Matrix2x2(
		float m00, float m01, 
		float m10, float m11);
	Matrix2x2(Vector2 row0, Vector2 row1);
	float Determinant() const;
	float Trace() const;
	void Transpose();
	Matrix2x2 Transposed() const;
	void Invert();
	Matrix2x2 Inverted() const;
	void Normalize();
	Matrix2x2 Normalized() const;
	float& m00();
	float& m01();
	float& m10();
	float& m11();
	Matrix2x2 operator+(const Matrix2x2& other) const;
	Matrix2x2 operator-(const Matrix2x2& other) const;
	Matrix2x2 operator*(const Matrix2x2& other) const;
	Matrix2x2 operator+=(const Matrix2x2& other);
	Matrix2x2 operator-=(const Matrix2x2& other);
	Matrix2x2 operator*=(const Matrix2x2& other);
	Matrix2x2 operator+(const float other) const;
	Matrix2x2 operator-(const float other) const;
	Matrix2x2 operator*(const float other) const;
	Matrix2x2 operator/(const float other) const;
	Matrix2x2 operator+=(const float other);
	Matrix2x2 operator-=(const float other);
	Matrix2x2 operator*=(const float other);
	Matrix2x2 operator/=(const float other);
	Matrix2x2 operator-() const;
	bool operator==(const Matrix2x2& other) const;
	bool operator!=(const Matrix2x2& other) const;
	bool Equals(const Matrix2x2& other) const;
	static Matrix2x2 CreateRoatation(float angle);
	static Matrix2x2 CreateScale(float scale);
	static Matrix2x2 CreateScale(float x, float y);
	static Matrix2x2 CreateScale(Vector2 scale);
};

std::ostream& operator<<(std::ostream &strm, const Matrix2x2 &a);
Matrix2x2 operator+(const float left, const Matrix2x2& right);
Matrix2x2 operator-(const float left, const Matrix2x2& right);
Matrix2x2 operator*(const float left, const Matrix2x2& right);
Matrix2x2 operator/(const float left, const Matrix2x2& right);
