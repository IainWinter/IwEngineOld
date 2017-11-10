#include "Matrix4x4.h"
#include "Matrix3x3.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace IwMath;

#pragma region Constants

const Matrix4x4 Matrix4x4::Zero = Matrix4x4(Vector4::Zero, Vector4::Zero, Vector4::Zero, Vector4::Zero);
const Matrix4x4 Matrix4x4::Identity = Matrix4x4(Vector4::UnitX, Vector4::UnitY, Vector4::UnitZ, Vector4::UnitW);

#pragma endregion

#pragma region Constructors

Matrix4x4::Matrix4x4(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33) :
	row0(Vector4(m00, m01, m02, m03)),
	row1(Vector4(m10, m11, m12, m13)),
	row2(Vector4(m20, m21, m22, m23)),
	row3(Vector4(m30, m31, m32, m33)) {
}

Matrix4x4::Matrix4x4(Vector4 row0, Vector4 row1, Vector4 row2, Vector4 row3) : row0(row0), row1(row1), row2(row2), row3(row3) {}

#pragma endregion

#pragma region MathFunctions

float Matrix4x4::Determinant() const {
	return
		  row0.x * row1.y * row2.z * row3.z - row0.x * row1.y * row2.w * row3.z + row0.x * row1.z * row2.w * row3.y - row0.x * row1.z * row2.y * row3.z
		+ row0.x * row1.w * row2.y * row3.z - row0.x * row1.w * row2.z * row3.y - row0.y * row1.z * row2.w * row3.x + row0.y * row1.z * row2.x * row3.z
		- row0.y * row1.w * row2.x * row3.z + row0.y * row1.w * row2.z * row3.x - row0.y * row1.x * row2.z * row3.z + row0.y * row1.x * row2.w * row3.z
		+ row0.z * row1.w * row2.x * row3.y - row0.z * row1.w * row2.y * row3.x + row0.z * row1.x * row2.y * row3.z - row0.z * row1.x * row2.w * row3.y
		+ row0.z * row1.y * row2.w * row3.x - row0.z * row1.y * row2.x * row3.z - row0.w * row1.x * row2.y * row3.z + row0.w * row1.x * row2.z * row3.y
		- row0.w * row1.y * row2.z * row3.x + row0.w * row1.y * row2.x * row3.z - row0.w * row1.z * row2.x * row3.y + row0.w * row1.z * row2.y * row3.x;
}

float Matrix4x4::Trace() const {
	return row0.x + row1.y + row2.z + row3.w;
}

void Matrix4x4::Transpose() {
	Matrix4x4 tmp = *this;
	row0.x = tmp.row0.x;
	row0.y = tmp.row1.x;
	row0.z = tmp.row2.x;
	row0.w = tmp.row3.x;
	row1.x = tmp.row0.y;
	row1.y = tmp.row1.y;
	row1.z = tmp.row2.y;
	row1.w = tmp.row3.y;
	row2.x = tmp.row0.z;
	row2.y = tmp.row1.z;
	row2.z = tmp.row2.z;
	row2.w = tmp.row3.z;
	row3.x = tmp.row0.w;
	row3.y = tmp.row1.w;
	row3.z = tmp.row2.w;
	row3.w = tmp.row3.w;
}

Matrix4x4 Matrix4x4::Transposed() const {
	Matrix4x4 tmp = *this;
	tmp.Transpose();

	return tmp;
}

