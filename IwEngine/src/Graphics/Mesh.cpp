#include "IwEngine\Graphics\Mesh.h"
#include "IwEngine\Graphics\IndexBuffer.h"
#include "GL\glew.h"

using namespace Graphics;

Mesh::Mesh(Graphics::VertexArray* va, Graphics::IndexBuffer* ib)
	: _vertexArray(va), _indexBuffer(ib) {}

Mesh::~Mesh() {
	delete &_vertexArray;
	delete &_indexBuffer;
}

void Graphics::Mesh::Draw() const {
	_vertexArray->Bind();
	_indexBuffer->Bind();

	_indexBuffer->Draw();
}