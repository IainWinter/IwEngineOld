#include "Matrix3x3.h"
#include "Matrix2x2.h"

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
	row2(Vector3(m20, m21, m22)) {}

Matrix3x3::Matrix3x3(Vector3 row0, Vector3 row1, Vector3 row2) : row0(row0), row1(row1), row2(row2) {}

#pragma endregion

#pragma region MathFunctions

float Matrix3x3::Determinant() const {
	float 
		m11 = row0.x, m12 = row0.y, m13 = row0.z,
		m21 = row1.x, m22 = row1.y, m23 = row1.z,
		m31 = row2.x, m32 = row2.y, m33 = row2.z;

	return m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32
		 - m13 * m22 * m31 - m11 * m23 * m32 - m12 * m21 * m33;
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
	tmp.Normalize();

	*this = tmp;
}

int main() {
	Matrix3x3 m(
		3, 0,  2,
		2, 0, -2,
		0, 1,  1
	);

	m.Invert();
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


#pragma endregion

#pragma region Operators

Matrix3x3 Matrix3x3::operator/(const float other) const {
	return Matrix3x3(
		row0 / other,
		row1 / other,
		row2 / other
	);
}

Matrix3x3 Matrix3x3::operator/=(const float other) {
	return *this = other / (*this);
}



#pragma endregion

#pragma region Static

#pragma endregion

std::ostream& operator<<(std::ostream & ostream, const Matrix3x3 & a) {
	return ostream << a.row0 << std::endl << a.row1 << std::endl << a.row2;
}

//Matrix3x3 operator+(const float left, const Matrix3x3 & right) {
//	return right + left;
//}
//
//Matrix3x3 operator-(const float left, const Matrix3x3 & right) {
//	return right - left;
//}
//
//Matrix3x3 operator*(const float left, const Matrix3x3 & right) {
//	return right * left;
//}

Matrix3x3 operator/(const float left, const Matrix3x3 & right) {
	return right / left;
}