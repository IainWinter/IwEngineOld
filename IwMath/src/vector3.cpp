#include <exception>
#include "IwMath\vector3.h"

using namespace iwmath;

const vector3 vector3::zero = vector3(0, 0, 0);
const vector3 vector3::one = vector3(1, 1, 1);
const vector3 vector3::unitX = vector3(1, 0, 0);
const vector3 vector3::unitY = vector3(0, 1, 0);
const vector3 vector3::unitZ = vector3(0, 0, 1);

vector3::vector3() 
	: x(0), y(0), z(0) {}

vector3::vector3(float xyz) 
	: x(xyz), y(xyz), z(xyz) {}

vector3::vector3(float x, float y, float z) 
	: x(x), y(y), z(z) {}

float vector3::length() const {
	return sqrtf(x * x + y * y + z * z);
}

float vector3::length_squared() const {
	return x * x + y * y + z * z;
}

float vector3::lengthFast() const {
	return 1 / invSqrt(x * x + y * y + z * z);
}

vector3 vector3::normalized() const {
	float scale = length();
	return vector3(x / scale, y / scale, z / scale);
}

vector3 vector3::normalized_fast() const {
	float scale = lengthFast();
	return vector3(x / scale, y / scale, z / scale);
}

vector3 iwmath::vector3::normalized() {
	float scale = length();
	return vector3(x / scale, y / scale, z / scale);
}

vector3 iwmath::vector3::normalized_fast() {
	float scale = lengthFast();
	return vector3(x / scale, y / scale, z / scale);
}

void vector3::normalize() {
	float scale = length();
	x /= scale;
	y /= scale;
	z /= scale;
}

void vector3::normalize_fast() {
	float scale = lengthFast();
	x /= scale;
	y /= scale;
	z /= scale;
}

float vector3::dot(const vector3 & other) const {
	return x * other.x + y * other.y + z * other.z;
}

vector3 vector3::cross(const vector3 & other) const {
	return vector3(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
}

float& iwmath::vector3::operator[](std::size_t index) {
	if (index == 0) return x;
	else if (index == 1) return y;
	else if (index == 2) return z;
	throw std::out_of_range("Index out of bounds");
}

vector3 vector3::operator+(const vector3& other) const {
	return vector3(x + other.x, y + other.y, z + other.z);
}

vector3 vector3::operator-(const vector3& other) const {
	return vector3(x - other.x, y - other.y, z - other.z);
}

vector3 vector3::operator*(const vector3& other) const {
	return vector3(x * other.x, y * other.y, z * other.z);
}

vector3 vector3::operator/(const vector3& other) const {
	return vector3(x / other.x, y / other.y, z / other.z);
}

vector3 vector3::operator+=(const vector3& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

vector3 vector3::operator-=(const vector3& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

vector3 vector3::operator*=(const vector3& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

vector3 vector3::operator/=(const vector3& other) {
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

vector3 vector3::operator+(const float& other) const {
	return vector3(x + other, y + other, z + other);
}

vector3 vector3::operator-(const float& other) const {
	return vector3(x - other, y - other, z - other);
}

vector3 vector3::operator*(const float& other) const {
	return vector3(x * other, y * other, z * other);
}

vector3 vector3::operator/(const float& other) const {
	return vector3(x / other, y / other, z / other);
}

vector3 vector3::operator+=(const float& other) {
	x += other;
	y += other;
	z += other;
	return *this;
}

vector3 vector3::operator-=(const float& other) {
	x -= other;
	y -= other;
	z -= other;
	return *this;
}

vector3 vector3::operator*=(const float& other) {
	x *= other;
	y *= other;
	z *= other;
	return *this;
}

vector3 vector3::operator/=(const float& other) {
	x /= other;
	y /= other;
	z /= other;
	return *this;
}

vector3 vector3::operator-() const {
	return vector3(-x, -y, -z);
}

bool vector3::operator==(const vector3 & other) const {
	return equals(other);
}

bool vector3::operator!=(const vector3 & other) const {
	return !equals(other);
}

bool vector3::equals(const vector3 & other) const {
	return x == other.x && y == other.y && z == other.z;
}

std::ostream& iwmath::operator<<(std::ostream& ostream, const vector3& vector) {
	return ostream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
}

vector3 iwmath::operator+(const float& right, const vector3& left) {
	return left + right;
}

vector3 iwmath::operator-(const float& right, const vector3& left) {
	return left - right;
}

vector3 iwmath::operator*(const float& right, const vector3& left) {
	return left * right;
}

vector3 iwmath::operator/(const float& right, const vector3& left) {
	return left / right;
}