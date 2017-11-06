#include "Quaternion.h"
#include "MathHelper.h"

#pragma region Constants

const Quaternion Quaternion::Identity = Vector4(0, 0, 0, 1);

#pragma endregion

#pragma region Constructors

Quaternion::Quaternion(float x, float y, float z, float w) : xyzw(Vector4(x, y, z, w)) {}

Quaternion::Quaternion(Vector3 xyz, float w) : xyzw(Vector4(xyz.x, xyz.y, xyz.z, w)) {}

Quaternion::Quaternion(Vector4 xyzw) : xyzw(xyzw) {}

#pragma endregion

#pragma region Misc

float& Quaternion::x() {
	return xyzw.x;
}

float& Quaternion::y() {
	return xyzw.y;
}

float& Quaternion::z() {
	return xyzw.z;
}

float& Quaternion::w() {
	return xyzw.w;
}

const float& Quaternion::x() const {
	return xyzw.x;
}

const float& Quaternion::y() const {
	return xyzw.y;
}

const float& Quaternion::z() const {
	return xyzw.z;
}

const float& Quaternion::w() const {
	return xyzw.w;
}

Vector3& Quaternion::Xyz() {
	return xyzw.Xyz();
}

const Vector3& Quaternion::Xyz() const {
	return xyzw.Xyz();
}

float Quaternion::Length() const {
	return xyzw.Length();
}

float Quaternion::LengthSquared() const {
	return xyzw.LengthSquared();
}

float Quaternion::LengthFast() const {
	return xyzw.LengthFast();
}

Quaternion Quaternion::Normalized() const {
	return Quaternion(xyzw.Normalized());
}

Quaternion Quaternion::NormalizedFast() const {
	return Quaternion(xyzw.NormalizedFast());
}

void Quaternion::Normalize() {
	xyzw.Normalize();
}

void Quaternion::NormalizeFast() {
	xyzw.NormalizeFast();
}

Quaternion Quaternion::Inverted() const {
	return Quaternion(x(), y(), z(), -w());
}

void Quaternion::Invert() {
	w() = -w();
}

Quaternion Quaternion::Conjugated() const {
	return Quaternion(-x(), -y(), -z(), w());
}

void Quaternion::Conjugate() {
	xyzw.Xyz() = -xyzw.Xyz(); //TODO: No ref
}

Vector4 Quaternion::ToAxisAngle() const {
	Quaternion q = *this;
	if (q.w() > 1) {
		q.Normalize();
	}

	Vector4 result;
	result.w = 2 * acos(q.w());
	float den = sqrt(1 - q.w() * q.w());
	if (den > 0.0001f) {
		result.Xyz() = q.Xyz() / den; //TODO: No ref
	} else {
		result.Xyz() = Vector3::UnitX; //TODO: No ref
	}

	return result;
}

#pragma endregion

#pragma region Operators

Quaternion Quaternion::operator+(const Quaternion& other) const {
	return Quaternion(xyzw + other.xyzw);
}

Quaternion Quaternion::operator-(const Quaternion& other) const {
	return Quaternion(xyzw - other.xyzw);
}

Quaternion Quaternion::operator*(const Quaternion& other) const {
	Vector3 xyz = Vector3(xyzw.x, xyzw.y, xyzw.z);
	Vector3 otherXyz = Vector3(other.xyzw.x, other.xyzw.y, other.xyzw.z);

	return Quaternion(other.w() * xyz + w() * otherXyz + xyz.Cross(otherXyz), w() * other.w() - xyz.Dot(otherXyz));
}

Quaternion Quaternion::operator+=(const Quaternion& other) {
	xyzw += other.xyzw;
	return *this;
}

Quaternion Quaternion::operator-=(const Quaternion& other) {
	xyzw -= xyzw;
	return *this;
}

Quaternion Quaternion::operator*=(const Quaternion& other) {
	Vector3 xyz = Vector3(xyzw.x, xyzw.y, xyzw.z);
	Vector3 otherXyz = Vector3(other.xyzw.x, other.xyzw.y, other.xyzw.z);

	Xyz() = other.w() * xyz + w() * otherXyz + xyz.Cross(otherXyz); //TODO: No ref
	w() = w() * other.w() - xyz.Dot(otherXyz);
	return *this;
}

Quaternion Quaternion::operator*(const float other) {
	return Quaternion(xyzw * other);
}

Quaternion Quaternion::operator*=(const float other) {
	xyzw *= other;
	return *this;
}

bool Quaternion::operator==(const Quaternion& other) const {
	return Equals(other);
}

bool Quaternion::operator!=(const Quaternion& other) const {
	return !Equals(other);
}

bool Quaternion::Equals(const Quaternion& other) const {
	return xyzw == other.xyzw;
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

Quaternion Quaternion::FromEulerAngles(const Vector3& eulerAngles) {
	return FromEulerAngles(eulerAngles.x, eulerAngles.y, eulerAngles.z);
}

#pragma endregion

int main() {
	Quaternion q = Quaternion::FromEulerAngles(45, 45, 0);
	Quaternion q2 = Quaternion::FromEulerAngles(5, 5, 0);

	q.Xyz().x = 1;
	//q *= q2;

	system("PAUSE");
}