void Matrix4x4::Invert() {
	float aDet = Determinant();
	if (aDet == 0) {
		throw std::invalid_argument("Determinant is zero, therefore inverse matrix doesn't exist.");
	}

	Matrix4x4 tmp = Matrix4x4::Zero;

	for (short i = 0; i < 3; i++) {
		for (short j = 0; j < 3; j++) {
			short t1c = (j + 1) % 4;
			short t1r = (i + 1) % 4;
			short t2c = (j + 2) % 4;
			short t2r = (i + 2) % 4;
			short t3c = (j + 3) % 4;
			short t3r = (i + 3) % 4;

			float m11 = operator()(t1r, t1c);
			float m21 = operator()(t2r, t1c);
			float m31 = operator()(t3r, t1c);
			float m12 = operator()(t1r, t2c);
			float m22 = operator()(t2r, t2c);
			float m32 = operator()(t3r, t2c);
			float m13 = operator()(t1r, t3c);
			float m23 = operator()(t2r, t3c);
			float m33 = operator()(t3r, t3c);

			t1c = t1c == 0 ? 0 : t1c - 1;
			t1r = t1r == 0 ? 0 : t1r - 1;
			t3r = t2r == 0 ? 0 : t2r - 1;
			if (t2c - 1 != t1c) {
				t2c = t2c == 0 ? 0 : t2c - 1;
			}

			if (t2r - 1 != t1r) {
				t2r = t2r == 0 ? 0 : t2r - 1;
			}

			if (t3c - 1 != t2c) {
				t3c = t3c == 0 ? 0 : t3c - 1;
			}

			if (t3r - 1 != t2r) {
				t3r = t3r == 0 ? 0 : t3r - 1;
			}

			Matrix3x3 m = Matrix3x3::Zero;

			m(t1r, t1c) = m11;
			m(t2r, t1c) = m21;
			m(t3r, t1c) = m31;
			m(t1r, t2c) = m12;
			m(t2r, t2c) = m22;
			m(t3r, t2c) = m32;
			m(t1r, t3c) = m13;
			m(t2r, t3c) = m23;
			m(t3r, t3c) = m33;

			float det = m.Determinant();

			tmp(i, j) = det;
		}
	}

	tmp(0, 1) *= -1;
	tmp(0, 3) *= -1;
	tmp(1, 0) *= -1;
	tmp(1, 2) *= -1;
	tmp(2, 1) *= -1;
	tmp(2, 3) *= -1;
	tmp(3, 0) *= -1;
	tmp(3, 2) *= -1;

	tmp.Transpose();
	tmp /= aDet;

	*this = tmp;
}

Matrix4x4 Matrix4x4::Inverted() const {
	Matrix4x4 tmp = *this;
	tmp.Invert();

	return tmp;
}

void Matrix4x4::Normalize() {
	float det = Determinant();
	*this /= det;
}

Matrix4x4 Matrix4x4::Normalized() const {
	float det = Determinant();
	return *this / det;
}

void Matrix4x4::ClearRotation() {
	row0 = Vector4(row0.Length, 0, 0, 0);
	row1 = Vector4(0, row1.Length, 0, 0);
	row2 = Vector4(0, 0, row2.Length, 0);
	row3 = Vector4(0, 0, 0, row3.Length);
}

Matrix4x4 Matrix4x4::ClearedRotation() const {
	Matrix4x4 tmp = *this;
	tmp.ClearRotation();

	return tmp;
}

Vector3 Matrix4x4::ExtractTranslation() const {
	return row3.Xyz();
}

Vector4 Matrix4x4::ExtractScale() const {
	return Vector4(row0.Length, row1.Length, row2.Length, row3.Length);
}

Vector4 Matrix4x4::ExtractProjection() const {
	return Vector4(row0.w, row1.w, row2.w, row3.w);
}

