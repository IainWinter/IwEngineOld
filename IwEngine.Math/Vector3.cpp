#include "Vector3.h"
#include "MathHelper.h"
#include <cmath>

#pragma region Constants

const Vector3 Vector3::Zero = Vector3(0, 0,  0);
const Vector3 Vector3::One = Vector3(1, 1, 1);
const Vector3 Vector3::UnitX = Vector3(1, 0, 0);
const Vector3 Vector3::UnitY = Vector3(0, 1,  0);
const Vector3 Vector3::UnitZ = Vector3(0, 0, 1);

#pragma endregion

#pragma region Constructors

Vector3::Vector3() {}

Vector3::Vector3(float xyz) : x(xyz), y(xyz), z(xyz) {}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

#pragma endregion

#pragma region Misc

float Vector3::Length() {
	return sqrtf(x * x + y * y + z * z);
}

float Vector3::LengthSquared() {
	return x * x + y * y + z * z;
}

float Vector3::LengthFast() {
	return 1 / InvSqrt(x * x + y * y + z * z);
}

Vector3 Vector3::Normalized() {
	float scale = 1.0f / Length();
	return Vector3(x / scale, y / scale, z / scale);
}

Vector3 Vector3::NormalizedFast() {
	float scale = 1.0f / LengthFast();
	return Vector3(x / scale, y / scale, z / scale);
}

void Vector3::Normalize() {
	float scale = 1.0f / Length();
	x /= scale;
	y /= scale;
	z /= scale;
}

void Vector3::NormalizeFast() {
	float scale = 1.0f / LengthFast();
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

std::ostream& operator<<(std::ostream& ostream, const Vector3& vector) {
	return ostream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
}

#pragma endregion

#pragma region Operators

Vector3 Vector3::operator+(const Vector3& other) const {
	return Add(other);
}

Vector3 Vector3::operator-(const Vector3& other) const {
	return Subtact(other);
}

Vector3 Vector3::operator*(const Vector3& other) const {
	return Multiply(other);
}

Vector3 Vector3::operator/(const Vector3& other) const {
	return Divide(other);
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

Vector3 Vector3::Add(const Vector3& other) const {
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::Subtact(const Vector3& other) const {
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::Multiply(const Vector3& other) const {
	return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::Divide(const Vector3& other) const {
	return Vector3(x / other.x, y / other.y, z / other.z);
}

Vector3 Vector3::operator+(const float other) const {
	return Add(other);
}

Vector3 Vector3::operator-(const float other) const {
	return Subtact(other);
}

Vector3 Vector3::operator*(const float other) const {
	return Multiply(other);
}

Vector3 Vector3::operator/(const float other) const {
	return Divide(other);
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

Vector3 Vector3::Add(const float other) const {
	return Vector3(x + other, y + other, z + other);
}

Vector3 Vector3::Subtact(const float other) const {
	return Vector3(x - other, y - other, z - other);
}

Vector3 Vector3::Multiply(const float other) const {
	return Vector3(x * other, y * other, z * other);
}

Vector3 Vector3::Divide(const float other) const {
	return Vector3(x / other, y / other, z / other);
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

#pragma endregion