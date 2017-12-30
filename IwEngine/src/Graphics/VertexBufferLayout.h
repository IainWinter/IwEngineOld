#pragma once

#include <vector>
#include "IwEngine\Utility\Debug.h"
#include "GL\glew.h"

namespace Graphics {
	struct VertexBufferLayoutElement {
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		static unsigned int GetSizeOfType(unsigned int glType) {
			switch (glType) {
			case GL_FLOAT: return sizeof(GLfloat);
			case GL_UNSIGNED_INT: return sizeof(GLuint);
			case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
			}

			ASSERT(false);
			return 0;
		}
	};

	class VertexBufferLayout {
	private:
		std::vector<VertexBufferLayoutElement> _elements;
		unsigned int _stride;
	public:
		VertexBufferLayout() : _stride(0) {}

		template<typename T>
		void Push(unsigned int count) {
			static_assert(false);
		}

		template<>
		void Push<float>(unsigned int count) {
			_elements.push_back({ GL_FLOAT, count, GL_FALSE });
			_stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_FLOAT);
		}

		template<>
		void Push<unsigned int>(unsigned int count) {
			_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			_stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_INT);
		}

		template<>
		void Push<unsigned char>(unsigned int count) {
			_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			_stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_BYTE);
		}

		inline const std::vector<VertexBufferLayoutElement>& GetElements() const {
			return _elements;
		}

		inline unsigned int GetStride() const {
			return _stride;
		}
	};
}