Quaternion Matrix4x4::ExtractRotation() const {
	Vector3 r0 = row0.Normalized().Xyz();
	Vector3 r1 = row1.Normalized().Xyz();
	Vector3 r2 = row2.Normalized().Xyz();

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

float& Matrix4x4::operator()(int row, int col) {
	if (row == 0) {
		if (col == 0) return row0.x;
		if (col == 1) return row0.y;
		if (col == 2) return row0.z;
		if (col == 3) return row0.w;
	}

	if (row == 1) {
		if (col == 0) return row1.x;
		if (col == 1) return row1.y;
		if (col == 2) return row1.z;
		if (col == 3) return row1.w;
	}

	if (row == 2) {
		if (col == 0) return row2.x;
		if (col == 1) return row2.y;
		if (col == 2) return row2.z;
		if (col == 3) return row2.w;
	}

	if (row == 3) {
		if (col == 0) return row3.x;
		if (col == 1) return row3.y;
		if (col == 2) return row3.z;
		if (col == 3) return row3.w;
	}

	throw std::out_of_range("Row/Col is outside the bounds of this maxtrix.");
}

float& Matrix4x4::m00() {
	return row0.x;
}

float& Matrix4x4::m01() {
	return row0.y;
}

float& Matrix4x4::m02() {
	return row0.z;
}

float & Matrix4x4::m03() {
	return row0.w;
}

float& Matrix4x4::m10() {
	return row1.x;
}

float& Matrix4x4::m11() {
	return row1.y;
}

float& Matrix4x4::m12() {
	return row1.z;
}

float & Matrix4x4::m13() {
	return row1.w;
}

float& Matrix4x4::m20() {
	return row2.x;
}

float& Matrix4x4::m21() {
	return row2.y;
}

float& Matrix4x4::m22() {
	return row2.z;
}

float & Matrix4x4::m23() {
	return row2.w;
}

float & Matrix4x4::m30() {
	return row3.x;
}

float & Matrix4x4::m31() {
	return row3.y;
}

float & Matrix4x4::m32() {
	return row3.z;
}

float & Matrix4x4::m33() {
	return row3.w;
}

#pragma endregion

#pragma region Operators

Matrix4x4 Matrix4x4::operator+(const Matrix4x4 & other) const {
	return Matrix4x4(
		row0 + other.row0,
		row1 + other.row1,
		row2 + other.row2,
		row3 + other.row3
	);
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4 & other) const {
	return Matrix4x4(
		row0 - other.row0,
		row1 - other.row1,
		row2 - other.row2,
		row3 - other.row3
	);
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 & other) const {
	return Matrix4x4(
		(((row0.x * row0.x) + (row0.y * row1.x)) + (row0.z * row2.x)) + (row0.w * row3.x),
		(((row0.x * row0.y) + (row0.y * row1.y)) + (row0.z * row2.y)) + (row0.w * row3.y),
		(((row0.x * row0.z) + (row0.y * row1.z)) + (row0.z * row2.z)) + (row0.w * row3.z),
		(((row0.x * row0.w) + (row0.y * row1.w)) + (row0.z * row2.w)) + (row0.w * row3.w),
		(((row1.x * row0.x) + (row1.y * row1.x)) + (row1.z * row2.x)) + (row1.w * row3.x),
		(((row1.x * row0.y) + (row1.y * row1.y)) + (row1.z * row2.y)) + (row1.w * row3.y),
		(((row1.x * row0.z) + (row1.y * row1.z)) + (row1.z * row2.z)) + (row1.w * row3.z),
		(((row1.x * row0.w) + (row1.y * row1.w)) + (row1.z * row2.w)) + (row1.w * row3.w),
		(((row2.x * row0.x) + (row2.y * row1.x)) + (row2.z * row2.x)) + (row2.w * row3.x),
		(((row2.x * row0.y) + (row2.y * row1.y)) + (row2.z * row2.y)) + (row2.w * row3.y),
		(((row2.x * row0.z) + (row2.y * row1.z)) + (row2.z * row2.z)) + (row2.w * row3.z),
		(((row2.x * row0.w) + (row2.y * row1.w)) + (row2.z * row2.w)) + (row2.w * row3.w),
		(((row3.x * row0.x) + (row3.y * row1.x)) + (row3.z * row2.x)) + (row3.w * row3.x),
		(((row3.x * row0.y) + (row3.y * row1.y)) + (row3.z * row2.y)) + (row3.w * row3.y),
		(((row3.x * row0.z) + (row3.y * row1.z)) + (row3.z * row2.z)) + (row3.w * row3.z),
		(((row3.x * row0.w) + (row3.y * row1.w)) + (row3.z * row2.w)) + (row3.w * row3.w)
	);
}

Matrix4x4 Matrix4x4::operator+=(const Matrix4x4 & other) {
	return *this = other + (*this);
}

Matrix4x4 Matrix4x4::operator-=(const Matrix4x4 & other) {
	return *this = other - (*this);
}

Matrix4x4 Matrix4x4::operator*=(const Matrix4x4 & other) {
	return *this = other * (*this);
}

Matrix4x4 Matrix4x4::operator+(const float other) const {
	return Matrix4x4(
		row0 + other,
		row1 + other,
		row2 + other,
		row3 + other
	);
}

Matrix4x4 Matrix4x4::operator-(const float other) const {
	return Matrix4x4(
		row0 - other,
		row1 - other,
		row2 - other,
		row3 - other
	);
}

Matrix4x4 Matrix4x4::operator*(const float other) const {
	return Matrix4x4(
		row0 * other,
		row1 * other,
		row2 * other,
		row3 * other
	);
}


Matrix4x4 Matrix4x4::operator/(const float other) const {
	return Matrix4x4(
		row0 / other,
		row1 / other,
		row2 / other,
		row3 / other
	);
}

Matrix4x4 Matrix4x4::operator+=(const float other) {
	return *this = other * (*this);
}

Matrix4x4 Matrix4x4::operator-=(const float other) {
	return *this = other * (*this);
}

Matrix4x4 Matrix4x4::operator*=(const float other) {
	return *this = other * (*this);
}

Matrix4x4 Matrix4x4::operator/=(const float other) {
	return *this = other / (*this);
}

Matrix4x4 Matrix4x4::operator-() const {
	return Matrix4x4(-row0, -row1, -row2, -row3);
}

bool Matrix4x4::operator==(const Matrix4x4& other) const {
	return Equals(other);
}

bool Matrix4x4::operator!=(const Matrix4x4& other) const {
	return !Equals(other);
}

bool Matrix4x4::Equals(const Matrix4x4& other) const {
	return row0 == other.row0 && row1 == other.row1 && row2 == other.row2 && row3 == other.row3;
}

#pragma endregion

#pragma region Static

Matrix4x4 Matrix4x4::CreateFromAxisAngle(float x, float y, float z, float angle) {
	return CreateFromAxisAngle(Vector3(x, y, z), angle);
}

Matrix4x4 Matrix4x4::CreateFromAxisAngle(const Vector3& axis, float angle) {
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

	return Matrix4x4(
		tXX + cos, tXY - sinZ, tXZ + sinY, 0,
		tXY + sinZ, tYY + cos, tYZ - sinX, 0,
		tXZ - sinY, tYZ + sinX, tZZ + cos, 0,
		0, 0, 0, 1
	);
}

Matrix4x4 Matrix4x4::CreateFromQuaternion(const Quaternion& quaternion) {
	Vector4 aa = quaternion.ToAxisAngle();
	return CreateFromAxisAngle(aa.x, aa.y, aa.z, aa.w);
}

Matrix4x4 Matrix4x4::CreateRoatationX(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	Matrix4x4 out = Matrix4x4::Identity;
	out.row1.y = cos;
	out.row1.z = sin;
	out.row2.y = -sin;
	out.row2.z = cos;

	return out;
}

Matrix4x4 Matrix4x4::CreateRoatationY(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	Matrix4x4 out = Matrix4x4::Identity;
	out.row0.x = cos;
	out.row0.z = -sin;
	out.row2.x = sin;
	out.row2.z = cos;

	return out;
}

Matrix4x4 Matrix4x4::CreateRoatationZ(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	Matrix4x4 out = Matrix4x4::Identity;
	out.row0.x = cos;
	out.row0.y = sin;
	out.row1.x = -sin;
	out.row1.y = cos;

	return out;
}

Matrix4x4 Matrix4x4::CreateRoatation(const Vector3& angles) {
	return Matrix4x4::CreateRoatation(angles.x, angles.y, angles.z);
}

Matrix4x4 Matrix4x4::CreateRoatation(float x, float y, float z) {
	return Matrix4x4::CreateRoatationX(x).CreateRoatationY(y).CreateRoatationZ(z);
}

Matrix4x4 Matrix4x4::CreateTranslation(const Vector3& translation) {
	CreateTranslation(translation.x, translation.y, translation.z);
}

Matrix4x4 Matrix4x4::CreateTranslation(float x, float y, float z) {
	return Matrix4x4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, y, z, 1
	);
}

