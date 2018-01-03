#include "IwEngine\Graphics\Mesh.h"
#include "IwEngine\Graphics\IndexBuffer.h"

using namespace Graphics;

Mesh::Mesh() {
	vertexArray = new VertexArray();
	indexBuffer = new IndexBuffer({ }, 0);
}

Mesh::Mesh(const void* data, uint dataCount, const VertexBufferLayout& layout, const uint* indices, uint indexCount) {
	vertexArray = new VertexArray();
	indexBuffer = new IndexBuffer(indices, indexCount);
	AddData(data, dataCount, layout);
}

Mesh::~Mesh() {
	delete &vertexArray;
	delete &indexBuffer;
}

void Mesh::AddData(const void* data, uint size, const VertexBufferLayout& layout) {
	VertexBuffer buffer = VertexBuffer(data, size);
	vertexArray->AddBuffer(buffer, layout);
}

void Mesh::SetIndices(const uint* indices, uint count) {
	indexBuffer = new IndexBuffer(indices, count);
}
