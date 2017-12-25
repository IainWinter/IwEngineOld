#include "IndexBuffer.h"
#include "GL\glew.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count) : _count(count) {
	glGenBuffers(1, &_renderId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _renderId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &_renderId);
}

void IndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _renderId);
}

void IndexBuffer::Unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
