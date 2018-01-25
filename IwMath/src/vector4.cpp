#include "IwMath\vector4.h"
#include <exception>
#include <cmath>

using namespace math;

const vector4 vector4::zero = vector4(0, 0, 0, 0);
const vector4 vector4::one = vector4(1, 1, 1, 1);
const vector4 vector4::unitX = vector4(1, 0, 0, 0);
const vector4 vector4::unitY = vector4(0, 1, 0, 0);
const vector4 vector4::unitZ = vector4(0, 0, 1, 0);
const vector4 vector4::unitW = vector4(0, 0, 0, 1);

vector4::vector4() 
	: x(0), y(0), z(0), w(0) {}

vector4::vector4(float xyzw) 
	: x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}

vector4::vector4(const vector3& xyz) 
	: x(xyz.x), y(xyz.y), z(xyz.z), w(0) {}

vector4::vector4(const vector3& xyz, float w) 
	: x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

vector4::vector4(float x, float y, float z, float w) 
	: x(x), y(y), z(z), w(w) {}

float vector4::length() const {
	return sqrtf(x * x + y * y + z * z + w * w);
}

float vector4::lengthSquared() const {
	return x * x + y * y + z * z + w * w;
}

float vector4::lengthFast() const {
	return 1 / invSqrt(x * x + y * y + z * z + w * w);
}

vector4 vector4::normalized() const {
	float scale = length();
	return vector4(x / scale, y / scale, z / scale, w / scale);
}

vector4 vector4::normalizedFast() const {
	float scale = lengthFast();
	return vector4(x / scale, y / scale, z / scale, w / scale);
}

void vector4::normalize() {
	float scale = length();
	x /= scale;
	y /= scale;
	z /= scale;
	w /= scale;
}

void vector4::normalizeFast() {
	float scale = lengthFast();
	x /= scale;
	y /= scale;
	z /= scale;
	w /= scale;
}

float vector4::dot(const vector4& other) const {
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

float& math::vector4::operator[](std::size_t index) {
	if (index == 0) return x;
	else if (index == 1) return y;
	else if (index == 2) return z;
	else if (index == 3) return w;
	throw std::out_of_range("Index out of bounds");
}

vector4 vector4::operator+(const vector4& other) const {
	return vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

vector4 vector4::operator-(const vector4& other) const {
	return vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

vector4 vector4::operator*(const vector4& other) const {
	return vector4(x * other.x, y * other.y, z * other.z, w * other.w);
}

vector4 vector4::operator/(const vector4& other) const {
	return vector4(x / other.x, y / other.y, z / other.z, w / other.w);
}

vector4 vector4::operator+=(const vector4& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

vector4 vector4::operator-=(const vector4& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}

vector4 vector4::operator*=(const vector4& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	w *= other.w;
	return *this;
}

vector4 vector4::operator/=(const vector4& other) {
	x /= other.x;
	y /= other.y;
	z /= other.z;
	w /= other.w;
	return *this;
}

vector4 vector4::operator+(const float& other) const {
	return vector4(x + other, y + other, z + other, w + other);
}

vector4 vector4::operator-(const float& other) const {
	return vector4(x - other, y - other, z - other, w - other);
}

vector4 vector4::operator*(const float& other) const {
	return vector4(x * other, y * other, z * other, w * other);
}

vector4 vector4::operator/(const float& other) const {
	return vector4(x / other, y / other, z / other, w / other);
}

vector4 vector4::operator+=(const float& other) {
	x += other;
	y += other;
	z += other;
	w += other;
	return *this;
}

vector4 vector4::operator-=(const float& other) {
	x -= other;
	y -= other;
	z -= other;
	w -= other;
	return *this;
}

vector4 vector4::operator*=(const float& other) {
	x *= other;
	y *= other;
	z *= other;
	w *= other;
	return *this;
}

vector4 vector4::operator/=(const float& other) {
	x /= other;
	y /= other;
	z /= other;
	w /= other;
	return *this;
}

vector4 vector4::operator-() const {
	return vector4(-x, -y, -z, -w);
}

bool vector4::operator==(const vector4& other) const {
	return equals(other);
}

bool vector4::operator!=(const vector4& other) const {
	return !equals(other);
}

bool vector4::equals(const vector4& other) const {
	return x == other.x&& y == other.y&& z == other.z&& w == other.w;
}

std::ostream& math::operator<<(std::ostream& ostream, const vector4& vector) {
	return ostream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
}

vector4 math::operator+(const float& right, const vector4& left) {
	return left + right;
}

vector4 math::operator-(const float& right, const vector4& left) {
	return left - right;
}

vector4 math::operator*(const float& right, const vector4& left) {
	return left + right;
}

vector4 math::operator/(const float& right, const vector4& left) {
	return left + right;
}