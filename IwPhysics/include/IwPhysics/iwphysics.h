#pragma once

#ifdef IWPHYSICS_EXPORTS
#define IWPHYSICS_API __declspec(dllexport)
#else
#define IWPHYSICS_API __declspec(dllimport)
#endif

#include "IwMath\matrix4.h"

//Describes a transformation to apply to a collider
struct IWPHYSICS_API transformation {
	iwmath::matrix4 matrix;
	
	transformation(iwmath::matrix4 matrix) 
		: matrix(matrix) {}
	transformation(const iwmath::vector3& translation, const iwmath::quaternion& rotation) {
		matrix = iwmath::matrix4::create_translation(translation)
			* iwmath::matrix4::create_from_quaternion(rotation);
	}

	inline iwmath::vector3 translation() const {
		return matrix.extractTranslation();
	}

	inline iwmath::quaternion rotation() const {
		return matrix.extract_rotation();
	}
};