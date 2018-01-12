#include "IwEngine\Graphics\Mesh.h"
#include "IwEngine\Graphics\IndexBuffer.h"

using namespace Graphics;

Mesh::Mesh(const void* data, uint dataCount, const VertexBufferLayout& layout, const uint* indices, uint indexCount) {
	_vertexArray = new VertexArray();
	_indexBuffer = new IndexBuffer(indices, indexCount);
	AddData(data, dataCount, layout);
}

Mesh::~Mesh() {
	delete &_vertexArray;
	delete &_indexBuffer;
}

void Graphics::Mesh::Bind() const {
	_vertexArray->Bind();
	_indexBuffer->Bind();
}

void Mesh::AddData(const void* data, uint size, const VertexBufferLayout& layout) {
	VertexBuffer buffer = VertexBuffer(data, size);
	_vertexArray->AddBuffer(buffer, layout);
}

void Mesh::SetIndices(const uint* indices, uint count) {
	_indexBuffer = new IndexBuffer(indices, count);
}
