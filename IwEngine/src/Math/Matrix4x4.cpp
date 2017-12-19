#include "IwEngine\Math\Matrix4x4.h"
#include "IwEngine\Math\Matrix3x3.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace Math;

Matrix4x4::Matrix4x4() {
	memset(elements, 0, 4 * 4 * sizeof(float));
}

Matrix4x4::Matrix4x4(float diagonal) {
	memset(elements, 0, 4 * 4 * sizeof(float));
}

Matrix4x4::Matrix4x4(float* elements) {
	memcpy(this->elements, elements, 4 * 4 * sizeof(float));
}

Matrix4x4::Matrix4x4(Vector4 row0, Vector4 row1, Vector4 row2, Vector4 row3) {
	rows[0] = row0;
	rows[1] = row1;
	rows[2] = row2;
	rows[3] = row3;
}

Matrix4x4::Matrix4x4(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33) 
{
	elements[0]  = m00; elements[1]  = m01; elements[2]  = m02; elements[3]  = m03; 
	elements[4]  = m10; elements[5]  = m11; elements[6]  = m12; elements[7]  = m13; 
	elements[8]  = m20; elements[9]  = m21; elements[10] = m22; elements[11] = m23;
	elements[12] = m30; elements[13] = m31; elements[14] = m32; elements[15] = m33;
}

float Matrix4x4::Determinant() const {
	return
		  rows[0].x * rows[1].y * rows[2].z * rows[3].z - rows[0].x * rows[1].y * rows[2].w * rows[3].z
		+ rows[0].x * rows[1].z * rows[2].w * rows[3].y - rows[0].x * rows[1].z * rows[2].y * rows[3].z
		+ rows[0].x * rows[1].w * rows[2].y * rows[3].z - rows[0].x * rows[1].w * rows[2].z * rows[3].y
		- rows[0].y * rows[1].z * rows[2].w * rows[3].x + rows[0].y * rows[1].z * rows[2].x * rows[3].z
		- rows[0].y * rows[1].w * rows[2].x * rows[3].z + rows[0].y * rows[1].w * rows[2].z * rows[3].x
		- rows[0].y * rows[1].x * rows[2].z * rows[3].z + rows[0].y * rows[1].x * rows[2].w * rows[3].z
		+ rows[0].z * rows[1].w * rows[2].x * rows[3].y - rows[0].z * rows[1].w * rows[2].y * rows[3].x
		+ rows[0].z * rows[1].x * rows[2].y * rows[3].z - rows[0].z * rows[1].x * rows[2].w * rows[3].y
		+ rows[0].z * rows[1].y * rows[2].w * rows[3].x - rows[0].z * rows[1].y * rows[2].x * rows[3].z
		- rows[0].w * rows[1].x * rows[2].y * rows[3].z + rows[0].w * rows[1].x * rows[2].z * rows[3].y
		- rows[0].w * rows[1].y * rows[2].z * rows[3].x + rows[0].w * rows[1].y * rows[2].x * rows[3].z
		- rows[0].w * rows[1].z * rows[2].x * rows[3].y + rows[0].w * rows[1].z * rows[2].y * rows[3].x;
}

float Matrix4x4::Trace() const {
	return rows[0].x + rows[1].y + rows[2].z + rows[3].w;
}

void Matrix4x4::Transpose() {
	Matrix4x4 tmp = *this;
	rows[0].x = tmp.rows[0].x;
	rows[0].y = tmp.rows[1].x;
	rows[0].z = tmp.rows[2].x;
	rows[0].w = tmp.rows[3].x;
	rows[1].x = tmp.rows[0].y;
	rows[1].y = tmp.rows[1].y;
	rows[1].z = tmp.rows[2].y;
	rows[1].w = tmp.rows[3].y;
	rows[2].x = tmp.rows[0].z;
	rows[2].y = tmp.rows[1].z;
	rows[2].z = tmp.rows[2].z;
	rows[2].w = tmp.rows[3].z;
	rows[3].x = tmp.rows[0].w;
	rows[3].y = tmp.rows[1].w;
	rows[3].z = tmp.rows[2].w;
	rows[3].w = tmp.rows[3].w;
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

	Matrix4x4 tmp = Matrix4x4();

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

			Matrix3x3 m = Matrix3x3();

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
	rows[0] = Vector4(rows[0].Length(), 0, 0, 0);
	rows[1] = Vector4(0, rows[1].Length(), 0, 0);
	rows[2] = Vector4(0, 0, rows[2].Length(), 0);
	rows[3] = Vector4(0, 0, 0, rows[3].Length());
}

