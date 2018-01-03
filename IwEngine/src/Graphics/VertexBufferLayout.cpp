#include "GL\glew.h"
#include "IwEngine\Graphics\VertexBufferLayout.h"

using namespace Graphics;

uint VertexBufferLayoutElement::GetSizeOfType(uint glType) {
	switch (glType) {
		case GL_FLOAT: return sizeof(GLfloat);
		case GL_UNSIGNED_INT: return sizeof(GLuint);
		case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
	}

	ASSERT(false);
	return 0;
}

template<typename T>
void Push(uint count) {
	static_assert(false);
}

template<>
void VertexBufferLayout::Push<float>(uint count) {
	_elements.vector.push_back({ GL_FLOAT, count, GL_FALSE });
	_stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_FLOAT);
}

template<>
void VertexBufferLayout::Push<uint>(uint count) {
	_elements.vector.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
	_stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::Push<unsigned char>(uint count) {
	_elements.vector.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
	_stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}
