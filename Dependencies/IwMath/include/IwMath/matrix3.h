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
		void clear_rotation();
		matrix3 cleared_rotation() const;
		vector3 extract_scale() const;
		quaternion extract_rotation() const;

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

		static matrix3 create_from_axis_angle(float x, float y, float z, float angle);
		static matrix3 create_from_axis_angle(const vector3& axis, float angle);
		static matrix3 create_from_quaternion(const quaternion& quaternion);
		static matrix3 create_roatation_x(float angle);
		static matrix3 create_roatation_y(float angle);
		static matrix3 create_roatation_z(float angle);
		static matrix3 create_roatation(const vector3& angles);
		static matrix3 create_roatation(float x, float y, float z);
		static matrix3 create_scale(float scale);
		static matrix3 create_scale(const vector3& scale);
		static matrix3 create_scale(float x, float y, float z);

		friend IWMATH_API std::ostream& operator<<(std::ostream& stream, const matrix3 &a);
		friend IWMATH_API matrix3 operator+(const float& left, const matrix3& right);
		friend IWMATH_API matrix3 operator-(const float& left, const matrix3& right);
		friend IWMATH_API matrix3 operator*(const float& left, const matrix3& right);
		friend IWMATH_API matrix3 operator/(const float& left, const matrix3& right);
	};
}