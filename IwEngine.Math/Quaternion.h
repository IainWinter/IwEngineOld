#pragma once

#include "Vector3.h"
#include "Vector4.h"

struct Quaternion {
	Vector3 xyz;
	float w;
	static const Quaternion Identity;

	Quaternion(float x, float y, float z, float w);
	Quaternion(Vector3 xyz, float w);
	Quaternion(Vector4 xyzw);
	float Length() const;
	float LengthSquared() const;
	float LengthFast() const;
	Quaternion Normalized() const;
	Quaternion NormalizedFast() const;
	void Normalize();
	void NormalizeFast();
	void Invert();
	Quaternion Inverted() const;
	void Conjugate();
	Quaternion Conjugated() const;
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

