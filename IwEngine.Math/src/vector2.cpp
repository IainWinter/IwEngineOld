#include "IwEngine\Math\vector2.h"
#include <exception>

using namespace math;

const vector2 vector2::zero = vector2(0, 0);
const vector2 vector2::one = vector2(1, 1);
const vector2 vector2::unitX = vector2(1, 0);
const vector2 vector2::unitY = vector2(0, 1);

vector2::vector2()
	: x(0), y(0) {}

vector2::vector2(float xy)
	: x(xy), y(xy) {}

vector2::vector2(float x, float y)
	: x(x), y(y) {}

float vector2::length() const {
	return sqrtf(x * x + y * y);
}

float vector2::lengthSquared() const {
	return x * x + y * y;
}

float vector2::lengthFast() const {
	return 1 / invSqrt(x * x + y * y);
}

vector2 vector2::normalRight() const {
	return vector2(x, -y);
}

vector2 vector2::normalLeft() const {
	return vector2(-x, y);
}

vector2 vector2::normalized() const {
	float scale = length();
	return vector2(x / scale, y / scale);
}

vector2 vector2::normalizedFast() const {
	float scale = lengthFast();
	return vector2(x / scale, y / scale);
}

void vector2::normalize() {
	float scale = length();
	x /= scale;
	y /= scale;
}

void vector2::normalizeFast() {
	float scale = lengthFast();
	x /= scale;
	y /= scale;
}

float vector2::dot(const vector2 & other) const {
	return x * other.x + y * other.y;
}

float vector2::crossLength(const vector2 & other) const {
	return x * other.y - y * other.x;
}

float& math::vector2::operator[](std::size_t index) {
	if	   (index == 0) return x;
	else if(index == 1) return y;
	throw std::out_of_range("Index out of bounds");
}

vector2 vector2::operator+(const vector2& other) const {
	return vector2(x + other.x, y + other.y);
}

vector2 vector2::operator-(const vector2& other) const {
	return vector2(x - other.x, y - other.y);
}

vector2 vector2::operator*(const vector2& other) const {
	return vector2(x * other.x, y * other.y);
}

vector2 vector2::operator/(const vector2& other) const {
	return vector2(x / other.x, y / other.y);
}

vector2 vector2::operator+=(const vector2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

vector2 vector2::operator-=(const vector2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

vector2 vector2::operator*=(const vector2& other) {
	x *= other.x;
	y *= other.y;
	return *this;
}

vector2 vector2::operator/=(const vector2& other) {
	x /= other.x;
	y /= other.y;
	return *this;
}

vector2 vector2::operator+(const float& other) const {
	return vector2(x + other, y + other);
}

vector2 vector2::operator-(const float& other) const {
	return vector2(x - other, y - other);
}

vector2 vector2::operator*(const float& other) const {
	return vector2(x * other, y * other);
}

vector2 vector2::operator/(const float& other) const {
	return vector2(x / other, y / other);
}

vector2 vector2::operator+=(const float& other) {
	x += other;
	y += other;
	return *this;
}

vector2 vector2::operator-=(const float& other) {
	x -= other;
	y -= other;
	return *this;
}

vector2 vector2::operator*=(const float& other) {
	x *= other;
	y *= other;
	return *this;
}

vector2 vector2::operator/=(const float& other) {
	x /= other;
	y /= other;
	return *this;
}

vector2 vector2::operator-() const {
	return vector2(-x, -y);
}

bool vector2::operator==(const vector2 & other) const {
	return equals(other);
}

bool vector2::operator!=(const vector2 & other) const {
	return !equals(other);
}

bool vector2::equals(const vector2 & other) const {
	return x == other.x && y == other.y;
}

std::ostream& math::operator<<(std::ostream& ostream, const vector2& vector) {
	return ostream << "(" << vector.x << ", " << vector.y << ")";
}

vector2 math::operator+(const float& right, const vector2& left) {
	return left + right;
}

vector2 math::operator-(const float& right, const vector2& left) {
	return left - right;
}

vector2 math::operator*(const float& right, const vector2& left) {
	return left + right;
}

vector2 math::operator/(const float& right, const vector2& left) {
	return left + right;
}