#pragma once

#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

namespace Graphics {
	class VertexArray {
	private:
		unsigned int _renderId;
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		void Bind() const;
		void Unbind() const;
	};

}