Matrix4x4 Matrix4x4::CreateScale(float scale) {
	return CreateScale(scale, scale, scale);
}

Matrix4x4 Matrix4x4::CreateScale(const Vector3& scale) {
	return CreateScale(scale.x, scale.y, scale.z);
}

Matrix4x4 Matrix4x4::CreateScale(float x, float y, float z) {
	return Matrix4x4(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 0
	);
}

Matrix4x4 Matrix4x4::CreateOrthographic(float width, float height, float zNear, float zFar) {
	return CreateOrthographicOffCenter(-width / 2, width / 2, -height / 2, height / 2, zNear, zFar);
}

Matrix4x4 Matrix4x4::CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNear, float zFar) {
	Matrix4x4 out = Matrix4x4::Identity;

	float invRL = 1.0f / (right - left);
	float invTB = 1.0f / (top - bottom);
	float invFN = 1.0f / (zFar - zNear);

	out.row0.x = 2 * invRL;
	out.row1.y = 2 * invTB;
	out.row2.z = -2 * invFN;
	out.row3.x = -(right + left) * invRL;
	out.row3.y = -(top + bottom) * invTB;
	out.row3.z = -(zFar + zNear) * invFN;

	return out;
}

Matrix4x4 Matrix4x4::CreatePerspectiveFieldOfView(float fov, float aspect, float zNear, float zFar) {
	if (fov <= 0 || fov > M_PI) {
		throw std::invalid_argument("fovy");
	}

	if (aspect <= 0) {
		throw std::invalid_argument("aspect");
	}

	if (zNear <= 0) {
		throw std::invalid_argument("zNear");
	}

	if (zFar <= 0) {
		throw std::invalid_argument("zFar");
	}

	float yMax = zNear * tanf(0.5f * fov);
	float yMin = -yMax;
	float xMin = yMin * aspect;
	float xMax = yMax * aspect;

	return CreatePerspectiveOffCenter(xMin, xMax, yMin, yMax, zNear, zFar);
}

