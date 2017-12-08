#include "Matrix3x3.h"
#include "Matrix2x2.h"

using namespace Math;

#pragma region Constants

const Matrix3x3 Matrix3x3::Zero = Matrix3x3(Vector3::Zero, Vector3::Zero, Vector3::Zero);
const Matrix3x3 Matrix3x3::Identity = Matrix3x3(Vector3::UnitX, Vector3::UnitY, Vector3::UnitZ);

#pragma endregion

#pragma region Constructors

Matrix3x3::Matrix3x3(
	float m00, float m01, float m02,
	float m10, float m11, float m12,
	float m20, float m21, float m22) :
	row0(Vector3(m00, m01, m02)),
	row1(Vector3(m10, m11, m12)),
	row2(Vector3(m20, m21, m22)) {
}

Matrix3x3::Matrix3x3(Vector3 row0, Vector3 row1, Vector3 row2) : row0(row0), row1(row1), row2(row2) {}

#pragma endregion

#pragma region MathFunctions

float Matrix3x3::Determinant() const {
	return row0.x * (row1.y * row2.z - row1.z * row2.y)
		- row0.y * (row1.x * row2.z - row1.z * row2.x)
		+ row0.z * (row1.x * row2.y - row1.y * row2.x);
}

float Matrix3x3::Trace() const {
	return row0.x + row1.y + row2.z;
}

void Matrix3x3::Transpose() {
	Matrix3x3 tmp = *this;
	row0.x = tmp.row0.x;
	row0.y = tmp.row1.x;
	row0.z = tmp.row2.x;
	row1.x = tmp.row0.y;
	row1.y = tmp.row1.y;
	row1.z = tmp.row2.y;
	row2.x = tmp.row0.z;
	row2.y = tmp.row1.z;
	row2.z = tmp.row2.z;
}

Matrix3x3 Matrix3x3::Transposed() const {
	Matrix3x3 tmp = *this;
	tmp.Transpose();

	return tmp;
}

void Matrix3x3::Invert() {
	float aDet = Determinant();
	if (aDet == 0) {
		throw std::invalid_argument("Determinant is zero, therefore inverse matrix doesn't exist.");
	}

	Matrix3x3 tmp = Matrix3x3::Zero;

	for (short i = 0; i < 3; i++) {
		for (short j = 0; j < 3; j++) {
			short t1c = (j + 1) % 3;
			short t1r = (i + 1) % 3;
			short t2c = (j + 2) % 3;
			short t2r = (i + 2) % 3;

			float m11 = operator()(t1r, t1c);
			float m21 = operator()(t2r, t1c);
			float m12 = operator()(t1r, t2c);
			float m22 = operator()(t2r, t2c);

			t1c = t1c == 0 ? 0 : t1c - 1;
			t1r = t1r == 0 ? 0 : t1r - 1;
			if (t2c - 1 != t1c) {
				t2c = t2c == 0 ? 0 : t2c - 1;
			}

			if (t2r - 1 != t1r) {
				t2r = t2r == 0 ? 0 : t2r - 1;
			}

			Matrix2x2 m = Matrix2x2::Zero;

			m(t1r, t1c) = m11;
			m(t2r, t1c) = m21;
			m(t1r, t2c) = m12;
			m(t2r, t2c) = m22;

			float det = m.Determinant();

			tmp(i, j) = det;
		}
	}

	tmp(0, 1) *= -1;
	tmp(1, 0) *= -1;
	tmp(1, 2) *= -1;
	tmp(2, 1) *= -1;

	tmp.Transpose();
	tmp /= aDet;

	*this = tmp;
}

Matrix3x3 Matrix3x3::Inverted() const {
	Matrix3x3 tmp = *this;
	tmp.Invert();

	return tmp;
}

void Matrix3x3::Normalize() {
	float det = Determinant();
	*this /= det;
}

Matrix3x3 Matrix3x3::Normalized() const {
	float det = Determinant();
	return *this / det;
}

void Matrix3x3::ClearRotation() {
	row0 = Vector3(row0.Length(), 0, 0);
	row1 = Vector3(0, row1.Length(), 0);
	row2 = Vector3(0, 0, row2.Length());
}

Matrix3x3 Matrix3x3::ClearedRotation() const {
	Matrix3x3 tmp = *this;
	tmp.ClearRotation();

	return tmp;
}

Vector3 Matrix3x3::ExtractScale() const {
	return Vector3(row0.Length(), row1.Length(), row2.Length());
}

