#include "IwEngine\Math\Matrix4.h"
#include "IwEngine\Math\Matrix3.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace Math;

const Matrix4 Matrix4::Identity = Matrix4(1.0f);

Matrix4::Matrix4() {
	memset(elements, 0, 4 * 4 * sizeof(float));
}

Matrix4::Matrix4(float diagonal) {
	memset(elements, 0, 4 * 4 * sizeof(float));
	elements[0 + 0 * 4] = diagonal;
	elements[1 + 1 * 4] = diagonal;
	elements[2 + 2 * 4] = diagonal;
	elements[3 + 3 * 4] = diagonal;
}

Matrix4::Matrix4(float* elements) {
	memcpy(this->elements, elements, 4 * 4 * sizeof(float));
}

Matrix4::Matrix4(Vector4 row0, Vector4 row1, Vector4 row2, Vector4 row3) {
	rows[0] = row0;
	rows[1] = row1;
	rows[2] = row2;
	rows[3] = row3;
}

Matrix4::Matrix4(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33) {
	elements[0] = m00; elements[1] = m01; elements[2] = m02; elements[3] = m03;
	elements[4] = m10; elements[5] = m11; elements[6] = m12; elements[7] = m13;
	elements[8] = m20; elements[9] = m21; elements[10] = m22; elements[11] = m23;
	elements[12] = m30; elements[13] = m31; elements[14] = m32; elements[15] = m33;
}

