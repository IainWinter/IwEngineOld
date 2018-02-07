#include "IwMath\matrix3.h"
#include "IwMath\matrix2.h"

using namespace iwmath;

const matrix3 matrix3::identity = matrix3(1.0f);

matrix3::matrix3() {
	memset(elements, 0, 3 * 3 * sizeof(float));
}

matrix3::matrix3(float diagonal) {
	memset(elements, 0, 3 * 3 * sizeof(float));
	elements[0 + 0 * 3] = diagonal;
	elements[1 + 1 * 3] = diagonal;
	elements[2 + 2 * 3] = diagonal;
}

matrix3::matrix3(float* elements) {
	memcpy(this->elements, elements, 3 * 3 * sizeof(float));
}

matrix3::matrix3(vector3 row0, vector3 row1, vector3 row2) {
	rows[0] = row0;
	rows[1] = row1;
	rows[2] = row2;
}

matrix3::matrix3(
	float m00, float m01, float m02,
	float m10, float m11, float m12,
	float m20, float m21, float m22) {
	elements[0] = m00; elements[1] = m01; elements[2] = m02;
	elements[3] = m10; elements[4] = m11; elements[5] = m12;
	elements[6] = m20; elements[7] = m21; elements[8] = m22;
}

float matrix3::determinant() const {
	return
		rows[0].x * (rows[1].y * rows[2].z - rows[1].z * rows[2].y)
		- rows[0].y * (rows[1].x * rows[2].z - rows[1].z * rows[2].x)
		+ rows[0].z * (rows[1].x * rows[2].y - rows[1].y * rows[2].x);
}

float matrix3::trace() const {
	return rows[0].x + rows[1].y + rows[2].z;
}

void matrix3::transpose() {
	matrix3 tmp = *this;
	rows[0].x = tmp.rows[0].x;
	rows[0].y = tmp.rows[1].x;
	rows[0].z = tmp.rows[2].x;
	rows[1].x = tmp.rows[0].y;
	rows[1].y = tmp.rows[1].y;
	rows[1].z = tmp.rows[2].y;
	rows[2].x = tmp.rows[0].z;
	rows[2].y = tmp.rows[1].z;
	rows[2].z = tmp.rows[2].z;
}

matrix3 matrix3::transposed() const {
	matrix3 tmp = *this;
	tmp.transpose();

	return tmp;
}

void matrix3::invert() {
	float aDet = determinant();
	if (aDet == 0) {
		throw std::invalid_argument("Determinant is zero, therefore inverse matrix doesn't exist.");
	}

	matrix3 tmp = matrix3();

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

			matrix2 m = matrix2();

			m(t1r, t1c) = m11;
			m(t2r, t1c) = m21;
			m(t1r, t2c) = m12;
			m(t2r, t2c) = m22;

			float det = m.determinant();

			tmp(i, j) = det;
		}
	}

	tmp(0, 1) *= -1;
	tmp(1, 0) *= -1;
	tmp(1, 2) *= -1;
	tmp(2, 1) *= -1;

	tmp.transpose();
	tmp /= aDet;

	*this = tmp;
}

matrix3 matrix3::inverted() const {
	matrix3 tmp = *this;
	tmp.invert();

	return tmp;
}

void matrix3::normalize() {
	float det = determinant();
	*this /= det;
}

matrix3 matrix3::normalized() const {
	float det = determinant();
	return *this / det;
}

void matrix3::clearRotation() {
	rows[0] = vector3(rows[0].length(), 0, 0);
	rows[1] = vector3(0, rows[1].length(), 0);
	rows[2] = vector3(0, 0, rows[2].length());
}

matrix3 matrix3::clearedRotation() const {
	matrix3 tmp = *this;
	tmp.clearRotation();

	return tmp;
}

vector3 matrix3::extractScale() const {
	return vector3(rows[0].length(), rows[1].length(), rows[2].length());
}

quaternion matrix3::extractRotation() const {
	vector3 r0 = rows[0].normalized();
	vector3 r1 = rows[1].normalized();
	vector3 r2 = rows[2].normalized();

	quaternion q = quaternion::identity;

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

	return q.normalized();
}

float& matrix3::operator()(int row, int col) {
	if (row > 3 || col > 3 || 0 > row || 0 > col) {
		throw std::out_of_range("Row/Col is outside the bounds of this maxtrix.");
	}

	return elements[col + row * 3];
}

matrix3 matrix3::operator+(const matrix3& other) const {
	return matrix3(
		rows[0] + other.rows[0],
		rows[1] + other.rows[1],
		rows[2] + other.rows[2]
	);
}

matrix3 matrix3::operator-(const matrix3& other) const {
	return matrix3(
		rows[0] - other.rows[0],
		rows[1] - other.rows[1],
		rows[2] - other.rows[2]
	);
}

