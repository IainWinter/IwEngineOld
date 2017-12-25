#pragma once

#include "IwEngine\Common.h"
#include "Vector3.h"
#include "Quaternion.h"

namespace Math {
	struct IWENGINE_API Matrix4 {
		union {
			float elements[4 * 4];
			Vector4 rows[4];
		};

		static const Matrix4 Identity;

		Matrix4();
		Matrix4(float diagonal);
		Matrix4(float* elements);
		Matrix4(Vector4 row0, Vector4 row1, Vector4 row2, Vector4 row3);
		Matrix4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33
		);

		float Determinant() const;
		float Trace() const;
		void Transpose();
		Matrix4 Transposed() const;
		void Invert();
		Matrix4 Inverted() const;
		void Normalize();
		Matrix4 Normalized() const;
		void ClearRotation();
		Matrix4 ClearedRotation() const;
		Vector3 ExtractTranslation() const;
		Vector4 ExtractScale() const;
		Vector4 ExtractProjection() const;
		Quaternion ExtractRotation() const;

		float& operator()(int row, int col);
		Matrix4 operator+(const Matrix4& other) const;
		Matrix4 operator-(const Matrix4& other) const;
		Matrix4 operator*(const Matrix4& other) const;
		Matrix4 operator+=(const Matrix4& other);
		Matrix4 operator-=(const Matrix4& other);
		Matrix4 operator*=(const Matrix4& other);
		Matrix4 operator+(const float other) const;
		Matrix4 operator-(const float other) const;
		Matrix4 operator*(const float other) const;
		Matrix4 operator/(const float other) const;
		Matrix4 operator+=(const float other);
		Matrix4 operator-=(const float other);
		Matrix4 operator*=(const float other);
		Matrix4 operator/=(const float other);
		Matrix4 operator-() const;
		bool operator==(const Matrix4& other) const;
		bool operator!=(const Matrix4& other) const;
		bool Equals(const Matrix4& other) const;

		static Matrix4 CreateFromAxisAngle(float x, float y, float z, float angle);
		static Matrix4 CreateFromAxisAngle(const Vector3& axis, float angle);
		static Matrix4 CreateFromQuaternion(const Quaternion& quaternion);
		static Matrix4 CreateRoatationX(float angle);
		static Matrix4 CreateRoatationY(float angle);
		static Matrix4 CreateRoatationZ(float angle);
		static Matrix4 CreateRoatation(const Vector3& angles);
		static Matrix4 CreateRoatation(float x, float y, float z);
		static Matrix4 CreateTranslation(const Vector3& translation);
		static Matrix4 CreateTranslation(float x, float y, float z);
		static Matrix4 CreateScale(float scale);
		static Matrix4 CreateScale(const Vector3& scale);
		static Matrix4 CreateScale(float x, float y, float z);
		static Matrix4 CreateOrthographic(float width, float height, float zNear, float zFar);
		static Matrix4 CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNear, float zFar);
		static Matrix4 CreatePerspectiveFieldOfView(float fov, float aspect, float zNear, float zFar);
		static Matrix4 CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float zNear, float zFar);
		static Matrix4 LookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

		friend IWENGINE_API std::ostream& operator<<(std::ostream &strm, const Matrix4 &a);
		friend IWENGINE_API Matrix4 operator+(const float left, const Matrix4& right);
		friend IWENGINE_API Matrix4 operator-(const float left, const Matrix4& right);
		friend IWENGINE_API Matrix4 operator*(const float left, const Matrix4& right);
		friend IWENGINE_API Matrix4 operator/(const float left, const Matrix4& right);
	};
}