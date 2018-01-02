#pragma once

#include <vector>
#include "GL\glew.h"
#include "IwEngine\Common.h"
#include "IwEngine\Utility\Debug.h"

namespace Graphics {
	struct VertexBufferLayoutElement {
		uint type;
		uint count;
		unsigned char normalized;

		static uint GetSizeOfType(uint glType) {
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
		uint _stride;
	public:
		VertexBufferLayout() : _stride(0) {}

		template<typename T>
		void Push(uint count) {
			static_assert(false);
		}

		template<>
		void Push<float>(uint count) {
			_elements.push_back({ GL_FLOAT, count, GL_FALSE });
			_stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_FLOAT);
		}

		template<>
		void Push<uint>(uint count) {
			_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			_stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_INT);
		}

		template<>
		void Push<unsigned char>(uint count) {
			_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			_stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_BYTE);
		}

		inline const std::vector<VertexBufferLayoutElement>& GetElements() const {
			return _elements;
		}

		inline uint GetStride() const {
			return _stride;
		}
	};
}