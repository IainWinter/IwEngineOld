#include "IwEngine\Graphics\VertexBuffer.h"
#include "GL\glew.h"

using namespace Graphics;

VertexBuffer::VertexBuffer(const void* data, uint size) {
	glGenBuffers(1, &_renderId);
	glBindBuffer(GL_ARRAY_BUFFER, _renderId);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &_renderId);
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, _renderId);
}

void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
