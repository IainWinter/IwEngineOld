#pragma once

#include <ostream>
#include "iwmath.h"
#include "vector3.h"
#include "vector4.h"
#include "quaternion.h"

namespace iwmath {
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
		void clear_rotation();
		matrix4 cleared_rotation() const;
		vector3 extractTranslation() const;
		vector4 extract_scale() const;
		vector4 extractProjection() const;
		quaternion extract_rotation() const;

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

		static matrix4 create_from_axis_angle(float x, float y, float z, float angle);
		static matrix4 create_from_axis_angle(const vector3& axis, float angle);
		static matrix4 create_from_quaternion(const quaternion& quaternion);
		static matrix4 create_roatation_x(float angle);
		static matrix4 create_roatation_y(float angle);
		static matrix4 create_roatation_z(float angle);
		static matrix4 create_roatation(const vector3& angles);
		static matrix4 create_roatation(float x, float y, float z);
		static matrix4 create_translation(const vector3& translation);
		static matrix4 create_translation(float x, float y, float z);
		static matrix4 create_scale(float scale);
		static matrix4 create_scale(const vector3& scale);
		static matrix4 create_scale(float x, float y, float z);
		static matrix4 create_orthographic(float width, float height, float zNear, float zFar);
		static matrix4 create_orthographic_off_center(float left, float right, float bottom, float top, float zNear, float zFar);
		static matrix4 create_perspective_field_of_view(float fov, float aspect, float zNear, float zFar);
		static matrix4 create_perspective_off_center(float left, float right, float bottom, float top, float zNear, float zFar);
		static matrix4 look_at(const vector3& eye, const vector3& target, const vector3& up);

		friend IWMATH_API std::ostream& operator<<(std::ostream& stream, const matrix4& a);
		friend IWMATH_API matrix4 operator+(const float& left, const matrix4& right);
		friend IWMATH_API matrix4 operator-(const float& left, const matrix4& right);
		friend IWMATH_API matrix4 operator*(const float& left, const matrix4& right);
		friend IWMATH_API matrix4 operator/(const float& left, const matrix4& right);
	};
}