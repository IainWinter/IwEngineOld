#include "IwMath\matrix4.h"
#include "IwMath\matrix3.h"

using namespace iwmath;

const matrix4 matrix4::identity = matrix4(1.0f);

matrix4::matrix4() {
	memset(elements, 0, 4 * 4 * sizeof(float));
}

matrix4::matrix4(float diagonal) {
	memset(elements, 0, 4 * 4 * sizeof(float));
	elements[0 + 0 * 4] = diagonal;
	elements[1 + 1 * 4] = diagonal;
	elements[2 + 2 * 4] = diagonal;
	elements[3 + 3 * 4] = diagonal;
}

matrix4::matrix4(float* elements) {
	memcpy(this->elements, elements, 4 * 4 * sizeof(float));
}

matrix4::matrix4(vector4 row0, vector4 row1, vector4 row2, vector4 row3) {
	rows[0] = row0;
	rows[1] = row1;
	rows[2] = row2;
	rows[3] = row3;
}

matrix4::matrix4(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33) {
	elements[0] = m00; elements[1] = m01; elements[2] = m02; elements[3] = m03;
	elements[4] = m10; elements[5] = m11; elements[6] = m12; elements[7] = m13;
	elements[8] = m20; elements[9] = m21; elements[10] = m22; elements[11] = m23;
	elements[12] = m30; elements[13] = m31; elements[14] = m32; elements[15] = m33;
}

