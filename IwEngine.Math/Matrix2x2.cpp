#include "Matrix2x2.h"

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
	row0.y = row1.x;
	row1.x = row0.y;
}

void Matrix2x2::Invert() {
	float det = Determinant();
	if (det == 0) {

	}

	float invDet = 1.0f / det;

	row0.x = row1.y * invDet;
	row0.y = -row0.y * invDet;
	row1.x = -row1.x * invDet;
	row1.y = row0.x * invDet;
}

float& Matrix2x2::m00() {
	float& ref = row0.x;
	return ref;
}

float& Matrix2x2::m01() {
	float& ref = row0.y;
	return ref;
}

float& Matrix2x2::m10() {
	float& ref = row1.x;
	return ref;
}

float& Matrix2x2::m11() {
	float& ref = row1.y;
	return ref;
}

#pragma endregion

#pragma region Operators


Matrix2x2 Matrix2x2::operator+(const Matrix2x2 & other) const {
	return Matrix2x2(
		row0.x + other.row0.x,
		row0.y + other.row0.y,
		row1.x + other.row1.x,
		row1.y + other.row1.y
	);
}

Matrix2x2 Matrix2x2::operator-(const Matrix2x2 & other) const {
	return Matrix2x2(
		row0.x - other.row0.x,
		row0.y - other.row0.y,
		row1.x - other.row1.x,
		row1.y - other.row1.y
	);
}

Matrix2x2 Matrix2x2::operator*(const Matrix2x2 & other) const {
	float 
		lM11 = row0.x, lM12 = row0.y,
		lM21 = row1.x, lM22 = row1.y,
		rM11 = other.row0.x, rM12 = other.row0.y,
		rM21 = other.row1.x, rM22 = other.row1.y;

	return Matrix2x2(
		lM11 * rM11 + lM12 * rM21,
		lM11 * rM12 + lM12 * rM22,
		lM21 * rM11 + lM22 * rM21,
		lM21 * rM12 + lM22 * rM22
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
		row0.x + other,
		row0.y + other,
		row1.x + other,
		row1.y + other
	);
}

Matrix2x2 Matrix2x2::operator-(const float other) const {
	return Matrix2x2(
		row0.x - other,
		row0.y - other,
		row1.x - other,
		row1.y - other
	);
}

Matrix2x2 Matrix2x2::operator*(const float other) const {
	return Matrix2x2(
		row0.x * other,
		row0.y * other,
		row1.x * other,
		row1.y * other
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
