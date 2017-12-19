#pragma once

#include "IwEngine\Common.h"

#include "Vector2.h"

namespace Math {
	struct IWENGINE_API Matrix2x2 {
		union {
			float elements[2 * 2];
			Vector2 rows[2];
		};

		static const Matrix2x2 Identity;

		Matrix2x2();
		Matrix2x2(float diagonal);
		Matrix2x2(float* elements);
		Matrix2x2(Vector2& row0, Vector2& row1);
		Matrix2x2(
			float m00, float m01,
			float m10, float m11
		);

		float Determinant() const;
		float Trace() const;
		void Transpose();
		Matrix2x2 Transposed() const;
		void Invert();
		Matrix2x2 Inverted() const;
		void Normalize();
		Matrix2x2 Normalized() const;

		float& operator()(int x, int y);
		Matrix2x2 operator+(const Matrix2x2& other) const;
		Matrix2x2 operator-(const Matrix2x2& other) const;
		Matrix2x2 operator*(const Matrix2x2& other) const;
		Matrix2x2 operator+=(const Matrix2x2& other);
		Matrix2x2 operator-=(const Matrix2x2& other);
		Matrix2x2 operator*=(const Matrix2x2& other);
		Matrix2x2 operator+(const float other) const;
		Matrix2x2 operator-(const float other) const;
		Matrix2x2 operator*(const float other) const;
		Matrix2x2 operator/(const float other) const;
		Matrix2x2 operator+=(const float other);
		Matrix2x2 operator-=(const float other);
		Matrix2x2 operator*=(const float other);
		Matrix2x2 operator/=(const float other);
		Matrix2x2 operator-() const;
		bool operator==(const Matrix2x2& other) const;
		bool operator!=(const Matrix2x2& other) const;
		bool Equals(const Matrix2x2& other) const;

		static Matrix2x2 CreateRoatation(float angle);
		static Matrix2x2 CreateScale(float scale);
		static Matrix2x2 CreateScale(const Vector2& scale);
		static Matrix2x2 CreateScale(float x, float y);

		friend IWENGINE_API std::ostream& operator<<(std::ostream &strm, const Matrix2x2 &a);
		friend IWENGINE_API Matrix2x2 operator+(const float left, const Matrix2x2& right);
		friend IWENGINE_API Matrix2x2 operator-(const float left, const Matrix2x2& right);
		friend IWENGINE_API Matrix2x2 operator*(const float left, const Matrix2x2& right);
		friend IWENGINE_API Matrix2x2 operator/(const float left, const Matrix2x2& right);
	};

	const Matrix2x2 Matrix2x2::Identity = Matrix2x2(1.0f);
}