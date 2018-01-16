#include "IwEngine\Graphics\VertexArray.h"
#include "GL\glew.h"

using namespace Graphics;

VertexArray::VertexArray() {
	glGenVertexArrays(1, &_renderId);
	glBindVertexArray(_renderId);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &_renderId);

	for (std::vector<VertexBuffer*>::iterator it = _buffers.begin(); it != _buffers.end(); ++it) {
		delete (*it);
	}

	for (std::vector<VertexBufferLayout*>::iterator it = _layouts.begin(); it != _layouts.end(); ++it) {
		delete (*it);
	}

	_buffers.clear();
	_layouts.clear();
}

void VertexArray::AddBuffer(VertexBuffer* vb, VertexBufferLayout* layout) {
	Bind();
	vb->Bind();
	const auto& elements = layout->GetElements();
	uint offset = 0;
	for (uint i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout->GetStride(), (const void*)offset);
		offset += element.count * VertexBufferLayoutElement::GetSizeOfType(element.type);
	}

	_buffers.push_back(vb);
	_layouts.push_back(layout);
}

void VertexArray::Bind() const {
	glBindVertexArray(_renderId);
}

void VertexArray::Unbind() const {;
	glBindVertexArray(0);
}
