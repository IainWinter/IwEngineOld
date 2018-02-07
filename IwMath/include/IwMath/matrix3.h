#pragma once

#include <ostream>
#include "iwmath.h"
#include "vector3.h"
#include "quaternion.h"

namespace iwmath {
	struct IWMATH_API matrix3 {
		static const matrix3 identity;

		union {
			float elements[3 * 3];
			vector3 rows[3];
		};

		matrix3();
		matrix3(float diagonal);
		matrix3(float* elements);
		matrix3(vector3 row0, vector3 row1, vector3 row2);
		matrix3(
			float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22
		);

		float determinant() const;
		float trace() const;
		void transpose();
		matrix3 transposed() const;
		void invert();
		matrix3 inverted() const;
		void normalize();
		matrix3 normalized() const;
		void clearRotation();
		matrix3 clearedRotation() const;
		vector3 extractScale() const;
		quaternion extractRotation() const;

		float& operator()(int row, int col);
		matrix3 operator+(const matrix3& other) const;
		matrix3 operator-(const matrix3& other) const;
		matrix3 operator*(const matrix3& other) const;
		matrix3 operator+=(const matrix3& other);
		matrix3 operator-=(const matrix3& other);
		matrix3 operator*=(const matrix3& other);
		matrix3 operator+(const float& other) const;
		matrix3 operator-(const float& other) const;
		matrix3 operator*(const float& other) const;
		matrix3 operator/(const float& other) const;
		matrix3 operator+=(const float& other);
		matrix3 operator-=(const float& other);
		matrix3 operator*=(const float& other);
		matrix3 operator/=(const float& other);
		matrix3 operator-() const;
		bool operator==(const matrix3& other) const;
		bool operator!=(const matrix3& other) const;
		bool equals(const matrix3& other) const;

		static matrix3 createFromAxisAngle(float x, float y, float z, float angle);
		static matrix3 createFromAxisAngle(const vector3& axis, float angle);
		static matrix3 createFromQuaternion(const quaternion& quaternion);
		static matrix3 createRoatationX(float angle);
		static matrix3 createRoatationY(float angle);
		static matrix3 createRoatationZ(float angle);
		static matrix3 createRoatation(const vector3& angles);
		static matrix3 createRoatation(float x, float y, float z);
		static matrix3 createScale(float scale);
		static matrix3 createScale(const vector3& scale);
		static matrix3 createScale(float x, float y, float z);

		friend IWMATH_API std::ostream& operator<<(std::ostream& stream, const matrix3 &a);
		friend IWMATH_API matrix3 operator+(const float& left, const matrix3& right);
		friend IWMATH_API matrix3 operator-(const float& left, const matrix3& right);
		friend IWMATH_API matrix3 operator*(const float& left, const matrix3& right);
		friend IWMATH_API matrix3 operator/(const float& left, const matrix3& right);
	};
}