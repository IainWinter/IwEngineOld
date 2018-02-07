#pragma once

#include <ostream>
#include "iwmath.h"
#include "vector3.h"
#include "vector4.h"

namespace iwmath {
	struct IWMATH_API quaternion {
		static const quaternion identity;

		float x, y, z, w;

		quaternion();
		quaternion(float x, float y, float z, float w);
		quaternion(const vector3& xyz, float w);
		quaternion(const vector4& xyzw);

		float length() const;
		float lengthSquared() const;
		float lengthFast() const;
		quaternion normalized() const;
		quaternion normalizedFast() const;
		void normalize();
		void normalizeFast();
		quaternion inverted() const;
		void invert();
		quaternion conjugated() const;
		void conjugate();
		vector3 getAxis() const;
		vector4 toAxisAngle() const;
		vector3 toEulerAngles() const;

		quaternion operator+(const quaternion& other) const;
		quaternion operator-(const quaternion& other) const;
		quaternion operator*(const quaternion& other) const;
		quaternion operator+=(const quaternion& other);
		quaternion operator-=(const quaternion& other);
		quaternion operator*=(const quaternion& other);
		quaternion operator*(const float& other) const;
		quaternion operator*=(const float& other);
		bool operator==(const quaternion& other) const;
		bool operator!=(const quaternion& other) const;
		bool equals(const quaternion& other) const;

		static quaternion fromAxisAngle(const vector3& axis, const float& angle);
		static quaternion fromAxisAngle(const vector4& axisAngle);
		static quaternion fromEulerAngles(const float& pitch, const float& yaw, const float& roll);
		static quaternion fromEulerAngles(const vector3& eulerAngles);

		friend IWMATH_API std::ostream& operator<<(std::ostream& stream, const quaternion& a);
		friend IWMATH_API quaternion operator*(const float& left, const quaternion& right);
		friend IWMATH_API vector3 operator*(const vector3& left, const quaternion& right);
	};
}