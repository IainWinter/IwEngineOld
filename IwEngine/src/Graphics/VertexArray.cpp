#include "IwEngine\Graphics\VertexArray.h"
#include "GL\glew.h"

using namespace Graphics;

VertexArray::VertexArray() {
	glGenVertexArrays(1, &_renderId);
	glBindVertexArray(_renderId);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &_renderId);

	uint bCount = _buffers.size();
	uint lCount = _layouts.size();
	for (size_t i = 0; i < bCount; i++) {
		delete _buffers[i];
	}

	for (size_t i = 0; i < lCount; i++) {
		delete _layouts[i];
	}
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	uint offset = 0;
	for (uint i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferLayoutElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const {
	glBindVertexArray(_renderId);
}

void VertexArray::Unbind() const {;
	glBindVertexArray(0);
}
