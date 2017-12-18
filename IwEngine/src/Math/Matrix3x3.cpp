#include "IwEngine\Math\Matrix3x3.h"
#include "IwEngine\Math\Matrix2x2.h"

using namespace Math;

const Matrix3x3 Matrix3x3::Identity = Matrix3x3(1.0f);

Matrix3x3::Matrix3x3() {
	memset(elements, 0, 3 * 3 * sizeof(float));
}

Matrix3x3::Matrix3x3(float diagonal) {
	memset(elements, 0, 3 * 3 * sizeof(float));
	elements[0 + 0 * 3] = diagonal;
	elements[1 + 1 * 3] = diagonal;
	elements[2 + 2 * 3] = diagonal;
}

Matrix3x3::Matrix3x3(float* elements) {
	memcpy(this->elements, elements, 3 * 3 * sizeof(float));
}

Matrix3x3::Matrix3x3(Vector3 row0, Vector3 row1, Vector3 row2) {
	rows[0] = row0;
	rows[1] = row1;
	rows[2] = row2;
}

Matrix3x3::Matrix3x3(
	float m00, float m01, float m02,
	float m10, float m11, float m12,
	float m20, float m21, float m22) 
{
	elements[0] = m00; elements[1] = m01; elements[2] = m02;
	elements[3] = m10; elements[4] = m11; elements[5] = m12;
	elements[6] = m20; elements[7] = m21; elements[8] = m22;
}

float Matrix3x3::Determinant() const {
	return 
		  rows[0].x * (rows[1].y * rows[2].z - rows[1].z * rows[2].y)
		- rows[0].y * (rows[1].x * rows[2].z - rows[1].z * rows[2].x)
		+ rows[0].z * (rows[1].x * rows[2].y - rows[1].y * rows[2].x);
}

float Matrix3x3::Trace() const {
	return rows[0].x + rows[1].y + rows[2].z;
}

void Matrix3x3::Transpose() {
	Matrix3x3 tmp = *this;
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

	Matrix3x3 tmp = Matrix3x3();

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

			Matrix2x2 m = Matrix2x2();

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
	rows[0] = Vector3(rows[0].Length(), 0, 0);
	rows[1] = Vector3(0, rows[1].Length(), 0);
	rows[2] = Vector3(0, 0, rows[2].Length());
}

Matrix3x3 Matrix3x3::ClearedRotation() const {
	Matrix3x3 tmp = *this;
	tmp.ClearRotation();

	return tmp;
}

Vector3 Matrix3x3::ExtractScale() const {
	return Vector3(rows[0].Length(), rows[1].Length(), rows[2].Length());
}

Quaternion Matrix3x3::ExtractRotation() const {
	Vector3 r0 = rows[0].Normalized();
	Vector3 r1 = rows[1].Normalized();
	Vector3 r2 = rows[2].Normalized();

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
	if (row > 3 || col > 3 || 0 > row || 0 > col) {
		throw std::out_of_range("Row/Col is outside the bounds of this maxtrix.");
	}

	return elements[col + row * 3];
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3 & other) const {
	return Matrix3x3(
		rows[0] + other.rows[0],
		rows[1] + other.rows[1],
		rows[2] + other.rows[2]
	);
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3 & other) const {
	return Matrix3x3(
		rows[0] - other.rows[0],
		rows[1] - other.rows[1],
		rows[2] - other.rows[2]
	);
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3 & other) const {
	return Matrix3x3(
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
		rows[0] + other,
		rows[1] + other,
		rows[2] + other
	);
}

Matrix3x3 Matrix3x3::operator-(const float other) const {
	return Matrix3x3(
		rows[0] - other,
		rows[1] - other,
		rows[2] - other
	);
}

Matrix3x3 Matrix3x3::operator*(const float other) const {
	return Matrix3x3(
		rows[0] * other,
		rows[1] * other,
		rows[2] * other
	);
}


Matrix3x3 Matrix3x3::operator/(const float other) const {
	return Matrix3x3(
		rows[0] / other,
		rows[1] / other,
		rows[2] / other
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
	return Matrix3x3(-rows[0], -rows[1], -rows[2]);
}

bool Matrix3x3::operator==(const Matrix3x3& other) const {
	return Equals(other);
}

bool Matrix3x3::operator!=(const Matrix3x3& other) const {
	return !Equals(other);
}

bool Matrix3x3::Equals(const Matrix3x3& other) const {
	return rows[0] == other.rows[0] && rows[1] == other.rows[1] && rows[2] == other.rows[2];
}

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
	out.rows[1].y = cos;
	out.rows[1].z = sin;
	out.rows[2].y = -sin;
	out.rows[2].z = cos;

	return out;
}

Matrix3x3 Matrix3x3::CreateRoatationY(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	Matrix3x3 out = Matrix3x3::Identity;
	out.rows[0].x = cos;
	out.rows[0].z = -sin;
	out.rows[2].x = sin;
	out.rows[2].z = cos;

	return out;
}

Matrix3x3 Matrix3x3::CreateRoatationZ(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	Matrix3x3 out = Matrix3x3::Identity;
	out.rows[0].x = cos;
	out.rows[0].y = sin;
	out.rows[1].x = -sin;
	out.rows[1].y = cos;

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

std::ostream& Math::operator<<(std::ostream & ostream, const Matrix3x3 & a) {
	return ostream << a.rows[0] << std::endl << a.rows[1] << std::endl << a.rows[2];
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