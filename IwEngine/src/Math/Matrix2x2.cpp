#include "IwEngine\Math\Matrix2x2.h"

using namespace Math;

const Matrix2x2 Matrix2x2::Identity = Matrix2x2(1.0f);

Matrix2x2::Matrix2x2() {
	memset(elements, 0, 2 * 2 * sizeof(float));
}

Matrix2x2::Matrix2x2(float diagonal) {
	memset(elements, 0, 2 * 2 * sizeof(float));
	elements[0 + 0 * 2] = diagonal;
	elements[1 + 1 * 2] = diagonal;
}

Matrix2x2::Matrix2x2(float* elements) {
	memcpy(this->elements, elements, 2 * 2 * sizeof(float));
}

Matrix2x2::Matrix2x2(Vector2& row0, Vector2& row1) {
	rows[0] = row0;
	rows[1] = row1;
}

Matrix2x2::Matrix2x2(float m00, float m01, float m10, float m11) {
	elements[0] = m00;
	elements[1] = m01;
	elements[2] = m10;
	elements[3] = m11;
}

float Matrix2x2::Determinant() const {
	return rows[0].x * rows[1].y - rows[0].y * rows[1].x;
}

float Matrix2x2::Trace() const {
	return rows[0].x + rows[1].y;
}

void Matrix2x2::Transpose() {
	Matrix2x2 tmp = *this;
	rows[0].y = tmp.rows[1].x;
	rows[1].x = tmp.rows[0].y;
}

Matrix2x2 Matrix2x2::Transposed() const {
	return Matrix2x2(
		rows[0].x, rows[1].x,
		rows[0].y, rows[1].y
	);
}

void Matrix2x2::Invert() {
	float det = Determinant();
	if (det == 0) {
		throw "Matrix cannot be inverted because it is singular.";
	}

	float invDet = 1.0f / det;

	Matrix2x2 tmp = *this;
	rows[0].x = tmp.rows[1].y * invDet;
	rows[0].y = -tmp.rows[0].y * invDet;
	rows[1].x = -tmp.rows[1].x * invDet;
	rows[1].y = tmp.rows[0].x * invDet;
}

Matrix2x2 Matrix2x2::Inverted() const {
	Matrix2x2 m = *this;
	m.Invert();

	return m;
}

void Matrix2x2::Normalize() {
	float det = Determinant();
	*this /= det;
}

Matrix2x2 Matrix2x2::Normalized() const {
	float det = Determinant();
	return *this / det;
}

float& Matrix2x2::operator()(int row, int col) {
	if (row > 2 || col > 2 || 0 > row || 0 > col) {
		throw std::out_of_range("Row/Col is outside the bounds of this maxtrix.");
	}

	return elements[col + row * 2];
}

Matrix2x2 Matrix2x2::operator+(const Matrix2x2 & other) const {
	return Matrix2x2(
		rows[0] + other.rows[0],
		rows[1] + other.rows[1]
	);
}

Matrix2x2 Matrix2x2::operator-(const Matrix2x2 & other) const {
	return Matrix2x2(
		rows[0] - other.rows[0],
		rows[1] - other.rows[1]
	);
}

Matrix2x2 Matrix2x2::operator*(const Matrix2x2 & other) const {
	return Matrix2x2(
		rows[0].x * other.rows[0].x + rows[0].y * other.rows[1].x,
		rows[0].x * other.rows[0].y + rows[0].y * other.rows[1].y,
		rows[1].x * other.rows[0].x + rows[1].y * other.rows[1].x,
		rows[1].x * other.rows[0].y + rows[1].y * other.rows[1].y
	);
}

Matrix2x2 Matrix2x2::operator+=(const Matrix2x2 & other) {
	return *this = other + (*this);
}

Matrix2x2 Matrix2x2::operator-=(const Matrix2x2 & other) {
	return *this = other - (*this);
}

Matrix2x2 Matrix2x2::operator*=(const Matrix2x2 & other) {
	return *this = other * (*this);
}

Matrix2x2 Matrix2x2::operator+(const float other) const {
	return Matrix2x2(
		rows[0] + other, 
		rows[1] + other
	);
}

Matrix2x2 Matrix2x2::operator-(const float other) const {
	return Matrix2x2(
		rows[0] - other,
		rows[1] - other
	);
}

Matrix2x2 Matrix2x2::operator*(const float other) const {
	return Matrix2x2(
		rows[0] * other,
		rows[1] * other
	);
}

Matrix2x2 Matrix2x2::operator/(const float other) const {
	return Matrix2x2(
		rows[0] / other,
		rows[1] / other
	);
}

Matrix2x2 Matrix2x2::operator+=(const float other) {
	return *this = other + (*this);
}

Matrix2x2 Matrix2x2::operator-=(const float other) {
	return *this = other - (*this);
}

Matrix2x2 Matrix2x2::operator*=(const float other) {
	return *this = other * (*this);
}

Matrix2x2 Matrix2x2::operator/=(const float other) {
	return *this = other / (*this);
}

Matrix2x2 Matrix2x2::operator-() const {
	return Matrix2x2(-rows[0], -rows[1]);
}

bool Matrix2x2::operator==(const Matrix2x2 & other) const {
	return Equals(other);
}

bool Matrix2x2::operator!=(const Matrix2x2 & other) const {
	return !Equals(other);
}

bool Matrix2x2::Equals(const Matrix2x2 & other) const {
	return rows[0] == other.rows[0] && rows[1] == other.rows[1];
}

Matrix2x2 Matrix2x2::CreateRoatation(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	return Matrix2x2(
		cos, sin, 
	   -sin, cos
	);
}

Matrix2x2 Matrix2x2::CreateScale(float scale) {
	return CreateScale(scale, scale);
}

Matrix2x2 Matrix2x2::CreateScale(const Vector2& scale) {
	return CreateScale(scale.x, scale.y);
}

Matrix2x2 Matrix2x2::CreateScale(float x, float y) {
	return Matrix2x2(
		x, 0,
		0, y
	);
}

std::ostream& Math::operator<<(std::ostream & ostream, const Matrix2x2 & a) {
	return ostream << a.rows[0] << std::endl << a.rows[1];
}

Matrix2x2 Math::operator+(const float left, const Matrix2x2 & right) {
	return right + left;
}

Matrix2x2 Math::operator-(const float left, const Matrix2x2 & right) {
	return right - left;
}

Matrix2x2 Math::operator*(const float left, const Matrix2x2 & right) {
	return right * left;
}

Matrix2x2 Math::operator/(const float left, const Matrix2x2 & right) {
	return right / left;
}