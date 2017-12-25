#pragma once

#include "IwEngine\Common.h"
#include "Vector3.h"
#include "Quaternion.h"

namespace Math {
	struct IWENGINE_API Matrix3 {
		union {
			float elements[3 * 3];
			Vector3 rows[3];
		};

		static const Matrix3 Identity;

		Matrix3();
		Matrix3(float diagonal);
		Matrix3(float* elements);
		Matrix3(Vector3 row0, Vector3 row1, Vector3 row2);
		Matrix3(
			float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22
		);

		float Determinant() const;
		float Trace() const;
		void Transpose();
		Matrix3 Transposed() const;
		void Invert();
		Matrix3 Inverted() const;
		void Normalize();
		Matrix3 Normalized() const;
		void ClearRotation();
		Matrix3 ClearedRotation() const;
		Vector3 ExtractScale() const;
		Quaternion ExtractRotation() const;

		float& operator()(int row, int col);
		Matrix3 operator+(const Matrix3& other) const;
		Matrix3 operator-(const Matrix3& other) const;
		Matrix3 operator*(const Matrix3& other) const;
		Matrix3 operator+=(const Matrix3& other);
		Matrix3 operator-=(const Matrix3& other);
		Matrix3 operator*=(const Matrix3& other);
		Matrix3 operator+(const float other) const;
		Matrix3 operator-(const float other) const;
		Matrix3 operator*(const float other) const;
		Matrix3 operator/(const float other) const;
		Matrix3 operator+=(const float other);
		Matrix3 operator-=(const float other);
		Matrix3 operator*=(const float other);
		Matrix3 operator/=(const float other);
		Matrix3 operator-() const;
		bool operator==(const Matrix3& other) const;
		bool operator!=(const Matrix3& other) const;
		bool Equals(const Matrix3& other) const;

		static Matrix3 CreateFromAxisAngle(float x, float y, float z, float angle);
		static Matrix3 CreateFromAxisAngle(const Vector3& axis, float angle);
		static Matrix3 CreateFromQuaternion(const Quaternion& quaternion);
		static Matrix3 CreateRoatationX(float angle);
		static Matrix3 CreateRoatationY(float angle);
		static Matrix3 CreateRoatationZ(float angle);
		static Matrix3 CreateRoatation(const Vector3& angles);
		static Matrix3 CreateRoatation(float x, float y, float z);
		static Matrix3 CreateScale(float scale);
		static Matrix3 CreateScale(const Vector3& scale);
		static Matrix3 CreateScale(float x, float y, float z);

		friend IWENGINE_API std::ostream& operator<<(std::ostream &strm, const Matrix3 &a);
		friend IWENGINE_API Matrix3 operator+(const float left, const Matrix3& right);
		friend IWENGINE_API Matrix3 operator-(const float left, const Matrix3& right);
		friend IWENGINE_API Matrix3 operator*(const float left, const Matrix3& right);
		friend IWENGINE_API Matrix3 operator/(const float left, const Matrix3& right);
	};
}