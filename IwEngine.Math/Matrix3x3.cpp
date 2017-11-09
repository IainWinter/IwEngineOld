#include "Matrix3x3.h"

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
}

Matrix3x3 Matrix3x3::Inverted() const {
	return Matrix3x3();
}

void Matrix3x3::Normalize() {
}

Matrix3x3 Matrix3x3::Normalized() const {
	return Matrix3x3();
}

void Matrix3x3::ClearRotation() {
}

#pragma endregion

#pragma region Operators

#pragma endregion

#pragma region Static

#pragma endregion