Matrix4x4 Matrix4x4::ClearedRotation() const {
	Matrix4x4 tmp = *this;
	tmp.ClearRotation();

	return tmp;
}

Vector3 Matrix4x4::ExtractTranslation() const {
	return rows[3].Xyz();
}

Vector4 Matrix4x4::ExtractScale() const {
	return Vector4(rows[0].Length(), rows[1].Length(), rows[2].Length(), rows[3].Length());
}

Vector4 Matrix4x4::ExtractProjection() const {
	return Vector4(rows[0].w, rows[1].w, rows[2].w, rows[3].w);
}

Quaternion Matrix4x4::ExtractRotation() const {
	Vector3 r0 = rows[0].Normalized().Xyz();
	Vector3 r1 = rows[1].Normalized().Xyz();
	Vector3 r2 = rows[2].Normalized().Xyz();

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
		if (col == 0) return rows[0].x;
		if (col == 1) return rows[0].y;
		if (col == 2) return rows[0].z;
		if (col == 3) return rows[0].w;
	}

	if (row == 1) {
		if (col == 0) return rows[1].x;
		if (col == 1) return rows[1].y;
		if (col == 2) return rows[1].z;
		if (col == 3) return rows[1].w;
	}

	if (row == 2) {
		if (col == 0) return rows[2].x;
		if (col == 1) return rows[2].y;
		if (col == 2) return rows[2].z;
		if (col == 3) return rows[2].w;
	}

	if (row == 3) {
		if (col == 0) return rows[3].x;
		if (col == 1) return rows[3].y;
		if (col == 2) return rows[3].z;
		if (col == 3) return rows[3].w;
	}

	throw std::out_of_range("Row/Col is outside the bounds of this maxtrix.");
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4 & other) const {
	return Matrix4x4(
		rows[0] + other.rows[0],
		rows[1] + other.rows[1],
		rows[2] + other.rows[2],
		rows[3] + other.rows[3]
	);
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4 & other) const {
	return Matrix4x4(
		rows[0] - other.rows[0],
		rows[1] - other.rows[1],
		rows[2] - other.rows[2],
		rows[3] - other.rows[3]
	);
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 & other) const {
	return Matrix4x4(
		(((rows[0].x * rows[0].x) + (rows[0].y * rows[1].x)) + (rows[0].z * rows[2].x)) + (rows[0].w * rows[3].x),
		(((rows[0].x * rows[0].y) + (rows[0].y * rows[1].y)) + (rows[0].z * rows[2].y)) + (rows[0].w * rows[3].y),
		(((rows[0].x * rows[0].z) + (rows[0].y * rows[1].z)) + (rows[0].z * rows[2].z)) + (rows[0].w * rows[3].z),
		(((rows[0].x * rows[0].w) + (rows[0].y * rows[1].w)) + (rows[0].z * rows[2].w)) + (rows[0].w * rows[3].w),
		(((rows[1].x * rows[0].x) + (rows[1].y * rows[1].x)) + (rows[1].z * rows[2].x)) + (rows[1].w * rows[3].x),
		(((rows[1].x * rows[0].y) + (rows[1].y * rows[1].y)) + (rows[1].z * rows[2].y)) + (rows[1].w * rows[3].y),
		(((rows[1].x * rows[0].z) + (rows[1].y * rows[1].z)) + (rows[1].z * rows[2].z)) + (rows[1].w * rows[3].z),
		(((rows[1].x * rows[0].w) + (rows[1].y * rows[1].w)) + (rows[1].z * rows[2].w)) + (rows[1].w * rows[3].w),
		(((rows[2].x * rows[0].x) + (rows[2].y * rows[1].x)) + (rows[2].z * rows[2].x)) + (rows[2].w * rows[3].x),
		(((rows[2].x * rows[0].y) + (rows[2].y * rows[1].y)) + (rows[2].z * rows[2].y)) + (rows[2].w * rows[3].y),
		(((rows[2].x * rows[0].z) + (rows[2].y * rows[1].z)) + (rows[2].z * rows[2].z)) + (rows[2].w * rows[3].z),
		(((rows[2].x * rows[0].w) + (rows[2].y * rows[1].w)) + (rows[2].z * rows[2].w)) + (rows[2].w * rows[3].w),
		(((rows[3].x * rows[0].x) + (rows[3].y * rows[1].x)) + (rows[3].z * rows[2].x)) + (rows[3].w * rows[3].x),
		(((rows[3].x * rows[0].y) + (rows[3].y * rows[1].y)) + (rows[3].z * rows[2].y)) + (rows[3].w * rows[3].y),
		(((rows[3].x * rows[0].z) + (rows[3].y * rows[1].z)) + (rows[3].z * rows[2].z)) + (rows[3].w * rows[3].z),
		(((rows[3].x * rows[0].w) + (rows[3].y * rows[1].w)) + (rows[3].z * rows[2].w)) + (rows[3].w * rows[3].w)
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
		rows[0] + other,
		rows[1] + other,
		rows[2] + other,
		rows[3] + other
	);
}