Quaternion Matrix3x3::ExtractRotation() const {
	Vector3 r0 = row0.Normalized();
	Vector3 r1 = row1.Normalized();
	Vector3 r2 = row2.Normalized();

	Quaternion q = Quaternion::Identity;

	float trace = 0.25f * (r0.y + r1.y + r2.z + 1.0f);

	if (trace > 0) {
		float sq = sqrtf(trace);

		q.w = sq;
		sq = 1.0f / 4.0f * sq;
		q.x = (r1.z - r2.y) * sq;
		q.y = (r2.x - r0.z) * sq;
		q.z = (r0.y - r1.x) * sq;
	} else if (r0.x > r1.y && r0.x > r2.z) {
		float sq = 2.0f * sqrtf(1.0f + r0.x - r1.y - r2.z);

		q.x = 0.25f * sq;
		sq = 1.0f / sq;
		q.w = (r2.y - r1.z) * sq;
		q.y = (r1.x - r0.y) * sq;
		q.z = (r2.x - r0.z) * sq;
	} else if (r1.y > r2.z) {
		float sq = 2.0f * sqrtf(1.0f + r1.y - r0.x - r2.z);

		q.y = 0.25f * sq;
		sq = 1.0f / sq;
		q.w = (r2.x - r0.z) * sq;
		q.x = (r1.x - r0.y) * sq;
		q.z = (r2.y - r1.z) * sq;
	} else {
		float sq = 2.0f * sqrtf(1.0f + r2.z - r0.x - r1.y);

		q.z = 0.25f * sq;
		sq = 1.0f / sq;
		q.w = (r1.x - r0.y) * sq;
		q.x = (r2.x - r0.z) * sq;
		q.y = (r2.y - r1.z) * sq;
	}

	return q.Normalized();
}

float& Matrix3x3::operator()(int row, int col) {
	if (row == 0) {
		if (col == 0) return row0.x;
		if (col == 1) return row0.y;
		if (col == 2) return row0.z;
	}

	if (row == 1) {
		if (col == 0) return row1.x;
		if (col == 1) return row1.y;
		if (col == 2) return row1.z;
	}

	if (row == 2) {
		if (col == 0) return row2.x;
		if (col == 1) return row2.y;
		if (col == 2) return row2.z;
	}

	throw std::out_of_range("Row/Col is outside the bounds of this maxtrix.");
}

float& Matrix3x3::m00() {
	return row0.x;
}

float& Matrix3x3::m01() {
	return row0.y;
}

float& Matrix3x3::m02() {
	return row0.z;
}

float& Matrix3x3::m10() {
	return row1.x;
}

float& Matrix3x3::m11() {
	return row1.y;
}

float& Matrix3x3::m12() {
	return row1.z;
}

float& Matrix3x3::m20() {
	return row2.x;
}

float& Matrix3x3::m21() {
	return row2.y;
}

float& Matrix3x3::m22() {
	return row2.z;
}

#pragma endregion

#pragma region Operators

Matrix3x3 Matrix3x3::operator+(const Matrix3x3 & other) const {
	return Matrix3x3(
		row0 + other.row0,
		row1 + other.row1,
		row2 + other.row2
	);
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3 & other) const {
	return Matrix3x3(
		row0 - other.row0,
		row1 - other.row1,
		row2 - other.row2
	);
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3 & other) const {
	return Matrix3x3(
		(row0.x * other.row0.x) + (row0.y * other.row1.x) + (row0.z * other.row2.x),
		(row0.x * other.row0.y) + (row0.y * other.row1.y) + (row0.z * other.row2.y),
		(row0.x * other.row0.z) + (row0.y * other.row1.z) + (row0.z * other.row2.z),
		(row1.x * other.row0.x) + (row1.y * other.row1.x) + (row1.z * other.row2.x),
		(row1.x * other.row0.y) + (row1.y * other.row1.y) + (row1.z * other.row2.y),
		(row1.x * other.row0.z) + (row1.y * other.row1.z) + (row1.z * other.row2.z),
		(row2.x * other.row0.x) + (row2.y * other.row1.x) + (row2.z * other.row2.x),
		(row2.x * other.row0.y) + (row2.y * other.row1.y) + (row2.z * other.row2.y),
		(row2.x * other.row0.z) + (row2.y * other.row1.z) + (row2.z * other.row2.z)
	);
}

Matrix3x3 Matrix3x3::operator+=(const Matrix3x3 & other) {
	return *this = other + (*this);
}

Matrix3x3 Matrix3x3::operator-=(const Matrix3x3 & other) {
	return *this = other - (*this);
}

Matrix3x3 Matrix3x3::operator*=(const Matrix3x3 & other) {
	return *this = other * (*this);
}

Matrix3x3 Matrix3x3::operator+(const float other) const {
	return Matrix3x3(
		row0 + other,
		row1 + other,
		row2 + other
	);
}

Matrix3x3 Matrix3x3::operator-(const float other) const {
	return Matrix3x3(
		row0 - other,
		row1 - other,
		row2 - other
	);
}

Matrix3x3 Matrix3x3::operator*(const float other) const {
	return Matrix3x3(
		row0 * other,
		row1 * other,
		row2 * other
	);
}