float Matrix4::Determinant() const {
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

float Matrix4::Trace() const {
	return rows[0].x + rows[1].y + rows[2].z + rows[3].w;
}

void Matrix4::Transpose() {
	Matrix4 tmp = *this;
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

Matrix4 Matrix4::Transposed() const {
	Matrix4 tmp = *this;
	tmp.Transpose();

	return tmp;
}

void Matrix4::Invert() {
	float aDet = Determinant();
	if (aDet == 0) {
		throw std::invalid_argument("Determinant is zero, therefore inverse matrix doesn't exist.");
	}

	Matrix4 tmp = Matrix4();

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

			Matrix3 m = Matrix3();

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

Matrix4 Matrix4::Inverted() const {
	Matrix4 tmp = *this;
	tmp.Invert();

	return tmp;
}

void Matrix4::Normalize() {
	float det = Determinant();
	*this /= det;
}

Matrix4 Matrix4::Normalized() const {
	float det = Determinant();
	return *this / det;
}

void Matrix4::ClearRotation() {
	rows[0] = Vector4(rows[0].Length(), 0, 0, 0);
	rows[1] = Vector4(0, rows[1].Length(), 0, 0);
	rows[2] = Vector4(0, 0, rows[2].Length(), 0);
	rows[3] = Vector4(0, 0, 0, rows[3].Length());
}

Matrix4 Matrix4::ClearedRotation() const {
	Matrix4 tmp = *this;
	tmp.ClearRotation();

	return tmp;
}

Vector3 Matrix4::ExtractTranslation() const {
	return rows[3].Xyz();
}

Vector4 Matrix4::ExtractScale() const {
	return Vector4(rows[0].Length(), rows[1].Length(), rows[2].Length(), rows[3].Length());
}

Vector4 Matrix4::ExtractProjection() const {
	return Vector4(rows[0].w, rows[1].w, rows[2].w, rows[3].w);
}

Quaternion Matrix4::ExtractRotation() const {
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

float& Matrix4::operator()(int row, int col) {
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

Matrix4 Matrix4::operator+(const Matrix4 & other) const {
	return Matrix4(
		rows[0] + other.rows[0],
		rows[1] + other.rows[1],
		rows[2] + other.rows[2],
		rows[3] + other.rows[3]
	);
}

Matrix4 Matrix4::operator-(const Matrix4 & other) const {
	return Matrix4(
		rows[0] - other.rows[0],
		rows[1] - other.rows[1],
		rows[2] - other.rows[2],
		rows[3] - other.rows[3]
	);
}

Matrix4 Matrix4::operator*(const Matrix4& other) const {
	float lM11 = rows[0].x, lM12 = rows[0].y, lM13 = rows[0].z, lM14 = rows[0].w,
		lM21 = rows[1].x, lM22 = rows[1].y, lM23 = rows[1].z, lM24 = rows[1].w,
		lM31 = rows[2].x, lM32 = rows[2].y, lM33 = rows[2].z, lM34 = rows[2].w,
		lM41 = rows[3].x, lM42 = rows[3].y, lM43 = rows[3].z, lM44 = rows[3].w,
		rM11 = other.rows[0].x, rM12 = other.rows[0].y, rM13 = other.rows[0].z, rM14 = other.rows[0].w,
		rM21 = other.rows[1].x, rM22 = other.rows[1].y, rM23 = other.rows[1].z, rM24 = other.rows[1].w,
		rM31 = other.rows[2].x, rM32 = other.rows[2].y, rM33 = other.rows[2].z, rM34 = other.rows[2].w,
		rM41 = other.rows[3].x, rM42 = other.rows[3].y, rM43 = other.rows[3].z, rM44 = other.rows[3].w;

	return Matrix4(
		(((lM11 * rM11) + (lM12 * rM21)) + (lM13 * rM31)) + (lM14 * rM41),
		(((lM11 * rM12) + (lM12 * rM22)) + (lM13 * rM32)) + (lM14 * rM42),
		(((lM11 * rM13) + (lM12 * rM23)) + (lM13 * rM33)) + (lM14 * rM43),
		(((lM11 * rM14) + (lM12 * rM24)) + (lM13 * rM34)) + (lM14 * rM44),
		(((lM21 * rM11) + (lM22 * rM21)) + (lM23 * rM31)) + (lM24 * rM41),
		(((lM21 * rM12) + (lM22 * rM22)) + (lM23 * rM32)) + (lM24 * rM42),
		(((lM21 * rM13) + (lM22 * rM23)) + (lM23 * rM33)) + (lM24 * rM43),
		(((lM21 * rM14) + (lM22 * rM24)) + (lM23 * rM34)) + (lM24 * rM44),
		(((lM31 * rM11) + (lM32 * rM21)) + (lM33 * rM31)) + (lM34 * rM41),
		(((lM31 * rM12) + (lM32 * rM22)) + (lM33 * rM32)) + (lM34 * rM42),
		(((lM31 * rM13) + (lM32 * rM23)) + (lM33 * rM33)) + (lM34 * rM43),
		(((lM31 * rM14) + (lM32 * rM24)) + (lM33 * rM34)) + (lM34 * rM44),
		(((lM41 * rM11) + (lM42 * rM21)) + (lM43 * rM31)) + (lM44 * rM41),
		(((lM41 * rM12) + (lM42 * rM22)) + (lM43 * rM32)) + (lM44 * rM42),
		(((lM41 * rM13) + (lM42 * rM23)) + (lM43 * rM33)) + (lM44 * rM43),
		(((lM41 * rM14) + (lM42 * rM24)) + (lM43 * rM34)) + (lM44 * rM44));
}

Matrix4 Matrix4::operator+=(const Matrix4 & other) {
	return *this = other + (*this);
}

Matrix4 Matrix4::operator-=(const Matrix4 & other) {
	return *this = other - (*this);
}

Matrix4 Matrix4::operator*=(const Matrix4 & other) {
	return *this = other * (*this);
}

Matrix4 Matrix4::operator+(const float other) const {
	return Matrix4(
		rows[0] + other,
		rows[1] + other,
		rows[2] + other,
		rows[3] + other
	);
}

Matrix4 Matrix4::operator-(const float other) const {
	return Matrix4(
		rows[0] - other,
		rows[1] - other,
		rows[2] - other,
		rows[3] - other
	);
}

Matrix4 Matrix4::operator*(const float other) const {
	return Matrix4(
		rows[0] * other,
		rows[1] * other,
		rows[2] * other,
		rows[3] * other
	);
}


Matrix4 Matrix4::operator/(const float other) const {
	return Matrix4(
		rows[0] / other,
		rows[1] / other,
		rows[2] / other,
		rows[3] / other
	);
}

Matrix4 Matrix4::operator+=(const float other) {
	return *this = other * (*this);
}

Matrix4 Matrix4::operator-=(const float other) {
	return *this = other * (*this);
}

Matrix4 Matrix4::operator*=(const float other) {
	return *this = other * (*this);
}

Matrix4 Matrix4::operator/=(const float other) {
	return *this = other / (*this);
}

Matrix4 Matrix4::operator-() const {
	return Matrix4(-rows[0], -rows[1], -rows[2], -rows[3]);
}

bool Matrix4::operator==(const Matrix4& other) const {
	return Equals(other);
}

bool Matrix4::operator!=(const Matrix4& other) const {
	return !Equals(other);
}

bool Matrix4::Equals(const Matrix4& other) const {
	return rows[0] == other.rows[0] && rows[1] == other.rows[1] && rows[2] == other.rows[2] && rows[3] == other.rows[3];
}

Matrix4 Matrix4::CreateFromAxisAngle(float x, float y, float z, float angle) {
	return CreateFromAxisAngle(Vector3(x, y, z), angle);
}

Matrix4 Matrix4::CreateFromAxisAngle(const Vector3& axis, float angle) {
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

	return Matrix4(
		tXX + cos, tXY - sinZ, tXZ + sinY, 0,
		tXY + sinZ, tYY + cos, tYZ - sinX, 0,
		tXZ - sinY, tYZ + sinX, tZZ + cos, 0,
		0, 0, 0, 1
	);
}

Matrix4 Matrix4::CreateFromQuaternion(const Quaternion& quaternion) {
	Vector4 aa = quaternion.ToAxisAngle();
	return CreateFromAxisAngle(aa.x, aa.y, aa.z, aa.w);
}

Matrix4 Matrix4::CreateRoatationX(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	Matrix4 out = Matrix4::Identity;
	out.rows[1].y = cos;
	out.rows[1].z = sin;
	out.rows[2].y = -sin;
	out.rows[2].z = cos;

	return out;
}

Matrix4 Matrix4::CreateRoatationY(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	Matrix4 out = Matrix4::Identity;
	out.rows[0].x = cos;
	out.rows[0].z = -sin;
	out.rows[2].x = sin;
	out.rows[2].z = cos;

	return out;
}

Matrix4 Matrix4::CreateRoatationZ(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	Matrix4 out = Matrix4::Identity;
	out.rows[0].x = cos;
	out.rows[0].y = sin;
	out.rows[1].x = -sin;
	out.rows[1].y = cos;

	return out;
}

Matrix4 Matrix4::CreateRoatation(const Vector3& angles) {
	return Matrix4::CreateRoatation(angles.x, angles.y, angles.z);
}

Matrix4 Matrix4::CreateRoatation(float x, float y, float z) {
	return Matrix4::CreateRoatationX(x).CreateRoatationY(y).CreateRoatationZ(z);
}

Matrix4 Matrix4::CreateTranslation(const Vector3& translation) {
	return CreateTranslation(translation.x, translation.y, translation.z);
}

Matrix4 Matrix4::CreateTranslation(float x, float y, float z) {
	return Matrix4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, y, z, 1
	);
}

Matrix4 Matrix4::CreateScale(float scale) {
	return CreateScale(scale, scale, scale);
}

Matrix4 Matrix4::CreateScale(const Vector3& scale) {
	return CreateScale(scale.x, scale.y, scale.z);
}

Matrix4 Matrix4::CreateScale(float x, float y, float z) {
	return Matrix4(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 0
	);
}

Matrix4 Matrix4::CreateOrthographic(float width, float height, float zNear, float zFar) {
	return CreateOrthographicOffCenter(-width / 2, width / 2, -height / 2, height / 2, zNear, zFar);
}

Matrix4 Matrix4::CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNear, float zFar) {
	Matrix4 out = Matrix4::Identity;

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

Matrix4 Matrix4::CreatePerspectiveFieldOfView(float fov, float aspect, float zNear, float zFar) {
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

Matrix4 Matrix4::CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float zNear, float zFar) {
	if (zNear <= 0 || zNear >= zFar) {
		throw std::invalid_argument("zNear");
	}

	if (zFar <= 0) {
		throw std::invalid_argument("zFar");
	}

	float x = 2.0f * zNear / (right - left);
	float y = 2 * zNear / (top - bottom);
	float a = -(zFar + zNear) / (zFar - zNear);
	float b = -zNear * (right + left) / (right - left);
	float c = -zNear * (top + bottom) / (top - bottom);
	float d = 2 * zFar * zNear / (zNear - zFar);

	return Matrix4(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, a, -1,
		b, c, d, 0
	);
}

Matrix4 Matrix4::LookAt(const Vector3& eye, const Vector3& target, const Vector3& up) {
	Vector3 z = (eye - target).Normalized();
	Vector3 x = up.Cross(z).Normalized();
	Vector3 y = z.Cross(x).Normalized();

	return Matrix4(
		x.x, y.x, z.x, 0,
		x.y, y.y, z.y, 0,
		x.z, y.z, z.z, 0,
		-((x.x * eye.x) + (x.y * eye.y) + (x.z * eye.z)), 
		-((y.x * eye.x) + (y.y * eye.y) + (y.z * eye.z)), 
		-((z.x * eye.x) + (z.y * eye.y) + (z.z * eye.z)), 1);
}

std::ostream& Math::operator<<(std::ostream& ostream, const Matrix4& a) {
	return ostream << a.rows[0] << std::endl << a.rows[1] << std::endl << a.rows[2] << std::endl << a.rows[3];
}

Matrix4 Math::operator+(const float left, const Matrix4& right) {
	return right + left;
}

Matrix4 Math::operator-(const float left, const Matrix4& right) {
	return right - left;
}

Matrix4 Math::operator*(const float left, const Matrix4& right) {
	return right * left;
}

Matrix4 Math::operator/(const float left, const Matrix4& right) {
	return right / left;
}