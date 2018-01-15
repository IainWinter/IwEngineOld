#include "IwEngine\Math\Vector3.h"
#include "IwEngine\Math\MathHelper.h"
#include <cmath>

using namespace Math;

const Vector3 Vector3::Zero = Vector3(0, 0, 0);
const Vector3 Vector3::One = Vector3(1, 1, 1);
const Vector3 Vector3::UnitX = Vector3(1, 0, 0);
const Vector3 Vector3::UnitY = Vector3(0, 1, 0);
const Vector3 Vector3::UnitZ = Vector3(0, 0, 1);

Vector3::Vector3() : x(0), y(0), z(0) {}

Vector3::Vector3(float xyz) : x(xyz), y(xyz), z(xyz) {}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

float Vector3::Length() const {
	return sqrtf(x * x + y * y + z * z);
}

float Vector3::LengthSquared() const {
	return x * x + y * y + z * z;
}

float Vector3::LengthFast() const {
	return 1 / InvSqrt(x * x + y * y + z * z);
}

Vector3 Vector3::Normalized() const {
	float scale = Length();
	return Vector3(x / scale, y / scale, z / scale);
}

Vector3 Vector3::NormalizedFast() const {
	float scale = LengthFast();
	return Vector3(x / scale, y / scale, z / scale);
}

Vector3 Math::Vector3::Normalized() {
	float scale = Length();
	return Vector3(x / scale, y / scale, z / scale);
}

Vector3 Math::Vector3::NormalizedFast() {
	float scale = LengthFast();
	return Vector3(x / scale, y / scale, z / scale);
}

void Vector3::Normalize() {
	float scale = Length();
	x /= scale;
	y /= scale;
	z /= scale;
}

void Vector3::NormalizeFast() {
	float scale = LengthFast();
	x /= scale;
	y /= scale;
	z /= scale;
}

float Vector3::Dot(const Vector3 & other) const {
	return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::Cross(const Vector3 & other) const {
	return Vector3(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
}

Vector3 Vector3::operator+(const Vector3& other) const {
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const {
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(const Vector3& other) const {
	return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator/(const Vector3& other) const {
	return Vector3(x / other.x, y / other.y, z / other.z);
}

Vector3 Vector3::operator+=(const Vector3& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3 Vector3::operator-=(const Vector3& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vector3 Vector3::operator*=(const Vector3& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

Vector3 Vector3::operator/=(const Vector3& other) {
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

Vector3 Vector3::operator+(const float other) const {
	return Vector3(x + other, y + other, z + other);
}

Vector3 Vector3::operator-(const float other) const {
	return Vector3(x - other, y - other, z - other);
}

Vector3 Vector3::operator*(const float other) const {
	return Vector3(x * other, y * other, z * other);
}

Vector3 Vector3::operator/(const float other) const {
	return Vector3(x / other, y / other, z / other);
}

Vector3 Vector3::operator+=(const float other) {
	x += other;
	y += other;
	z += other;
	return *this;
}

Vector3 Vector3::operator-=(const float other) {
	x -= other;
	y -= other;
	z -= other;
	return *this;
}

Vector3 Vector3::operator*=(const float other) {
	x *= other;
	y *= other;
	z *= other;
	return *this;
}

Vector3 Vector3::operator/=(const float other) {
	x /= other;
	y /= other;
	z /= other;
	return *this;
}

Vector3 Vector3::operator-() const {
	return Vector3(-x, -y, -z);
}

bool Vector3::operator==(const Vector3 & other) const {
	return Equals(other);
}

bool Vector3::operator!=(const Vector3 & other) const {
	return !Equals(other);
}

bool Vector3::Equals(const Vector3 & other) const {
	return x == other.x && y == other.y && z == other.z;
}

std::ostream& Math::operator<<(std::ostream& ostream, const Vector3& vector) {
	return ostream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
}

Vector3 Math::operator+(const float right, const Vector3& left) {
	return left + right;
}

Vector3 Math::operator-(const float right, const Vector3& left) {
	return left - right;
}

Vector3 Math::operator*(const float right, const Vector3& left) {
	return left * right;
}

Vector3 Math::operator/(const float right, const Vector3& left) {
	return left / right;
}