Matrix3x3 Matrix3x3::operator/(const float other) const {
	return Matrix3x3(
		row0 / other,
		row1 / other,
		row2 / other
	);
}

Matrix3x3 Matrix3x3::operator+=(const float other) {
	return *this = other * (*this);
}

Matrix3x3 Matrix3x3::operator-=(const float other) {
	return *this = other * (*this);
}

Matrix3x3 Matrix3x3::operator*=(const float other) {
	return *this = other * (*this);
}

Matrix3x3 Matrix3x3::operator/=(const float other) {
	return *this = other / (*this);
}

Matrix3x3 Matrix3x3::operator-() const {
	return Matrix3x3(-row0, -row1, -row2);
}

bool Matrix3x3::operator==(const Matrix3x3& other) const {
	return Equals(other);
}

bool Matrix3x3::operator!=(const Matrix3x3& other) const {
	return !Equals(other);
}

bool Matrix3x3::Equals(const Matrix3x3& other) const {
	return row0 == other.row0 && row1 == other.row1 && row2 == other.row2;
}

#pragma endregion

#pragma region Static

Matrix3x3 Matrix3x3::CreateFromAxisAngle(float x, float y, float z, float angle) {
	return CreateFromAxisAngle(Vector3(x, y, z), angle);
}

Matrix3x3 Matrix3x3::CreateFromAxisAngle(const Vector3& axis, float angle) {
	Vector3 a = axis.Normalized();
	float axisX = a.x;
	float axisY = a.y;
	float axisZ = a.z;

	float cos = cosf(-angle);
	float sin = sinf(-angle);
	float t = 1.0f - cos;

	float tXX = t * axisX * axisX;
	float tXY = t * axisX * axisY;
	float tXZ = t * axisX * axisZ;
	float tYY = t * axisY * axisY;
	float tYZ = t * axisY * axisZ;
	float tZZ = t * axisZ * axisZ;

	float sinX = sin * axisX;
	float sinY = sin * axisY;
	float sinZ = sin * axisZ;

	return Matrix3x3(
		tXX + cos, tXY - sinZ, tXZ + sinY,
		tXY + sinZ, tYY + cos, tYZ - sinX,
		tXZ - sinY, tYZ + sinX, tZZ + cos
	);
}

Matrix3x3 Matrix3x3::CreateFromQuaternion(const Quaternion& quaternion) {
	Vector4 aa = quaternion.ToAxisAngle();
	return CreateFromAxisAngle(aa.x, aa.y, aa.z, aa.w);
}

Matrix3x3 Matrix3x3::CreateRoatationX(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	Matrix3x3 out = Matrix3x3::Identity;
	out.row1.y = cos;
	out.row1.z = sin;
	out.row2.y = -sin;
	out.row2.z = cos;

	return out;
}

Matrix3x3 Matrix3x3::CreateRoatationY(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	Matrix3x3 out = Matrix3x3::Identity;
	out.row0.x = cos;
	out.row0.z = -sin;
	out.row2.x = sin;
	out.row2.z = cos;

	return out;
}

Matrix3x3 Matrix3x3::CreateRoatationZ(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	Matrix3x3 out = Matrix3x3::Identity;
	out.row0.x = cos;
	out.row0.y = sin;
	out.row1.x = -sin;
	out.row1.y = cos;

	return out;
}

Matrix3x3 Matrix3x3::CreateRoatation(const Vector3& angles) {
	return Matrix3x3::CreateRoatation(angles.x, angles.y, angles.z);
}

Matrix3x3 Matrix3x3::CreateRoatation(float x, float y, float z) {
	return Matrix3x3::CreateRoatationX(x).CreateRoatationY(y).CreateRoatationZ(z);
}

Matrix3x3 Matrix3x3::CreateScale(float scale) {
	return CreateScale(scale, scale, scale);
}

Matrix3x3 Matrix3x3::CreateScale(const Vector3& scale) {
	return CreateScale(scale.x, scale.y, scale.z);
}

Matrix3x3 Matrix3x3::CreateScale(float x, float y, float z) {
	return Matrix3x3(
		x, 0, 0,
		0, y, 0,
		0, 0, z
	);
}

#pragma endregion

std::ostream& Math::operator<<(std::ostream & ostream, const Matrix3x3 & a) {
	return ostream << a.row0 << std::endl << a.row1 << std::endl << a.row2;
}

Matrix3x3 Math::operator+(const float left, const Matrix3x3 & right) {
	return right + left;
}

Matrix3x3 Math::operator-(const float left, const Matrix3x3 & right) {
	return right - left;
}

Matrix3x3 Math::operator*(const float left, const Matrix3x3 & right) {
	return right * left;
}

Matrix3x3 Math::operator/(const float left, const Matrix3x3 & right) {
	return right / left;
}