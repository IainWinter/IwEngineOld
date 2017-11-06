#pragma once

#include "Vector3.h"
#include "Vector4.h"

struct Quaternion {
	Vector4 xyzw;
	static const Quaternion Identity;

	Quaternion(float x, float y, float z, float w);
	Quaternion(Vector3 xyz, float w);
	Quaternion(Vector4 xyzw);
	float& x();
	float& y();
	float& z();
	float& w();
	const float& x() const;
	const float& y() const;
	const float& z() const;
	const float& w() const;
	Vector3& Xyz();
	const Vector3& Xyz() const;
	float Length() const;
	float LengthSquared() const;
	float LengthFast() const;
	Quaternion Normalized() const;
	Quaternion NormalizedFast() const;
	void Normalize();
	void NormalizeFast();
	Quaternion Inverted() const;
	void Invert();
	Quaternion Conjugated() const;
	void Conjugate();
	Vector4 ToAxisAngle() const;
	Quaternion operator+(const Quaternion& other) const;
	Quaternion operator-(const Quaternion& other) const;
	Quaternion operator*(const Quaternion& other) const;
	Quaternion operator+=(const Quaternion& other);
	Quaternion operator-=(const Quaternion& other);
	Quaternion operator*=(const Quaternion& other);
	Quaternion operator*(const float other);
	Quaternion operator*=(const float other);
	bool operator==(const Quaternion& other) const;
	bool operator!=(const Quaternion& other) const;
	bool Equals(const Quaternion& other) const;
	static Quaternion FromAxisAngle(const Vector3& axis, const float angle);
	static Quaternion FromAxisAngle(const Vector4& axisAngle);
	static Quaternion FromEulerAngles(const float pitch, const float yaw, const float roll);
	static Quaternion FromEulerAngles(const Vector3& eulerAngles);
};

