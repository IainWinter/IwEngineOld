#include "Vector4.h"
#include "MathHelper.h"
#include <cmath>

using namespace IwMath;

#pragma region Constants

const Vector4 Vector4::Zero = Vector4(0, 0, 0, 0);
const Vector4 Vector4::One = Vector4(1, 1, 1, 1);
const Vector4 Vector4::UnitX = Vector4(1, 0, 0, 0);
const Vector4 Vector4::UnitY = Vector4(0, 1, 0, 0);
const Vector4 Vector4::UnitZ = Vector4(0, 0, 1, 0);
const Vector4 Vector4::UnitW = Vector4(0, 0, 0, 1);

#pragma endregion

#pragma region Constructors

Vector4::Vector4() {}

Vector4::Vector4(float xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

#pragma endregion

#pragma region MathFunctions

float Vector4::Length() const {
	return sqrtf(x * x + y * y + z * z + w * w);
}

float Vector4::LengthSquared() const {
	return x * x + y * y + z * z + w * w;
}

float Vector4::LengthFast() const {
	return 1 / InvSqrt(x * x + y * y + z * z + w * w);
}

Vector4 Vector4::Normalized() const {
	float scale = 1.0f / Length();
	return Vector4(x / scale, y / scale, z / scale, w / scale);
}

Vector4 Vector4::NormalizedFast() const {
	float scale = 1.0f / LengthFast();
	return Vector4(x / scale, y / scale, z / scale, w / scale);
}

void Vector4::Normalize() {
	float scale = 1.0f / Length();
	x /= scale;
	y /= scale;
	z /= scale;
	w /= scale;
}

void Vector4::NormalizeFast() {
	float scale = 1.0f / LengthFast();
	x /= scale;
	y /= scale;
	z /= scale;
	w /= scale;
}

float Vector4::Dot(const Vector4 & other) const {
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

Vector3 Vector4::Xyz() const {
	return Vector3(x, y, z);
}

#pragma endregion

#pragma region Operators

Vector4 Vector4::operator+(const Vector4& other) const {
	return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4 Vector4::operator-(const Vector4& other) const {
	return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector4 Vector4::operator*(const Vector4& other) const {
	return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
}

Vector4 Vector4::operator/(const Vector4& other) const {
	return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
}

Vector4 Vector4::operator+=(const Vector4& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

Vector4 Vector4::operator-=(const Vector4& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}

Vector4 Vector4::operator*=(const Vector4& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	w *= other.w;
	return *this;
}

Vector4 Vector4::operator/=(const Vector4& other) {
	x /= other.x;
	y /= other.y;
	z /= other.z;
	w /= other.w;
	return *this;
}

Vector4 Vector4::operator+(const float other) const {
	return Vector4(x + other, y + other, z + other, w + other);
}

Vector4 Vector4::operator-(const float other) const {
	return Vector4(x - other, y - other, z - other, w - other);
}

Vector4 Vector4::operator*(const float other) const {
	return Vector4(x * other, y * other, z * other, w * other);
}

Vector4 Vector4::operator/(const float other) const {
	return Vector4(x / other, y / other, z / other, w / other);
}

Vector4 Vector4::operator+=(const float other) {
	x += other;
	y += other;
	z += other;
	w += other;
	return *this;
}

Vector4 Vector4::operator-=(const float other) {
	x -= other;
	y -= other;
	z -= other;
	w -= other;
	return *this;
}

Vector4 Vector4::operator*=(const float other) {
	x *= other;
	y *= other;
	z *= other;
	w *= other;
	return *this;
}

Vector4 Vector4::operator/=(const float other) {
	x /= other;
	y /= other;
	z /= other;
	w /= other;
	return *this;
}

Vector4 Vector4::operator-() const {
	return Vector4(-x, -y, -z, -w);
}

bool Vector4::operator==(const Vector4 & other) const {
	return Equals(other);
}

bool Vector4::operator!=(const Vector4 & other) const {
	return !Equals(other);
}

bool Vector4::Equals(const Vector4 & other) const {
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

#pragma endregion


std::ostream& IwMath::operator<<(std::ostream& ostream, const Vector4& vector) {
	return ostream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
}

Vector4 IwMath::operator+(const float right, const Vector4& left) {
	return left + right;
}

Vector4 IwMath::operator-(const float right, const Vector4& left) {
	return left - right;
}

Vector4 IwMath::operator*(const float right, const Vector4& left) {
	return left + right;
}

Vector4 IwMath::operator/(const float right, const Vector4& left) {
	return left + right;
}