#pragma once

#include <ostream>
#include "IwMath\mathf.h"
#include "IwMath\vector3.h"
#include "IwMath\vector4.h"
#include "IwMath\quaternion.h"

namespace math {
	struct IWMATH_API matrix4 {
		static const matrix4 identity;

		union {
			float elements[4 * 4];
			vector4 rows[4];
		};

		matrix4();
		matrix4(float diagonal);
		matrix4(float* elements);
		matrix4(vector4 row0, vector4 row1, vector4 row2, vector4 row3);
		matrix4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33
		);

		float determinant() const;
		float trace() const;
		void transpose();
		matrix4 transposed() const;
		void invert();
		matrix4 inverted() const;
		void normalize();
		matrix4 normalized() const;
		void clearRotation();
		matrix4 clearedRotation() const;
		vector3 extractTranslation() const;
		vector4 extractScale() const;
		vector4 extractProjection() const;
		quaternion extractRotation() const;

		float& operator()(int row, int col);
		matrix4 operator+(const matrix4& other) const;
		matrix4 operator-(const matrix4& other) const;
		matrix4 operator*(const matrix4& other) const;
		matrix4 operator+=(const matrix4& other);
		matrix4 operator-=(const matrix4& other);
		matrix4 operator*=(const matrix4& other);
		matrix4 operator+(const float& other) const;
		matrix4 operator-(const float& other) const;
		matrix4 operator*(const float& other) const;
		matrix4 operator/(const float& other) const;
		matrix4 operator+=(const float& other);
		matrix4 operator-=(const float& other);
		matrix4 operator*=(const float& other);
		matrix4 operator/=(const float& other);
		matrix4 operator-() const;
		bool operator==(const matrix4& other) const;
		bool operator!=(const matrix4& other) const;
		bool equals(const matrix4& other) const;

		static matrix4 createFromAxisAngle(float x, float y, float z, float angle);
		static matrix4 createFromAxisAngle(const vector3& axis, float angle);
		static matrix4 createFromquaternion(const quaternion& quaternion);
		static matrix4 createRoatationX(float angle);
		static matrix4 createRoatationY(float angle);
		static matrix4 createRoatationZ(float angle);
		static matrix4 createRoatation(const vector3& angles);
		static matrix4 createRoatation(float x, float y, float z);
		static matrix4 createTranslation(const vector3& translation);
		static matrix4 createTranslation(float x, float y, float z);
		static matrix4 createScale(float scale);
		static matrix4 createScale(const vector3& scale);
		static matrix4 createScale(float x, float y, float z);
		static matrix4 createOrthographic(float width, float height, float zNear, float zFar);
		static matrix4 createOrthographicOffCenter(float left, float right, float bottom, float top, float zNear, float zFar);
		static matrix4 createPerspectiveFieldOfView(float fov, float aspect, float zNear, float zFar);
		static matrix4 createPerspectiveOffCenter(float left, float right, float bottom, float top, float zNear, float zFar);
		static matrix4 lookAt(const vector3& eye, const vector3& target, const vector3& up);

		friend IWMATH_API std::ostream& operator<<(std::ostream& stream, const matrix4& a);
		friend IWMATH_API matrix4 operator+(const float& left, const matrix4& right);
		friend IWMATH_API matrix4 operator-(const float& left, const matrix4& right);
		friend IWMATH_API matrix4 operator*(const float& left, const matrix4& right);
		friend IWMATH_API matrix4 operator/(const float& left, const matrix4& right);
	};
}