float matrix4::determinant() const {
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

float matrix4::trace() const {
	return rows[0].x + rows[1].y + rows[2].z + rows[3].w;
}

void matrix4::transpose() {
	matrix4 tmp = *this;
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

matrix4 matrix4::transposed() const {
	matrix4 tmp = *this;
	tmp.transpose();

	return tmp;
}

void matrix4::invert() {
	float aDet = determinant();
	if (aDet == 0) {
		throw std::invalid_argument("Determinant is zero, therefore inverse matrix doesn't exist.");
	}

	matrix4 tmp = matrix4();

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

			matrix3 m = matrix3();

			m(t1r, t1c) = m11;
			m(t2r, t1c) = m21;
			m(t3r, t1c) = m31;
			m(t1r, t2c) = m12;
			m(t2r, t2c) = m22;
			m(t3r, t2c) = m32;
			m(t1r, t3c) = m13;
			m(t2r, t3c) = m23;
			m(t3r, t3c) = m33;

			float det = m.determinant();

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

	tmp.transpose();
	tmp /= aDet;

	*this = tmp;
}

matrix4 matrix4::inverted() const {
	matrix4 tmp = *this;
	tmp.invert();

	return tmp;
}

void matrix4::normalize() {
	float det = determinant();
	*this /= det;
}

matrix4 matrix4::normalized() const {
	float det = determinant();
	return *this / det;
}

void matrix4::clearRotation() {
	rows[0] = vector4(rows[0].length(), 0, 0, 0);
	rows[1] = vector4(0, rows[1].length(), 0, 0);
	rows[2] = vector4(0, 0, rows[2].length(), 0);
	rows[3] = vector4(0, 0, 0, rows[3].length());
}

matrix4 matrix4::clearedRotation() const {
	matrix4 tmp = *this;
	tmp.clearRotation();

	return tmp;
}

vector3 matrix4::extractTranslation() const {
	return rows[3].asVector3();
}

vector4 matrix4::extractScale() const {
	return vector4(rows[0].length(), rows[1].length(), rows[2].length(), rows[3].length());
}

vector4 matrix4::extractProjection() const {
	return vector4(rows[0].w, rows[1].w, rows[2].w, rows[3].w);
}

quaternion matrix4::extractRotation() const {
	vector3 r0 = rows[0].asVector3().normalized();
	vector3 r1 = rows[1].asVector3().normalized();
	vector3 r2 = rows[2].asVector3().normalized();

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

float& matrix4::operator()(int row, int col) {
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

matrix4 matrix4::operator+(const matrix4& other) const {
	return matrix4(
		rows[0] + other.rows[0],
		rows[1] + other.rows[1],
		rows[2] + other.rows[2],
		rows[3] + other.rows[3]
	);
}

matrix4 matrix4::operator-(const matrix4& other) const {
	return matrix4(
		rows[0] - other.rows[0],
		rows[1] - other.rows[1],
		rows[2] - other.rows[2],
		rows[3] - other.rows[3]
	);
}

matrix4 matrix4::operator*(const matrix4& other) const {
	float lM11 = rows[0].x, lM12 = rows[0].y, lM13 = rows[0].z, lM14 = rows[0].w,
		lM21 = rows[1].x, lM22 = rows[1].y, lM23 = rows[1].z, lM24 = rows[1].w,
		lM31 = rows[2].x, lM32 = rows[2].y, lM33 = rows[2].z, lM34 = rows[2].w,
		lM41 = rows[3].x, lM42 = rows[3].y, lM43 = rows[3].z, lM44 = rows[3].w,
		rM11 = other.rows[0].x, rM12 = other.rows[0].y, rM13 = other.rows[0].z, rM14 = other.rows[0].w,
		rM21 = other.rows[1].x, rM22 = other.rows[1].y, rM23 = other.rows[1].z, rM24 = other.rows[1].w,
		rM31 = other.rows[2].x, rM32 = other.rows[2].y, rM33 = other.rows[2].z, rM34 = other.rows[2].w,
		rM41 = other.rows[3].x, rM42 = other.rows[3].y, rM43 = other.rows[3].z, rM44 = other.rows[3].w;

	return matrix4(
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

matrix4 matrix4::operator+=(const matrix4& other) {
	return *this = other + (*this);
}

matrix4 matrix4::operator-=(const matrix4& other) {
	return *this = other - (*this);
}

matrix4 matrix4::operator*=(const matrix4& other) {
	return *this = other * (*this);
}

matrix4 matrix4::operator+(const float& other) const {
	return matrix4(
		rows[0] + other,
		rows[1] + other,
		rows[2] + other,
		rows[3] + other
	);
}

matrix4 matrix4::operator-(const float& other) const {
	return matrix4(
		rows[0] - other,
		rows[1] - other,
		rows[2] - other,
		rows[3] - other
	);
}

matrix4 matrix4::operator*(const float& other) const {
	return matrix4(
		rows[0] * other,
		rows[1] * other,
		rows[2] * other,
		rows[3] * other
	);
}


matrix4 matrix4::operator/(const float& other) const {
	return matrix4(
		rows[0] / other,
		rows[1] / other,
		rows[2] / other,
		rows[3] / other
	);
}

matrix4 matrix4::operator+=(const float& other) {
	return *this = other * (*this);
}

matrix4 matrix4::operator-=(const float& other) {
	return *this = other * (*this);
}

matrix4 matrix4::operator*=(const float& other) {
	return *this = other * (*this);
}

matrix4 matrix4::operator/=(const float& other) {
	return *this = other / (*this);
}

matrix4 matrix4::operator-() const {
	return matrix4(-rows[0], -rows[1], -rows[2], -rows[3]);
}

bool matrix4::operator==(const matrix4& other) const {
	return equals(other);
}

bool matrix4::operator!=(const matrix4& other) const {
	return !equals(other);
}

bool matrix4::equals(const matrix4& other) const {
	return rows[0] == other.rows[0] && rows[1] == other.rows[1] && rows[2] == other.rows[2] && rows[3] == other.rows[3];
}

matrix4 matrix4::createFromAxisAngle(float x, float y, float z, float angle) {
	return createFromAxisAngle(vector3(x, y, z), angle);
}

matrix4 matrix4::createFromAxisAngle(const vector3& axis, float angle) {
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

	return matrix4(
		tXX + cos, tXY - sinZ, tXZ + sinY, 0,
		tXY + sinZ, tYY + cos, tYZ - sinX, 0,
		tXZ - sinY, tYZ + sinX, tZZ + cos, 0,
		0, 0, 0, 1
	);
}

matrix4 matrix4::createFromQuaternion(const quaternion& quaternion) {
	vector4 aa = quaternion.toAxisAngle();
	return createFromAxisAngle(aa.x, aa.y, aa.z, aa.w);
}

matrix4 matrix4::createRoatationX(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	matrix4 out = matrix4::identity;
	out.rows[1].y = cos;
	out.rows[1].z = sin;
	out.rows[2].y = -sin;
	out.rows[2].z = cos;

	return out;
}

matrix4 matrix4::createRoatationY(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	matrix4 out = matrix4::identity;
	out.rows[0].x = cos;
	out.rows[0].z = -sin;
	out.rows[2].x = sin;
	out.rows[2].z = cos;

	return out;
}

matrix4 matrix4::createRoatationZ(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	matrix4 out = matrix4::identity;
	out.rows[0].x = cos;
	out.rows[0].y = sin;
	out.rows[1].x = -sin;
	out.rows[1].y = cos;

	return out;
}

matrix4 matrix4::createRoatation(const vector3& angles) {
	return matrix4::createRoatation(angles.x, angles.y, angles.z);
}

matrix4 matrix4::createRoatation(float x, float y, float z) {
	return matrix4::createRoatationX(x)
		* matrix4::createRoatationY(y)
		* matrix4::createRoatationZ(z);
}

matrix4 matrix4::createTranslation(const vector3& translation) {
	return createTranslation(translation.x, translation.y, translation.z);
}

matrix4 matrix4::createTranslation(float x, float y, float z) {
	return matrix4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, y, z, 1
	);
}

matrix4 matrix4::createScale(float scale) {
	return createScale(scale, scale, scale);
}

matrix4 matrix4::createScale(const vector3& scale) {
	return createScale(scale.x, scale.y, scale.z);
}

matrix4 matrix4::createScale(float x, float y, float z) {
	return matrix4(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 0
	);
}

matrix4 matrix4::createOrthographic(float width, float height, float zNear, float zFar) {
	return createOrthographicOffCenter(-width / 2, width / 2, -height / 2, height / 2, zNear, zFar);
}

matrix4 matrix4::createOrthographicOffCenter(float left, float right, float bottom, float top, float zNear, float zFar) {
	matrix4 out = matrix4::identity;

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

matrix4 matrix4::createPerspectiveFieldOfView(float fov, float aspect, float zNear, float zFar) {
	if (fov <= 0 || fov > PI) {
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

	return createPerspectiveOffCenter(xMin, xMax, yMin, yMax, zNear, zFar);
}

matrix4 matrix4::createPerspectiveOffCenter(float left, float right, float bottom, float top, float zNear, float zFar) {
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

	return matrix4(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, a, -1,
		b, c, d, 0
	);
}

matrix4 matrix4::lookAt(const vector3& eye, const vector3& target, const vector3& up) {
	vector3 z = (eye - target).normalized();
	vector3 x = up.cross(z).normalized();
	vector3 y = z.cross(x).normalized();

	return matrix4(
		x.x, y.x, z.x, 0,
		x.y, y.y, z.y, 0,
		x.z, y.z, z.z, 0,
		-((x.x * eye.x) + (x.y * eye.y) + (x.z * eye.z)),
		-((y.x * eye.x) + (y.y * eye.y) + (y.z * eye.z)),
		-((z.x * eye.x) + (z.y * eye.y) + (z.z * eye.z)), 1);
}

std::ostream& iwmath::operator<<(std::ostream& ostream, const matrix4& a) {
	return ostream << a.rows[0] << std::endl << a.rows[1] << std::endl << a.rows[2] << std::endl << a.rows[3];
}

matrix4 iwmath::operator+(const float& left, const matrix4& right) {
	return right + left;
}

matrix4 iwmath::operator-(const float& left, const matrix4& right) {
	return right - left;
}

matrix4 iwmath::operator*(const float& left, const matrix4& right) {
	return right * left;
}

matrix4 iwmath::operator/(const float& left, const matrix4& right) {
	return right / left;
}