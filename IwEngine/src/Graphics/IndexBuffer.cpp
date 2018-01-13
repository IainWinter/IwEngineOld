#include "IwEngine\Graphics\IndexBuffer.h"
#include "GL\glew.h"

using namespace Graphics;

IndexBuffer::IndexBuffer(const void* data, uint count) : _count(count), _data(data) {
	glGenBuffers(1, &_renderId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _renderId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW);
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

void Graphics::IndexBuffer::Draw() const {
	glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, nullptr);
}
