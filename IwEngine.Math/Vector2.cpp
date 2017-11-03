#include "Vector2.h"
#include "MathHelper.h"
#include <cmath>

#pragma region Constants

const Vector2 Vector2::Zero = Vector2(0, 0);
const Vector2 Vector2::One = Vector2(1, 1);
const Vector2 Vector2::UnitX = Vector2(1, 0);
const Vector2 Vector2::UnitY = Vector2(0, 1);

#pragma endregion

#pragma region Constructors

Vector2::Vector2() {}

Vector2::Vector2(float xy) : x(xy), y(xy) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

#pragma endregion

#pragma region Misc

float Vector2::Length() {
	return sqrtf(x * x + y * y);
}

float Vector2::LengthSquared() {
	return x * x + y * y;
}

float Vector2::LengthFast() {
	return 1 / InvSqrt(x * x + y * y);
}

Vector2 Vector2::NormalRight() {
	return Vector2(x, -y);
}

Vector2 Vector2::NormalLeft() {
	return Vector2(-x, y);
}

Vector2 Vector2::Normalized() {
	float scale = 1.0f / Length();
	return Vector2(x / scale, y / scale);
}

Vector2 Vector2::NormalizedFast() {
	float scale = 1.0f / LengthFast();
	return Vector2(x / scale, y / scale);
}

void Vector2::Normalize() {
	float scale = 1.0f / Length();
	x /= scale;
	y /= scale;
}

void Vector2::NormalizeFast() {
	float scale = 1.0f / LengthFast();
	x /= scale;
	y /= scale;
}

float Vector2::Dot(const Vector2 & other) const {
	return x * other.x + y * other.y;
}

float Vector2::CrossLength(const Vector2 & other) const {
	return x * other.y - y * other.x;
}

std::ostream& operator<<(std::ostream& ostream, const Vector2& vector) {
	return ostream << "(" << vector.x << ", " << vector.y << ")";
}

#pragma endregion

#pragma region Operators

Vector2 Vector2::operator+(const Vector2& other) const {
	return Add(other);
}

Vector2 Vector2::operator-(const Vector2& other) const {
	return Subtact(other);
}

Vector2 Vector2::operator*(const Vector2& other) const {
	return Multiply(other);
}

Vector2 Vector2::operator/(const Vector2& other) const {
	return Divide(other);
}

Vector2 Vector2::operator+=(const Vector2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

Vector2 Vector2::operator-=(const Vector2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2 Vector2::operator*=(const Vector2& other) {
	x *= other.x;
	y *= other.y;
	return *this;
}

Vector2 Vector2::operator/=(const Vector2& other) {
	x /= other.x;
	y /= other.y;
	return *this;
}

Vector2 Vector2::Add(const Vector2& other) const {
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::Subtact(const Vector2& other) const {
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::Multiply(const Vector2& other) const {
	return Vector2(x * other.x, y * other.y);
}

Vector2 Vector2::Divide(const Vector2& other) const {
	return Vector2(x / other.x, y / other.y);
}

Vector2 Vector2::operator+(const float other) const {
	return Add(other);
}

Vector2 Vector2::operator-(const float other) const {
	return Subtact(other);
}

Vector2 Vector2::operator*(const float other) const {
	return Multiply(other);
}

Vector2 Vector2::operator/(const float other) const {
	return Divide(other);
}

Vector2 Vector2::operator+=(const float other) {
	x += other;
	y += other;
	return *this;
}

Vector2 Vector2::operator-=(const float other) {
	x -= other;
	y -= other;
	return *this;
}

Vector2 Vector2::operator*=(const float other) {
	x *= other;
	y *= other;
	return *this;
}

Vector2 Vector2::operator/=(const float other) {
	x /= other;
	y /= other;
	return *this;
}

Vector2 Vector2::Add(const float other) const {
	return Vector2(x + other, y + other);
}

Vector2 Vector2::Subtact(const float other) const {
	return Vector2(x - other, y - other);
}

Vector2 Vector2::Multiply(const float other) const {
	return Vector2(x * other, y * other);
}

Vector2 Vector2::Divide(const float other) const {
	return Vector2(x / other, y / other);
}

bool Vector2::operator==(const Vector2 & other) const {
	return Equals(other);
}

bool Vector2::operator!=(const Vector2 & other) const {
	return !Equals(other);
}

bool Vector2::Equals(const Vector2 & other) const {
	return x == other.x && y == other.y;
}

#pragma endregion