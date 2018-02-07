#include "IwMath\matrix2.h"

using namespace iwmath;

const matrix2 matrix2::identity = matrix2(1.0f);

matrix2::matrix2() {
	memset(elements, 0, 2 * 2 * sizeof(float));
}

matrix2::matrix2(float diagonal) {
	memset(elements, 0, 2 * 2 * sizeof(float));
	elements[0 + 0 * 2] = diagonal;
	elements[1 + 1 * 2] = diagonal;
}

matrix2::matrix2(float* elements) {
	memcpy(this->elements, elements, 2 * 2 * sizeof(float));
}

matrix2::matrix2(vector2& row0, vector2& row1) {
	rows[0] = row0;
	rows[1] = row1;
}

matrix2::matrix2(float m00, float m01, float m10, float m11) {
	elements[0] = m00;
	elements[1] = m01;
	elements[2] = m10;
	elements[3] = m11;
}

float matrix2::determinant() const {
	return rows[0].x * rows[1].y - rows[0].y * rows[1].x;
}

float matrix2::trace() const {
	return rows[0].x + rows[1].y;
}

void matrix2::transpose() {
	matrix2 tmp = *this;
	rows[0].y = tmp.rows[1].x;
	rows[1].x = tmp.rows[0].y;
}

matrix2 matrix2::transposed() const {
	return matrix2(
		rows[0].x, rows[1].x,
		rows[0].y, rows[1].y
	);
}

void matrix2::invert() {
	float det = determinant();
	if (det == 0) {
		throw "Matrix cannot be inverted because it is singular.";
	}

	float invDet = 1.0f / det;

	matrix2 tmp = *this;
	rows[0].x = tmp.rows[1].y * invDet;
	rows[0].y = -tmp.rows[0].y * invDet;
	rows[1].x = -tmp.rows[1].x * invDet;
	rows[1].y = tmp.rows[0].x * invDet;
}

matrix2 matrix2::inverted() const {
	matrix2 m = *this;
	m.invert();

	return m;
}

void matrix2::normalize() {
	float det = determinant();
	*this /= det;
}

matrix2 matrix2::normalized() const {
	float det = determinant();
	return *this / det;
}

float& matrix2::operator()(int row, int col) {
	if (row > 2 || col > 2 || 0 > row || 0 > col) {
		throw std::out_of_range("Row/Col is outside the bounds of this maxtrix.");
	}

	return elements[col + row * 2];
}

matrix2 matrix2::operator+(const matrix2 & other) const {
	return matrix2(
		rows[0] + other.rows[0],
		rows[1] + other.rows[1]
	);
}

matrix2 matrix2::operator-(const matrix2 & other) const {
	return matrix2(
		rows[0] - other.rows[0],
		rows[1] - other.rows[1]
	);
}

matrix2 matrix2::operator*(const matrix2 & other) const {
	return matrix2(
		rows[0].x * other.rows[0].x + rows[0].y * other.rows[1].x,
		rows[0].x * other.rows[0].y + rows[0].y * other.rows[1].y,
		rows[1].x * other.rows[0].x + rows[1].y * other.rows[1].x,
		rows[1].x * other.rows[0].y + rows[1].y * other.rows[1].y
	);
}

matrix2 matrix2::operator+=(const matrix2 & other) {
	return *this = other + (*this);
}

matrix2 matrix2::operator-=(const matrix2 & other) {
	return *this = other - (*this);
}

matrix2 matrix2::operator*=(const matrix2 & other) {
	return *this = other * (*this);
}

matrix2 matrix2::operator+(const float& other) const {
	return matrix2(
		rows[0] + other,
		rows[1] + other
	);
}

matrix2 matrix2::operator-(const float& other) const {
	return matrix2(
		rows[0] - other,
		rows[1] - other
	);
}

matrix2 matrix2::operator*(const float& other) const {
	return matrix2(
		rows[0] * other,
		rows[1] * other
	);
}

matrix2 matrix2::operator/(const float& other) const {
	return matrix2(
		rows[0] / other,
		rows[1] / other
	);
}

matrix2 matrix2::operator+=(const float& other) {
	return *this = other + (*this);
}

matrix2 matrix2::operator-=(const float& other) {
	return *this = other - (*this);
}

matrix2 matrix2::operator*=(const float& other) {
	return *this = other * (*this);
}

matrix2 matrix2::operator/=(const float& other) {
	return *this = other / (*this);
}

matrix2 matrix2::operator-() const {
	return matrix2(-rows[0], -rows[1]);
}

bool matrix2::operator==(const matrix2 & other) const {
	return Equals(other);
}

bool matrix2::operator!=(const matrix2 & other) const {
	return !Equals(other);
}

bool matrix2::Equals(const matrix2 & other) const {
	return rows[0] == other.rows[0] && rows[1] == other.rows[1];
}

matrix2 matrix2::createRoatation(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	return matrix2(
		cos, sin,
		-sin, cos
	);
}

matrix2 matrix2::createScale(float scale) {
	return createScale(scale, scale);
}

matrix2 matrix2::createScale(const vector2& scale) {
	return createScale(scale.x, scale.y);
}

matrix2 matrix2::createScale(float x, float y) {
	return matrix2(
		x, 0,
		0, y
	);
}

std::ostream& iwmath::operator<<(std::ostream & ostream, const matrix2 & a) {
	return ostream << a.rows[0] << std::endl << a.rows[1];
}

matrix2 iwmath::operator+(const float& left, const matrix2 & right) {
	return right + left;
}

matrix2 iwmath::operator-(const float& left, const matrix2 & right) {
	return right - left;
}

matrix2 iwmath::operator*(const float& left, const matrix2 & right) {
	return right * left;
}

matrix2 iwmath::operator/(const float& left, const matrix2 & right) {
	return right / left;
}