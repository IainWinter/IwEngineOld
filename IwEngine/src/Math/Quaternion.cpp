#include "IwEngine\Math\Quaternion.h"
#include "IwEngine\Math\MathHelper.h"

using namespace Math;

const Quaternion Quaternion::Identity = Quaternion(0, 0, 0, 1);

Quaternion::Quaternion() : x(0), y(0), z(0), w(1) {}

Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Quaternion::Quaternion(const Vector3& xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

Quaternion::Quaternion(const Vector4& xyzw) : x(xyzw.x), y(xyzw.y), z(xyzw.z), w(xyzw.w) {}

Quaternion& Quaternion::SetXYZ(const Vector3& xyz) {
	x = xyz.x;
	y = xyz.y;
	z = xyz.z;
	return *this;
}

const Vector3 Quaternion::GetXYZ() const {
	return Vector3(x, y, z);
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

Vector3 Math::Quaternion::GetAxis() const {
	float x = 1.0f - w * w;
	if (x < 0.000001f) {
		return Vector3::UnitX;
	}

	float x2 = x * x;
	return GetXYZ() / x2;
}

Vector4 Quaternion::ToAxisAngle() const {
	Quaternion q = *this;
	if (q.w > 1) {
		q.Normalize();
	}

	Vector3 axis = GetAxis();
	return Vector4(axis, 2 * acos(q.w));
}

Vector3 Quaternion::ToEulerAngles() const {
	return Vector3(
		atan2(2 * x * w - 2 * y * z, 1 - 2 * x * x - 2 * z * z),
		atan2(2 * y * w - 2 * x * z, 1 - 2 * y * y - 2 * z * z),
		asin(2 * x * y + 2 * z * w));
}

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

std::ostream & Math::operator<<(std::ostream & ostream, const Quaternion & quaternion) {
	return ostream << "(" << quaternion.x << ", " << quaternion.y << ", " << quaternion.z << ", " << quaternion.w << ")";
}

Quaternion Math::operator*(const float left, const Quaternion& right) {
	return right * left;
}

Vector3 Math::operator*(const Math::Vector3& left, const Quaternion& right) {
	Math::Vector3 vec = right.GetXYZ();
	float scale = right.w;

	return 2.0f * vec.Dot(left) * vec + (scale*scale - vec.Dot(vec)) * left + 2.0f * scale * vec.Cross(left);
}
