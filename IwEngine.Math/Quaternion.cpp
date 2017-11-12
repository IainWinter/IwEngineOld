#include "Quaternion.h"
#include "MathHelper.h"

using namespace IwMath;

#pragma region Constants

const Quaternion Quaternion::Identity = Vector4(0, 0, 0, 1);

#pragma endregion

#pragma region Constructors

Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Quaternion::Quaternion(Vector3 xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

Quaternion::Quaternion(Vector4 xyzw) : x(xyzw.x), y(xyzw.y), z(xyzw.z), w(xyzw.w) {}

#pragma endregion

#pragma region MathFunctions

Vector4 Quaternion::Xyzw() const {
	return Vector4(x, y, z, w);
}

float Quaternion::Length() const {
	return sqrtf(x * x + y * y + z * z + w * w);
}

float Quaternion::LengthSquared() const {
	return x * x + y * y + z * z + w * w;
}

float Quaternion::LengthFast() const {
	return 1 / InvSqrt(x * x + y * y + z * z + w * w);
}

Quaternion Quaternion::Normalized() const {
	float scale = 1.0f / Length();
	return Quaternion(x / scale, y / scale, z / scale, w / scale);
}

Quaternion Quaternion::NormalizedFast() const {
	float scale = 1.0f / LengthFast();
	return Quaternion(x / scale, y / scale, z / scale, w / scale);
}

void Quaternion::Normalize() {
	float scale = 1.0f / Length();
	x /= scale;
	y /= scale;
	z /= scale;
	w /= scale;
}

void Quaternion::NormalizeFast() {
	float scale = 1.0f / LengthFast();
	x /= scale;
	y /= scale;
	z /= scale;
	w /= scale;
}

Quaternion Quaternion::Inverted() const {
	return Quaternion(x, y, z, -w);
}

void Quaternion::Invert() {
	w = -w;
}

Quaternion Quaternion::Conjugated() const {
	return Quaternion(-x, -y, -z, w);
}

void Quaternion::Conjugate() {
	x = -x;
	y = -y;
	z = -z;
}

Vector4 Quaternion::ToAxisAngle() const {
	Quaternion q = *this;
	if (q.w > 1) {
		q.Normalize();
	}

	Vector4 result = Vector4::UnitX;

	float den = sqrt(1 - q.w * q.w);
	if (den > 0.0001f) {
		result.x = q.x / den;
		result.y = q.y / den;
		result.z = q.z / den;
	}

	result.w = 2 * acos(q.w);

	return result;
}

Vector3 Quaternion::ToEulerAngles() const {
	Vector3 out;

	float sinr = 2.0f * (w * x + y * z);
	float cosr = 1.0f - 2.0f * (x * x + y * y);
	out.x = atan2(sinr, cosr);

	float sinp = 2.0f * (w * y - z * x);
	if (fabs(sinp) >= 1) {
		out.y = copysignf(PI / 2, sinp);
	} else {
		out.y = asin(sinp);
	}

	float siny = 2.0f * (w * z + x * y);
	float cosy = 1.0f - 2.0f * (y * y + z * z);
	out.z = atan2(siny, cosy);

	return out;
}

#pragma endregion

#pragma region Operators

Quaternion Quaternion::operator+(const Quaternion& other) const {
	return Quaternion(x + other.x, y + other.y, z + other.z, w + other.w);
}

Quaternion Quaternion::operator-(const Quaternion& other) const {
	return Quaternion(x - other.x, y - other.y, z - other.z, w - other.w);
}

Quaternion Quaternion::operator*(const Quaternion& other) const {
	return Quaternion(
		(other.w * x) + (other.x * w) + (other.y * z) - (other.z * y),
		(other.w * y) + (other.y * w) + (other.z * x) - (other.x * z),
		(other.w * z) + (other.z * w) + (other.x * y) - (other.y * x),
		(other.w * w) - (other.x * x) - (other.y * y) - (other.z * z));
}

Quaternion Quaternion::operator+=(const Quaternion& other) {
	return *this = other + (*this);
}

Quaternion Quaternion::operator-=(const Quaternion& other) {
	return *this = other - (*this);
}

Quaternion Quaternion::operator*=(const Quaternion& other) {
	return *this = other * (*this);
}

Quaternion Quaternion::operator*(const float other) const {
	return Quaternion(x * other, y * other, z * other, w * other);
}

Quaternion Quaternion::operator*=(const float other) {
	return *this = other * (*this);
}

bool Quaternion::operator==(const Quaternion& other) const {
	return Equals(other);
}

bool Quaternion::operator!=(const Quaternion& other) const {
	return !Equals(other);
}

bool Quaternion::Equals(const Quaternion& other) const {
	return x == other.x
		&& y == other.y
		&& z == other.z
		&& w == other.w;
}

#pragma endregion

#pragma region Static

Quaternion Quaternion::FromAxisAngle(const Vector3& axis, const float angle) {
	if (axis.LengthSquared() == 0) {
		return Identity;
	}

	float a = angle / 2;

	return Quaternion(axis.Normalized() * sin(a), cos(a));
}

Quaternion Quaternion::FromAxisAngle(const Vector4& axisAngle) {
	return FromAxisAngle(Vector3(axisAngle.x, axisAngle.y, axisAngle.z), axisAngle.w);
}

Quaternion Quaternion::FromEulerAngles(const float pitch, const float yaw, const float roll) {
	float p = pitch / 2;
	float y = yaw / 2;
	float r = roll / 2;

	float cr = cos(r);
	float sr = sin(r);
	float cp = cos(p);
	float sp = sin(p);
	float cy = cos(y);
	float sy = sin(y);

	return Quaternion(
		cr * sp * cy - sr * cp * sy,
		cr * cp * sy + sr * sp * cy,
		sr * cp * cy - cr * sp * sy,
		cr * cp * cy + sr * sp * sy);
}

Quaternion Quaternion::FromEulerAngles(const Vector3& eulerAngles) {
	return FromEulerAngles(eulerAngles.x, eulerAngles.y, eulerAngles.z);
}

#pragma endregion

std::ostream & IwMath::operator<<(std::ostream & ostream, const Quaternion & quaternion) {
	return ostream << "(" << quaternion.x << ", " << quaternion.y << ", " << quaternion.z << ", " << quaternion.w << ")";
}

Quaternion IwMath::operator*(const float left, const Quaternion& right) {
	return right * left;
}