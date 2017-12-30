#pragma once
#include "IwEngine\Object.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

namespace Graphics {
	class Mesh : public Object {
	private:
		float* vertices;
		unsigned int* indices;
		VertexArray vertexArray;
		IndexBuffer indexBuffer;
	public:
		Mesh(float* vertices, unsigned int* indices);
		~Mesh();

	};
}

