#include "IwMath\quaternion.h"
#include "IwMath\matrix3.h"

using namespace math;

const quaternion quaternion::identity = quaternion(0, 0, 0, 1);

quaternion::quaternion() 
	: x(0), y(0), z(0), w(1) {}

quaternion::quaternion(float x, float y, float z, float w) 
	: x(x), y(y), z(z), w(w) {}

quaternion::quaternion(const vector3& xyz, float w) 
	: x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

quaternion::quaternion(const vector4& xyzw) 
	: x(xyzw.x), y(xyzw.y), z(xyzw.z), w(xyzw.w) {}

float quaternion::length() const {
	return sqrtf(x * x + y * y + z * z + w * w);
}

float quaternion::lengthSquared() const {
	return x * x + y * y + z * z + w * w;
}

float quaternion::lengthFast() const {
	return 1 / invSqrt(x * x + y * y + z * z + w * w);
}

quaternion quaternion::normalized() const {
	float scale = 1.0f / length();
	return quaternion(x / scale, y / scale, z / scale, w / scale);
}

quaternion quaternion::normalizedFast() const {
	float scale = 1.0f / lengthFast();
	return quaternion(x / scale, y / scale, z / scale, w / scale);
}

void quaternion::normalize() {
	float scale = 1.0f / length();
	x /= scale;
	y /= scale;
	z /= scale;
	w /= scale;
}

void quaternion::normalizeFast() {
	float scale = 1.0f / lengthFast();
	x /= scale;
	y /= scale;
	z /= scale;
	w /= scale;
}

quaternion quaternion::inverted() const {
	return quaternion(x, y, z, -w);
}

void quaternion::invert() {
	w = -w;
}

quaternion quaternion::conjugated() const {
	return quaternion(-x, -y, -z, w);
}

void quaternion::conjugate() {
	x = -x;
	y = -y;
	z = -z;
}

vector3 math::quaternion::getAxis() const {
	float x = 1.0f - w * w;
	if (x < 0.000001f) {
		return vector3::unitX;
	}

	float x2 = x * x;
	return math::vector3(x, y, z) / x2;
}

vector4 quaternion::toAxisAngle() const {
	quaternion q = *this;
	if (q.w > 1) {
		q.normalize();
	}

	vector3 axis = getAxis();
	return vector4(axis, 2 * acos(q.w));
}

vector3 quaternion::toEulerAngles() const {
	return vector3(
		atan2(2 * x * w - 2 * y * z, 1 - 2 * x * x - 2 * z * z),
		atan2(2 * y * w - 2 * x * z, 1 - 2 * y * y - 2 * z * z),
		asin(2 * x * y + 2 * z * w));
}

quaternion quaternion::operator+(const quaternion& other) const {
	return quaternion(x + other.x, y + other.y, z + other.z, w + other.w);
}

quaternion quaternion::operator-(const quaternion& other) const {
	return quaternion(x - other.x, y - other.y, z - other.z, w - other.w);
}

quaternion quaternion::operator*(const quaternion& other) const {
	return quaternion(
		(other.w * x) + (other.x * w) + (other.y * z) - (other.z * y),
		(other.w * y) + (other.y * w) + (other.z * x) - (other.x * z),
		(other.w * z) + (other.z * w) + (other.x * y) - (other.y * x),
		(other.w * w) - (other.x * x) - (other.y * y) - (other.z * z));
}

quaternion quaternion::operator+=(const quaternion& other) {
	return *this = other + (*this);
}

quaternion quaternion::operator-=(const quaternion& other) {
	return *this = other - (*this);
}

quaternion quaternion::operator*=(const quaternion& other) {
	return *this = other * (*this);
}

quaternion quaternion::operator*(const float& other) const {
	return quaternion(x * other, y * other, z * other, w * other);
}

quaternion quaternion::operator*=(const float& other) {
	return *this = other * (*this);
}

bool quaternion::operator==(const quaternion& other) const {
	return equals(other);
}

bool quaternion::operator!=(const quaternion& other) const {
	return !equals(other);
}

bool quaternion::equals(const quaternion& other) const {
	return x == other.x
		&& y == other.y
		&& z == other.z
		&& w == other.w;
}

quaternion quaternion::fromAxisAngle(const vector3& axis, const float& angle) {
	if (axis.lengthSquared() == 0) {
		return identity;
	}

	float a = angle / 2;

	return quaternion(axis.normalized() * sin(a), cos(a));
}

quaternion quaternion::fromAxisAngle(const vector4& axisAngle) {
	return fromAxisAngle(vector3(axisAngle.x, axisAngle.y, axisAngle.z), axisAngle.w);
}

quaternion quaternion::fromEulerAngles(const float& pitch, const float& yaw, const float& roll) {
	float p = pitch / 2;
	float y = yaw / 2;
	float r = roll / 2;

	float cr = cos(r);
	float sr = sin(r);
	float cp = cos(p);
	float sp = sin(p);
	float cy = cos(y);
	float sy = sin(y);

	return quaternion(
		cr * sp * cy - sr * cp * sy,
		cr * cp * sy + sr * sp * cy,
		sr * cp * cy - cr * sp * sy,
		cr * cp * cy + sr * sp * sy);
}

quaternion quaternion::fromEulerAngles(const vector3& eulerAngles) {
	return fromEulerAngles(eulerAngles.x, eulerAngles.y, eulerAngles.z);
}

std::ostream & math::operator<<(std::ostream & ostream, const quaternion & quaternion) {
	return ostream << "(" << quaternion.x << ", " << quaternion.y << ", " << quaternion.z << ", " << quaternion.w << ")";
}

quaternion math::operator*(const float& left, const quaternion& right) {
	return right * left;
}

vector3 math::operator*(const math::vector3& left, const quaternion& right) {
	float r = right.w;
	float i = right.x;
	float j = right.y;
	float k = right.z;

	float length = right.length();
	float s = 2 * 1 / (length*length);

	math::matrix3 mat = math::matrix3(
		1 - s * (j*j + k*k), s * (i*j - k*r), s * (i*k + j*r),
		s * (i*j + k*r), 1 - s * (i*i + k*k), s * (j*k + i*r),
		s * (i*k - j*r), s * (j*k + i*r), 1 - s * (i*i - j*j)
	);

	return vector3(
		mat(0, 0) * left.x + mat(0, 1) * left.y + mat(0, 2) * left.z,
		mat(1, 0) * left.x + mat(1, 1) * left.y + mat(1, 2) * left.z,
		mat(2, 0) * left.x + mat(2, 1) * left.y + mat(2, 2) * left.z
	);
}
