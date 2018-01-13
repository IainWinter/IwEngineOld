#include "IwEngine\Graphics\Mesh.h"
#include "IwEngine\Graphics\IndexBuffer.h"
#include "GL\glew.h"

using namespace Graphics;

Mesh::Mesh(Graphics::VertexArray* va, Graphics::IndexBuffer* ib)
	: _vertexArray(va), _indexBuffer(ib) {
}

Mesh::~Mesh() {
	delete _vertexArray;
	delete _indexBuffer;
}

void Mesh::Draw() const {
	_vertexArray->Bind();
	_indexBuffer->Bind();

	_indexBuffer->Draw();
}

Mesh* Mesh::MakeBox(const Math::Vector3& bottomCorner, const Math::Vector3& scale) {
	float* pos = new float[72] {
		//left
		bottomCorner.x,				bottomCorner.y,			  bottomCorner.z,
		bottomCorner.x,				bottomCorner.y + scale.y, bottomCorner.z,
		bottomCorner.x,				bottomCorner.y + scale.y, bottomCorner.z + scale.z,
		bottomCorner.x,				bottomCorner.y,			  bottomCorner.z + scale.z,
		//right
		bottomCorner.x + scale.x,	bottomCorner.y,			  bottomCorner.z,
		bottomCorner.x + scale.x,	bottomCorner.y + scale.y, bottomCorner.z,
		bottomCorner.x + scale.x,	bottomCorner.y + scale.y, bottomCorner.z + scale.z,
		bottomCorner.x + scale.x,	bottomCorner.y,			  bottomCorner.z + scale.z,
		//bottom
		bottomCorner.x,				bottomCorner.y,			  bottomCorner.z,
		bottomCorner.x + scale.x,	bottomCorner.y,			  bottomCorner.z,
		bottomCorner.x + scale.x,	bottomCorner.y,			  bottomCorner.z + scale.z,
		bottomCorner.x,				bottomCorner.y,			  bottomCorner.z + scale.z,
		//top
		bottomCorner.x,				bottomCorner.y + scale.y, bottomCorner.z,
		bottomCorner.x + scale.x,	bottomCorner.y + scale.y, bottomCorner.z,
		bottomCorner.x + scale.x,	bottomCorner.y + scale.y, bottomCorner.z + scale.z,
		bottomCorner.x,				bottomCorner.y + scale.y, bottomCorner.z + scale.z,
		//back
		bottomCorner.x,				bottomCorner.y,			  bottomCorner.z,
		bottomCorner.x + scale.x,	bottomCorner.y,			  bottomCorner.z,
		bottomCorner.x + scale.x,	bottomCorner.y + scale.y, bottomCorner.z,
		bottomCorner.x,				bottomCorner.y + scale.y, bottomCorner.z,
		//front
		bottomCorner.x,				bottomCorner.y,			  bottomCorner.z + scale.z,
		bottomCorner.x + scale.x,	bottomCorner.y,			  bottomCorner.z + scale.z,
		bottomCorner.x + scale.x,	bottomCorner.y + scale.y, bottomCorner.z + scale.z, 
		bottomCorner.x,				bottomCorner.y + scale.y, bottomCorner.z + scale.z
	};

	uint* indices = new uint[36] {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		8, 9, 10,
		10, 11, 8,
		12, 13, 14,
		14, 15, 12,
		16, 17, 18,
		18, 19, 16,
		20, 21, 22,
		22, 23, 20
	};

	VertexBufferLayout* layout = new VertexBufferLayout();
	layout->Push<float>(3);

	VertexArray* va = new Graphics::VertexArray();
	IndexBuffer* ib = new Graphics::IndexBuffer(indices, 36);

	VertexBuffer* vb = new VertexBuffer(pos, 72 * sizeof(float));
	va->AddBuffer(*vb, *layout);

	return new Mesh(va, ib);
}

Mesh* Mesh::MakeSphere(const Math::Vector3 & center, float radius, uint detail) {
	return nullptr;
}