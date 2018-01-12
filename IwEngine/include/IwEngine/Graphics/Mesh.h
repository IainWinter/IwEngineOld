#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Object.h"
#include "IwEngine\Graphics\VertexArray.h" //TODO: Put in /src and acces through thread safe system (same goes for all \graphics\... .h)
#include "IwEngine\Graphics\IndexBuffer.h"
#include "IwEngine\Graphics\VertexBufferLayout.h" //TODO: Not this one though because it is thread safe

namespace Graphics {
	class IWENGINE_API Mesh : public Object {
	private:
		Graphics::VertexArray* _vertexArray;
		Graphics::IndexBuffer* _indexBuffer;
	public:
		Mesh(const void* data, uint dataCount, const VertexBufferLayout& layout, const uint* indices, uint indexCount);
		~Mesh();

		void Bind() const;

		void AddData(const void* data, uint size, const VertexBufferLayout& layout);
		void SetIndices(const uint* indices, uint count);
	};
}