matrix3 matrix3::operator*(const matrix3& other) const {
	return matrix3(
		(rows[0].x * other.rows[0].x) + (rows[0].y * other.rows[1].x) + (rows[0].z * other.rows[2].x),
		(rows[0].x * other.rows[0].y) + (rows[0].y * other.rows[1].y) + (rows[0].z * other.rows[2].y),
		(rows[0].x * other.rows[0].z) + (rows[0].y * other.rows[1].z) + (rows[0].z * other.rows[2].z),
		(rows[1].x * other.rows[0].x) + (rows[1].y * other.rows[1].x) + (rows[1].z * other.rows[2].x),
		(rows[1].x * other.rows[0].y) + (rows[1].y * other.rows[1].y) + (rows[1].z * other.rows[2].y),
		(rows[1].x * other.rows[0].z) + (rows[1].y * other.rows[1].z) + (rows[1].z * other.rows[2].z),
		(rows[2].x * other.rows[0].x) + (rows[2].y * other.rows[1].x) + (rows[2].z * other.rows[2].x),
		(rows[2].x * other.rows[0].y) + (rows[2].y * other.rows[1].y) + (rows[2].z * other.rows[2].y),
		(rows[2].x * other.rows[0].z) + (rows[2].y * other.rows[1].z) + (rows[2].z * other.rows[2].z)
	);
}

matrix3 matrix3::operator+=(const matrix3& other) {
	return *this = other + (*this);
}

matrix3 matrix3::operator-=(const matrix3& other) {
	return *this = other - (*this);
}

matrix3 matrix3::operator*=(const matrix3& other) {
	return *this = other * (*this);
}

matrix3 matrix3::operator+(const float& other) const {
	return matrix3(
		rows[0] + other,
		rows[1] + other,
		rows[2] + other
	);
}

matrix3 matrix3::operator-(const float& other) const {
	return matrix3(
		rows[0] - other,
		rows[1] - other,
		rows[2] - other
	);
}

matrix3 matrix3::operator*(const float& other) const {
	return matrix3(
		rows[0] * other,
		rows[1] * other,
		rows[2] * other
	);
}


matrix3 matrix3::operator/(const float& other) const {
	return matrix3(
		rows[0] / other,
		rows[1] / other,
		rows[2] / other
	);
}

matrix3 matrix3::operator+=(const float& other) {
	return *this = other * (*this);
}

matrix3 matrix3::operator-=(const float& other) {
	return *this = other * (*this);
}

matrix3 matrix3::operator*=(const float& other) {
	return *this = other * (*this);
}

matrix3 matrix3::operator/=(const float& other) {
	return *this = other / (*this);
}

matrix3 matrix3::operator-() const {
	return matrix3(-rows[0], -rows[1], -rows[2]);
}

bool matrix3::operator==(const matrix3& other) const {
	return equals(other);
}

bool matrix3::operator!=(const matrix3& other) const {
	return !equals(other);
}

bool matrix3::equals(const matrix3& other) const {
	return rows[0] == other.rows[0] && rows[1] == other.rows[1] && rows[2] == other.rows[2];
}

matrix3 matrix3::createFromAxisAngle(float x, float y, float z, float angle) {
	return createFromAxisAngle(vector3(x, y, z), angle);
}

matrix3 matrix3::createFromAxisAngle(const vector3& axis, float angle) {
	vector3 a = axis.normalized();
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

	return matrix3(
		tXX + cos, tXY - sinZ, tXZ + sinY,
		tXY + sinZ, tYY + cos, tYZ - sinX,
		tXZ - sinY, tYZ + sinX, tZZ + cos
	);
}

matrix3 matrix3::createFromQuaternion(const quaternion& quaternion) {
	vector4 aa = quaternion.toAxisAngle();
	return createFromAxisAngle(aa.x, aa.y, aa.z, aa.w);
}

matrix3 matrix3::createRoatationX(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	matrix3 out = matrix3::identity;
	out.rows[1].y = cos;
	out.rows[1].z = sin;
	out.rows[2].y = -sin;
	out.rows[2].z = cos;

	return out;
}

matrix3 matrix3::createRoatationY(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	matrix3 out = matrix3::identity;
	out.rows[0].x = cos;
	out.rows[0].z = -sin;
	out.rows[2].x = sin;
	out.rows[2].z = cos;

	return out;
}

matrix3 matrix3::createRoatationZ(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	matrix3 out = matrix3::identity;
	out.rows[0].x = cos;
	out.rows[0].y = sin;
	out.rows[1].x = -sin;
	out.rows[1].y = cos;

	return out;
}

matrix3 matrix3::createRoatation(const vector3& angles) {
	return matrix3::createRoatation(angles.x, angles.y, angles.z);
}

matrix3 matrix3::createRoatation(float x, float y, float z) {
	return matrix3::createRoatationX(x).createRoatationY(y).createRoatationZ(z);
}

matrix3 matrix3::createScale(float scale) {
	return createScale(scale, scale, scale);
}

matrix3 matrix3::createScale(const vector3& scale) {
	return createScale(scale.x, scale.y, scale.z);
}

matrix3 matrix3::createScale(float x, float y, float z) {
	return matrix3(
		x, 0, 0,
		0, y, 0,
		0, 0, z
	);
}

std::ostream& iwmath::operator<<(std::ostream& stream, const matrix3& a) {
	return stream << a.rows[0] << std::endl << a.rows[1] << std::endl << a.rows[2];
}

matrix3 iwmath::operator+(const float& left, const matrix3& right) {
	return right + left;
}

matrix3 iwmath::operator-(const float& left, const matrix3& right) {
	return right - left;
}

matrix3 iwmath::operator*(const float& left, const matrix3& right) {
	return right * left;
}

matrix3 iwmath::operator/(const float& left, const matrix3& right) {
	return right / left;
}