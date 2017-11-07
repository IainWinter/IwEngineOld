#include "Quaternion.h"
#include "MathHelper.h"

#pragma region Constants

const Quaternion Quaternion::Identity = Vector4(0, 0, 0, 1);

#pragma endregion

#pragma region Constructors

Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Quaternion::Quaternion(Vector3 xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

Quaternion::Quaternion(Vector4 xyzw) : x(xyzw.x), y(xyzw.y), z(xyzw.z), w(xyzw.w) {}

#pragma endregion

#pragma region Misc

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

	// roll (x-axis rotation)
	double sinr = +2.0 * (w * x + y * z);
	double cosr = +1.0 - 2.0 * (x * x + y * y);
	out.x = atan2(sinr, cosr);

	// pitch (y-axis rotation)
	double sinp = +2.0 * (w * y - z * x);
	if (fabs(sinp) >= 1)
		out.y = copysign(3.14159 / 2, sinp); // use 90 degrees if out of range
	else
		out.y = asin(sinp);

	// yaw (z-axis rotation)
	double siny = +2.0 * (w * z + x * y);
	double cosy = +1.0 - 2.0 * (y * y + z * z);
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

Quaternion Quaternion::operator*(const float other) {
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

	return Quaternion(axis.Normalized() * sin(angle / 2), cos(angle / 2));
}

Quaternion Quaternion::FromAxisAngle(const Vector4& axisAngle) {
	return FromAxisAngle(Vector3(axisAngle.x, axisAngle.y, axisAngle.z), axisAngle.w);
}

Quaternion Quaternion::FromEulerAngles(const float pitch, const float yaw, const float roll) {
	Quaternion q(0, 0, 0, 0);
	// Abbreviations for the various angular functions
	float cy = cos(yaw * 0.5);
	float sy = sin(yaw * 0.5);
	float cr = cos(roll * 0.5);
	float sr = sin(roll * 0.5);
	float cp = cos(pitch * 0.5);
	float sp = sin(pitch * 0.5);

	q.w = cy * cr * cp + sy * sr * sp;
	q.x = cy * sr * cp - sy * cr * sp;
	q.y = cy * cr * sp + sy * sr * cp;
	q.z = sy * cr * cp - cy * sr * sp;

	return q;
}

Quaternion Quaternion::FromEulerAngles(const Vector3& eulerAngles) {
	return FromEulerAngles(eulerAngles.x, eulerAngles.y, eulerAngles.z);
}

#pragma endregion

int main() {
	Quaternion q = Quaternion::FromEulerAngles(0.3f, 0, 0.9f);
	Vector3 v = q.ToEulerAngles();
}

Quaternion operator*(const float left, const Quaternion & right) {
	return left * right;
}