Matrix4x4 Matrix4x4::CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float zNear, float zFar) {
	if (zNear <= 0 || zNear >= zFar) {
		throw std::invalid_argument("zNear");
	}

	if (zFar <= 0) {
		throw std::invalid_argument("zFar");
	}

	float x = (2.0f * zNear) / (right - left);
	float y = (2.0f * zNear) / (top - bottom);
	float a = (right + left) / (right - left);
	float b = (top + bottom) / (top - bottom);
	float c = -(zFar + zNear) / (zFar - zNear);
	float d = -(2.0f * zFar * zNear) / (zFar - zNear);

	return Matrix4x4(
		x, 0, 0, 0,
		0, y, 0, 0,
		a, b, c, -1, 
		0, 0, d, 0
	);
}

Matrix4x4 Matrix4x4::LookAt(Vector3 eye, Vector3 target, Vector3 up) {
	Vector3 z = (eye - target).Normalized();
	Vector3 x = up.Cross(z).Normalized();
	Vector3 y = z.Cross(x).Normalized();

	return Matrix4x4(
		x.x, y.x, z.x, 0,
		x.y, y.y, z.y, 0,
		x.z, y.z, z.z, 0,
		-((x.x * eye.x) + (x.y * eye.y) + (x.z * eye.z)), 
		-((y.x * eye.x) + (y.y * eye.y) + (y.z * eye.z)), 
		-((z.x * eye.x) + (z.y * eye.y) + (z.z * eye.z)), 1
	);
}

#pragma endregion

std::ostream& IwMath::operator<<(std::ostream & ostream, const Matrix4x4& a) {
	return ostream << a.row0 << std::endl << a.row1 << std::endl << a.row2 << std::endl << a.row3;
}

Matrix4x4 IwMath::operator+(const float left, const Matrix4x4 & right) {
	return right + left;
}

Matrix4x4 IwMath::operator-(const float left, const Matrix4x4 & right) {
	return right - left;
}

Matrix4x4 IwMath::operator*(const float left, const Matrix4x4 & right) {
	return right * left;
}

Matrix4x4 IwMath::operator/(const float left, const Matrix4x4 & right) {
	return right / left;
}