#include "IwEngine\Math\Matrix2x2.h"

using namespace Math;

#pragma region Constants

const Matrix2x2 Matrix2x2::Zero = Matrix2x2(Vector2::Zero, Vector2::Zero);
const Matrix2x2 Matrix2x2::Identity = Matrix2x2(Vector2::UnitX, Vector2::UnitY);

#pragma endregion

#pragma region Constructors

Matrix2x2::Matrix2x2(float m00, float m01, float m10, float m11) : row0(Vector2(m00, m01)), row1(Vector2(m10, m11)) {}

Matrix2x2::Matrix2x2(Vector2 row0, Vector2 row1) : row0(row0), row1(row1) {}

#pragma endregion

#pragma region MathFunctions

float Matrix2x2::Determinant() const {
	return row0.x * row1.y - row0.y * row1.x;
}

float Matrix2x2::Trace() const {
	return row0.x + row1.y;
}

void Matrix2x2::Transpose() {
	Matrix2x2 tmp = *this;
	row0.y = tmp.row1.x;
	row1.x = tmp.row0.y;
}

Matrix2x2 Matrix2x2::Transposed() const {
	return Matrix2x2(
		row0.x, row1.x,
		row0.y, row1.y
	);
}

void Matrix2x2::Invert() {
	float det = Determinant();
	if (det == 0) {
		throw "Matrix cannot be inverted because it is singular.";
	}

	float invDet = 1.0f / det;

	Matrix2x2 tmp = *this;
	row0.x = tmp.row1.y * invDet;
	row0.y = -tmp.row0.y * invDet;
	row1.x = -tmp.row1.x * invDet;
	row1.y = tmp.row0.x * invDet;
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
	if (row == 0) {
		if (col == 0) return row0.x;
		if (col == 1) return row0.y;
	}

	if (row == 1) {
		if (col == 0) return row1.x;
		if (col == 1) return row1.y;
	}

	throw std::out_of_range("Row/Col is outside the bounds of this maxtrix.");
}

float& Matrix2x2::m00() {
	return row0.x;
}

float& Matrix2x2::m01() {
	return row0.y;
}

float& Matrix2x2::m10() {
	return row1.x;
}

float& Matrix2x2::m11() {
	return row1.y;
}

#pragma endregion

#pragma region Operators

Matrix2x2 Matrix2x2::operator+(const Matrix2x2 & other) const {
	return Matrix2x2(
		row0 + other.row0,
		row1 + other.row1
	);
}

Matrix2x2 Matrix2x2::operator-(const Matrix2x2 & other) const {
	return Matrix2x2(
		row0 - other.row0,
		row1 - other.row1
	);
}

Matrix2x2 Matrix2x2::operator*(const Matrix2x2 & other) const {
	return Matrix2x2(
		row0.x * other.row0.x + row0.y * other.row1.x,
		row0.x * other.row0.y + row0.y * other.row1.y,
		row1.x * other.row0.x + row1.y * other.row1.x,
		row1.x * other.row0.y + row1.y * other.row1.y
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
		row0 + other, 
		row1 + other
	);
}

Matrix2x2 Matrix2x2::operator-(const float other) const {
	return Matrix2x2(
		row0 - other,
		row1 - other
	);
}

Matrix2x2 Matrix2x2::operator*(const float other) const {
	return Matrix2x2(
		row0 * other,
		row1 * other
	);
}

Matrix2x2 Matrix2x2::operator/(const float other) const {
	return Matrix2x2(
		row0 / other,
		row1 / other
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
	return Matrix2x2(-row0, -row1);
}

bool Matrix2x2::operator==(const Matrix2x2 & other) const {
	return Equals(other);
}

bool Matrix2x2::operator!=(const Matrix2x2 & other) const {
	return !Equals(other);
}

bool Matrix2x2::Equals(const Matrix2x2 & other) const {
	return row0 == other.row0 && row1 == other.row1;
}

#pragma endregion

#pragma region Static

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

#pragma endregion

std::ostream& Math::operator<<(std::ostream & ostream, const Matrix2x2 & a) {
	return ostream << a.row0 << std::endl << a.row1;
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