Matrix4x4 Matrix4x4::operator-(const float other) const {
	return Matrix4x4(
		rows[0] - other,
		rows[1] - other,
		rows[2] - other,
		rows[3] - other
	);
}

Matrix4x4 Matrix4x4::operator*(const float other) const {
	return Matrix4x4(
		rows[0] * other,
		rows[1] * other,
		rows[2] * other,
		rows[3] * other
	);
}


Matrix4x4 Matrix4x4::operator/(const float other) const {
	return Matrix4x4(
		rows[0] / other,
		rows[1] / other,
		rows[2] / other,
		rows[3] / other
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
	return Matrix4x4(-rows[0], -rows[1], -rows[2], -rows[3]);
}

bool Matrix4x4::operator==(const Matrix4x4& other) const {
	return Equals(other);
}

bool Matrix4x4::operator!=(const Matrix4x4& other) const {
	return !Equals(other);
}

bool Matrix4x4::Equals(const Matrix4x4& other) const {
	return rows[0] == other.rows[0] && rows[1] == other.rows[1] && rows[2] == other.rows[2] && rows[3] == other.rows[3];
}

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
	out.rows[1].y = cos;
	out.rows[1].z = sin;
	out.rows[2].y = -sin;
	out.rows[2].z = cos;

	return out;
}

Matrix4x4 Matrix4x4::CreateRoatationY(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	Matrix4x4 out = Matrix4x4::Identity;
	out.rows[0].x = cos;
	out.rows[0].z = -sin;
	out.rows[2].x = sin;
	out.rows[2].z = cos;

	return out;
}

Matrix4x4 Matrix4x4::CreateRoatationZ(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	Matrix4x4 out = Matrix4x4::Identity;
	out.rows[0].x = cos;
	out.rows[0].y = sin;
	out.rows[1].x = -sin;
	out.rows[1].y = cos;

	return out;
}

Matrix4x4 Matrix4x4::CreateRoatation(const Vector3& angles) {
	return Matrix4x4::CreateRoatation(angles.x, angles.y, angles.z);
}

Matrix4x4 Matrix4x4::CreateRoatation(float x, float y, float z) {
	return Matrix4x4::CreateRoatationX(x).CreateRoatationY(y).CreateRoatationZ(z);
}

Matrix4x4 Matrix4x4::CreateTranslation(const Vector3& translation) {
	return CreateTranslation(translation.x, translation.y, translation.z);
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

	out.rows[0].x = 2 * invRL;
	out.rows[1].y = 2 * invTB;
	out.rows[2].z = -2 * invFN;
	out.rows[3].x = -(right + left) * invRL;
	out.rows[3].y = -(top + bottom) * invTB;
	out.rows[3].z = -(zFar + zNear) * invFN;

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

std::ostream& Math::operator<<(std::ostream& ostream, const Matrix4x4& a) {
	return ostream << a.rows[0] << std::endl << a.rows[1] << std::endl << a.rows[2] << std::endl << a.rows[3];
}

Matrix4x4 Math::operator+(const float left, const Matrix4x4& right) {
	return right + left;
}

Matrix4x4 Math::operator-(const float left, const Matrix4x4& right) {
	return right - left;
}

Matrix4x4 Math::operator*(const float left, const Matrix4x4& right) {
	return right * left;
}

Matrix4x4 Math::operator/(const float left, const Matrix4x4& right) {
	return right / left;
}