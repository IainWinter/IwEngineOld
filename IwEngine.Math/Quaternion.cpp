#include "Quaternion.h"
#include "MathHelper.h"

#pragma region Constants

const Quaternion Quaternion::Identity = Vector4(0, 0, 0, 1);

#pragma endregion

#pragma region Constructors

Quaternion::Quaternion(float x, float y, float z, float w) : xyz(Vector3(x, y, z)), w(w) {}

Quaternion::Quaternion(Vector3 xyz, float w) : xyz(xyz), w(w) {}

Quaternion::Quaternion(Vector4 xyzw) : xyz(Vector3(xyzw.x, xyzw.y, xyzw.z)), w(xyzw.w) {}

#pragma endregion

#pragma region Misc

float Quaternion::Length() const {
	return sqrtf(w * w + xyz.LengthSquared());
}

float Quaternion::LengthSquared() const {
	return w * w + xyz.LengthSquared();
}

float Quaternion::LengthFast() const {
	return 1 / InvSqrt(w * w + xyz.LengthSquared());
}

Quaternion Quaternion::Normalized() const {
	float scale = 1.0f / Length();
	return Quaternion(xyz / scale, w / scale);
}

Quaternion Quaternion::NormalizedFast() const {
	float scale = 1.0f / LengthFast();
	return Quaternion(xyz / scale, w / scale);
}

void Quaternion::Normalize() {
	float scale = 1.0f / Length();
	xyz /= scale;
	w /= scale;
}

void Quaternion::NormalizeFast() {
	float scale = 1.0f / LengthFast();
	xyz /= scale;
	w /= scale;
}

void Quaternion::Invert() {
	w = -w;
}

Quaternion Quaternion::Inverted() const {
	return Quaternion(xyz, -w);
}

void Quaternion::Conjugate() {
	xyz = -xyz;
}

Quaternion Quaternion::Conjugated() const {
	return Quaternion(-xyz, w);
}

Vector4 Quaternion::ToAxisAngle() const {
	Quaternion q = *this;
	if (q.w > 1) {
		q.Normalize();
	}

	Vector4 result;
	result.w = 2 * acos(q.w);
	float den = sqrt(1 - q.w * q.w);
	if (den > 0.0001f) {
		result.x = q.xyz.x / den;
		result.y = q.xyz.y / den;
		result.z = q.xyz.z / den;
	} else {
		result.x = 1;
		result.y = 0;
		result.z = 0;
	}

	return result;
}

#pragma endregion

#pragma region Operators

Quaternion Quaternion::operator+(const Quaternion & other) const {
	return Quaternion(xyz + other.xyz, w + other.w);
}

Quaternion Quaternion::operator-(const Quaternion & other) const {
	return Quaternion(xyz - other.xyz, w - other.w);
}

Quaternion Quaternion::operator*(const Quaternion & other) const {
	return Quaternion(other.w * xyz + w * other.xyz + xyz.Cross(other.xyz), w * other.w - xyz.Dot(other.xyz));
}

Quaternion Quaternion::operator+=(const Quaternion & other) {
	xyz += other.xyz;
	w += other.w;
	return *this;
}

Quaternion Quaternion::operator-=(const Quaternion & other) {
	xyz -= other.xyz;
	w -= other.w;
	return *this;
}

Quaternion Quaternion::operator*=(const Quaternion & other) {
	xyz = other.w * xyz + w * other.xyz + xyz.Cross(other.xyz);
	w = w * other.w - xyz.Dot(other.xyz);
	return *this;
}

Quaternion Quaternion::operator*(const float other) {
	return Quaternion(xyz * other, w * other);
}

Quaternion Quaternion::operator*=(const float other) {
	xyz *= other;
	w *= other;
	return *this;
}

bool Quaternion::operator==(const Quaternion & other) const {
	return Equals(other);
}

bool Quaternion::operator!=(const Quaternion & other) const {
	return !Equals(other);
}

bool Quaternion::Equals(const Quaternion & other) const {
	return xyz == other.xyz && w == other.w;
}

#pragma endregion

#pragma region Static

Quaternion Quaternion::FromAxisAngle(const Vector3 & axis, const float angle) {
	if (axis.LengthSquared == 0) {
		return Identity;
	}

	return Quaternion(axis.Normalized() * sin(angle / 2), cos(angle / 2));
}

Quaternion Quaternion::FromAxisAngle(const Vector4 & axisAngle) {
	return FromAxisAngle(Vector3(axisAngle.x, axisAngle.y, axisAngle.z), axisAngle.w);
}

Quaternion Quaternion::FromEulerAngles(const float pitch, const float yaw, const float roll) {
	float c1 = cosf(yaw / 2);
	float c2 = cosf(pitch / 2);
	float c3 = cosf(roll / 2);
	float s1 = sinf(yaw / 2);
	float s2 = sinf(pitch / 2);
	float s3 = sinf(roll / 2);

	return Quaternion(
		s1 * s2 * c3 + c1 * c2 * s3, 
		s1 * c2 * c3 + c1 * s2 * s3, 
		c1 * s2 * c3 - s1 * c2 * s3, 
		c1 * c2 * c3 - s1 * s2 * s3);
}

Quaternion Quaternion::FromEulerAngles(const Vector3 & eulerAngles) {
	return FromEulerAngles(eulerAngles.x, eulerAngles.y, eulerAngles.z);
}

#pragma endregion
